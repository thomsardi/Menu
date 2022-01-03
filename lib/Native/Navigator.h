#ifndef Navigator_H
#define Navigator_H

#include <stdint.h>
#include <Menu.h>
#include <DataDef.h>
#include <iostream>
#include <cstdlib>

class Navigator {
    public:
        Navigator(uint8_t col, uint8_t row);
        void setMenu(const std::vector<Content> &content);
        void setArrow(bool enabled = true);
        void show();
        void showScreen();
        void up();
        void down();
        void back();
        void ok();
        void printCursorPos();
        void printBeforeCursor(uint8_t cursorPos);
        void printAfterCursor(uint8_t cursorPos);
        void printAroundCursor(uint8_t screenCursorPos, uint8_t cursorPos);
        ~Navigator();
    private:
        void updateScreen();        
        bool isTopOut();
        bool isBottomOut();
        const std::vector<Content> *_contentptr = nullptr;
        Content _content;
        uint8_t _currentCursorPos = 0;
        uint8_t _cursorPos = 0;
        uint8_t _screenCursorPos = 0;
        uint8_t _rowSize;
        uint8_t _colSize;
        uint8_t _topLimit;
        uint8_t _bottomLimit;
        bool _isArrowEnabled;
        bool _isTopOut = false;
        bool _isBottomOut = false;
};

#endif