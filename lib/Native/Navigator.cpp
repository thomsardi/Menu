#include <Navigator.h>

Navigator::Navigator(uint8_t col, uint8_t row)
{
    _colSize = col;
    _rowSize = row;
    _screenCursorPos = _cursorPos;
    _isInCustomEvent = false;
    _activeListener = nullptr;
    _isKeypadDisabled = false;
    _isNeedUpdate = true;
}

void Navigator::run()
{
    if (_isNeedUpdate)
    {
        print();
        _isNeedUpdate = false;
    }
    if (_isInCustomEvent)
    {
        if (_activeListener != nullptr)
        {
            _activeListener();
        }
        else
        {
            if (_notFoundListener != nullptr)
            {
                _notFoundListener();
            }
        }
    }
    else
    {
        _activeListener = nullptr;
    }
}

void Navigator::setMenu(const DataList &content)
{
    _isNeedUpdate = true;
    _dataMenu.clear();
    _listenerList.clear();
    _activeListener = nullptr;
    for (size_t i = 0; i < content.size(); i++)
    {
        _dataMenu.push_back(content.at(i));
    }
    getContentsByParentId(0);
}

void Navigator::setArrow(bool enabled)
{
    _isArrowEnabled = enabled;
}

void Navigator::print()
{
    if (_buffer.size() <= 0)
    {
        return;
    }
    // printList(std::cout);
    printList(_buffer);
}

void Navigator::printList(const DataList &_buffer)
{
    int rows = _rowSize;
    if (_buffer.size() <= _rowSize)
    {
        rows = _buffer.size();
    }
    
    for (int i = 0; i < rows; i++)
    {
        if (i == _screenCursorPos)
        {
            std::cout << ">";
        }
        else
        {
            std::cout << ".";
        }
        int index = (_cursorPos - _screenCursorPos) + i;
        if (index < 0)
        {
            index = _buffer.size() - abs(index);
        }

        else if (index >= _buffer.size())
        {
            index = index - _buffer.size();
        }
        std::cout << _buffer.at(index).description << std::endl;
    }
}

void Navigator::addListener(uint8_t id, Listener listener)
{
    ListenerList e;
    e.id = id;
    e.listener = listener;
    _listenerList.push_back(e);
}

void Navigator::addNotFoundListener(Listener listener)
{
    _notFoundListener = listener;
}

void Navigator::removeListener(uint8_t id)
{
    std::vector<ListenerList>::iterator _iterator;
    for(size_t i = 0; i < _listenerList.size(); i++)
    {
        _iterator = _listenerList.begin() + i;
        if(_listenerList.at(i).id == id)
        {
            if (_listenerList.at(i).listener != _activeListener) // to prevent erasing running function
            {
                _listenerList.erase(_iterator);
            }
            return;
        }
    }
}

void Navigator::printCursorPos()
{
    // std::cout << "Cursor Pos = " << unsigned(_cursorPos) << std::endl;
    // std::cout << "Screen Cursor Pos = " << unsigned(_screenCursorPos) << std::endl;
}


void Navigator::disableKeypad()
{
    _isKeypadDisabled = true;
}

void Navigator::enableKeypad()
{
    _isKeypadDisabled = false;
}

void Navigator::up()
{
    if (_buffer.size() <= 0 || _isInCustomEvent)
    {
        return;
    }
    if (_cursorPos == 0)
    {
        _cursorPos = _buffer.size() - 1;
        
    }
    else
    {
        _cursorPos--;
    }

    if (_buffer.size() <= _rowSize)
    {
        _screenCursorPos = _cursorPos;
    }
    else
    {
        if (_screenCursorPos == 0)
        {
            _screenCursorPos = 0;
        }
        else
        {
            _screenCursorPos--;
        }
    }  
    _isNeedUpdate = true;  
}

void Navigator::down()
{
    if (_buffer.size() <= 0 || _isInCustomEvent)
    {
        return;
    }
    if (_cursorPos == _buffer.size() - 1)
    {
        _cursorPos = 0;
    }
    else
    {
        _cursorPos++;
    }

    if (_buffer.size() <= _rowSize)
    {
        _screenCursorPos = _cursorPos;
    }
    else
    {
        if (_screenCursorPos == (_rowSize-1))
        {
            _screenCursorPos = _rowSize-1;
        }
        else
        {
            _screenCursorPos++;
        }
    }
    _isNeedUpdate = true;
}

