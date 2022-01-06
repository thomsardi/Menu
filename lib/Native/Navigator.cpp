#include <Navigator.h>

Navigator::Navigator(uint8_t col, uint8_t row)
{
    _colSize = col;
    _rowSize = row;
    _screenCursorPos = _cursorPos;
}

void Navigator::setMenu(const DataList &content)
{
    _contentptr = &content;
}

void Navigator::setArrow(bool enabled)
{
    _isArrowEnabled = enabled;
}

void Navigator::print()
{
    if (_contentptr == nullptr)
    {
        return;
    }
    // printList(std::cout);
    printList();
}

/*
void Navigator::printList(std::ostream &os)
{
    int rows = _rowSize;
    if (_contentptr->size() <= _rowSize)
    {
        rows = _contentptr->size();
    }
    
    for (int i = 0; i < rows; i++)
    {
        if (i == _screenCursorPos)
        {
            // std::cout << ">";
            os << ">";
        }
        else
        {
            // std::cout << ".";
            os << ".";
        }
        int index = (_cursorPos - _screenCursorPos) + i;
        if (index < 0)
        {
            index = _contentptr->size() - abs(index);
        }

        else if (index >= _contentptr->size())
        {
            index = index - _contentptr->size();
        }
        // std::cout << _contentptr->at(index).description << std::endl;
        os << _contentptr->at(index).description << '\n'; 
        os.flush();
        // std::cout << '\n' << std::flush;
    }
}
*/

void Navigator::printList()
{
    int rows = _rowSize;
    if (_contentptr->size() <= _rowSize)
    {
        rows = _contentptr->size();
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
            index = _contentptr->size() - abs(index);
        }

        else if (index >= _contentptr->size())
        {
            index = index - _contentptr->size();
        }
        std::cout << _contentptr->at(index).description << std::endl;
    }
}


void Navigator::updateScreen()
{

}


void Navigator::printCursorPos()
{
    std::cout << "Cursor Pos = " << unsigned(_cursorPos) << std::endl;
    std::cout << "Screen Cursor Pos = " << unsigned(_screenCursorPos) << std::endl;
}

void Navigator::up()
{
    if (_contentptr == nullptr)
    {
        return;
    }
    if (_cursorPos == 0)
    {
        _cursorPos = _contentptr->size() - 1;
        
    }
    else
    {
        _cursorPos--;
    }

    if (_contentptr->size() <= _rowSize)
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
}

void Navigator::down()
{
    if (_contentptr == nullptr)
    {
        return;
    }
    if (_cursorPos == _contentptr->size() - 1)
    {
        _cursorPos = 0;
    }
    else
    {
        _cursorPos++;
    }

    if (_contentptr->size() <= _rowSize)
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
}

void Navigator::back()
{

}

void Navigator::ok()
{

}


Content Navigator::getContentById(uint8_t id)
{
    Content content;
    for (size_t i = 0; i < _contentptr->size() ; i++)
    {
        if (_contentptr->at(i).id == id)
        {
            content = _contentptr->at(i);
        }
    }
    return content;
}

void Navigator::getContentsByParentId(uint8_t parentId)
{
    _buffer.clear();
    for (size_t i = 0; i < _contentptr->size(); i++)
    {
        if (_contentptr->at(i).parentId == parentId)
        {
            _buffer.push_back(_contentptr->at(i));
        }
    }
}

Navigator::~Navigator()
{

}