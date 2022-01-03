#include <Navigator.h>

Navigator::Navigator(uint8_t col, uint8_t row)
{
    _colSize = col;
    _rowSize = row;
    _screenCursorPos = _cursorPos;
}

void Navigator::setMenu(const std::vector<Content> &content)
{
    _contentptr = &content;
}

void Navigator::setArrow(bool enabled)
{
    _isArrowEnabled = enabled;
}

void Navigator::show()
{
    if (_contentptr == nullptr)
    {
        return;
    }
    for (int i = 0; i < _rowSize; i ++)
    {
        if (i == _screenCursorPos)
        {
            std::cout << ">";
        }
        else
        {
            std::cout << ".";
        }
        if (_cursorPos+i >= _contentptr->size())
        {
            int index = (_cursorPos + i) - _contentptr->size();
            std::cout << _contentptr->at(index).description << std::endl;    
        }
        else
        {
            int index = _cursorPos + i;
            std::cout << _contentptr->at(index).description << std::endl;
        }    
    }

}

void Navigator::showScreen()
{
    if (_contentptr == nullptr)
    {
        return;
    }
    for (int i = 0; i < _rowSize; i ++)
    {
        if (i == _screenCursorPos)
        {
            std::cout << ">";
        }
        else
        {
            std::cout << " ";
        }

        if (_isTopOut)
        {    
            // Print after cursor
            int index = _cursorPos + i;
            if (index >= _contentptr->size())
            {
                index = index - _contentptr->size();
            }
            std::cout << _contentptr->at(index).description << std::endl;            
        }
        else if (_isBottomOut)
        {
            // Print befor cursor
            int index = (_cursorPos - (_rowSize - 1)) + i;
            if (index < 0 )
            {
                index = _contentptr->size() - abs(index);
            }
            std::cout << _contentptr->at(index).description << std::endl;
        }
        else
        {
            // Print around cursor
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
}

void Navigator::printBeforeCursor(uint8_t cursorPos)
{
    for (int i = 0; i < _rowSize; i++)
    {
        if (i == _screenCursorPos)
        {
            std::cout << ">";
        }
        else
        {
            std::cout << " ";
        }
        int index = (cursorPos - (_rowSize - 1)) + i;
        if (index < 0 )
        {
            index = _contentptr->size() - abs(index);
        }
        std::cout << _contentptr->at(index).description << std::endl;
    }
}

void Navigator::printAfterCursor(uint8_t cursorPos)
{
    for (int i = 0; i < _rowSize; i++)
    {
        if (i == _screenCursorPos)
        {
            std::cout << ">";
        }
        else
        {
            std::cout << " ";
        }
        int index = cursorPos + i;
        if (index >= _contentptr->size())
        {
            index = index - _contentptr->size();
        }
        std::cout << _contentptr->at(index).description << std::endl;
    }
}

void Navigator::printAroundCursor(uint8_t screenCursorPos, uint8_t cursorPos)
{
    for (int i = 0; i < _rowSize; i++)
    {
        if (i == _screenCursorPos)
        {
            std::cout << ">";
        }
        else
        {
            std::cout << " ";
        }
        int index = (cursorPos - screenCursorPos) + i;
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
    _isTopOut = false;
    _isBottomOut = false;
    if (_screenCursorPos == 0)
    {
        _isTopOut = true;
        _screenCursorPos = 0;
    }
    else
    {
        _screenCursorPos--;
    }

    if (_cursorPos == 0)
    {
        _cursorPos = _contentptr->size() - 1;
        
    }
    else
    {
        _cursorPos--;
    }
}

void Navigator::down()
{
    if (_contentptr == nullptr)
    {
        return;
    }
    _isBottomOut = false;
    _isTopOut = false;
    if (_screenCursorPos == (_rowSize-1))
    {
        _isBottomOut = true;
        _screenCursorPos = _rowSize-1;
    }
    else
    {
        _screenCursorPos++;
    }
    
    if (_cursorPos == _contentptr->size() - 1)
    {
        _cursorPos = 0;
    }
    else
    {
        _cursorPos++;
    }
}

void Navigator::back()
{

}

void Navigator::ok()
{

}

Navigator::~Navigator()
{

}