void Navigator::back()
{
    if (_isKeypadDisabled)
    {
        return;
    }
    Content c = _buffer.at(_cursorPos);
    uint8_t id = c.id;
    _isNeedUpdate = true;
    _activeListener = nullptr;
    getContentById(id, c);
    if (!_isInCustomEvent) //if it is not from custom event
    {
        id = c.parentId; // 7 2 0, id = 2
    }
    _isInCustomEvent = false;
    // std::cout << "ID to find = " << (unsigned) id << std::endl;    
    if (getContentById(id,c)) //if found;
    {
        Cursor cursor = _cursorHistory.back();
        _cursorPos = cursor.cursorPos;
        _screenCursorPos = cursor.screenCursorPos;
        _cursorHistory.pop_back();
        // std::cout << "Parent Id to find = " << (unsigned)c.parentId << std::endl;
        getContentsByParentId(c.parentId);
    }
    else
    {
        _isNeedUpdate = false;
    }
}

void Navigator::ok()
{
    if (_isInCustomEvent || _isKeypadDisabled) // if it is still in custom event
    {
        return;
    }
    _isNeedUpdate = true;
    uint8_t id = _buffer.at(_cursorPos).id;
    Content c;
    Cursor cursor;
    // std::cout << "Id to find = " << (unsigned)id << std::endl;
    if (getContentById(id,c)) // if found
    {
        if (!c.endFlag) // if it is not the end of menu level
        {
            if (getContentsByParentId(c.id))
            {
                cursor.cursorPos = _cursorPos; // save the last cursor position
                cursor.screenCursorPos = _screenCursorPos; // save the last screen cursor position
                _cursorHistory.push_back(cursor); // save the cursor into cursor history
                _cursorPos = 0;
                _screenCursorPos = 0;
            }     
        }
        else // if end flag is true
        {
            // std::cout << "Custom Event" << std::endl;
            // std::cout << "Get the event" << std::endl;
            cursor.cursorPos = _cursorPos; // save the last cursor position
            cursor.screenCursorPos = _screenCursorPos; // save the last screen cursor position
            _cursorHistory.push_back(cursor); // save the cursor into cursor history
            _isInCustomEvent = true;
            _isNeedUpdate = false; // disable the update to prevent run method update the screen
            _activeListener = getEvent(c.id); // get the event
            if (_activeListener == nullptr) // if the event not found
            {
                // std::cout << "Event not found" << std::endl;
                // _isInCustomEvent = false; // set the flag event to false to prevent "run" method execute blank function pointer
            }
            else
            {
                // _isInCustomEvent = true;
            }
        }    
    }
    else // if id not found
    {
        // std::cout << "Not Found" << std::endl;
        _isNeedUpdate = false;
    }
}

Listener Navigator::getEvent(uint8_t id)
{
    for(size_t i = 0; i < _listenerList.size(); i++)
    {
        if(_listenerList.at(i).id == id)
        {
            return _listenerList.at(i).listener;
        }
    }
    return nullptr;
}

bool Navigator::getContentById(uint8_t id, Content &content)
{
    bool isFound = false;
    content = _error;
    for (size_t i = 0; i < _dataMenu.size() ; i++)
    {
        if (_dataMenu.at(i).id == id)
        {
            isFound = true;
            content = _dataMenu.at(i);
        }
    }
    return isFound;
}

bool Navigator::getContentsByParentId(uint8_t parentId)
{
    bool isFound = false;
    bool lastIsFound = false;
    for (size_t i = 0; i < _dataMenu.size(); i++)
    {
        if (_dataMenu.at(i).parentId == parentId)
        {
            isFound = true;
            if (lastIsFound != isFound)
            {
                _buffer.clear();
                lastIsFound = isFound;
            }
            _buffer.push_back(_dataMenu.at(i));
        }
    }
    return isFound;
}

Navigator::~Navigator()
{

}