#ifndef Navigator_H
#define Navigator_H

#include <stdint.h>
#include <DataDef.h>

#ifdef Arduino_h
    #include <Vector.h>
    #include <MenuEmbedded.h>
    typedef Vector<Content> DataList;
#else
    #include <Menu.h>
    #include <cstdlib>
    #include <iostream>
    typedef std::vector<Content> DataList;
#endif

class Navigator {
    public:
        Navigator(uint8_t col, uint8_t row);
        void setMenu(const DataList &content);
        void setArrow(bool enabled = true);
        void show();
        void print();
        void up();
        void down();
        void back();
        void ok();
        void printCursorPos();
        ~Navigator();
    private:
        void updateScreen();
        // void printList(std::ostream &os); //std::ostream used to test on native environment        
        void printList();
        Content getContentById(uint8_t id);
        void getContentsByParentId(uint8_t parentId);
        const DataList *_contentptr = nullptr;
        DataList _buffer;
        uint8_t _currentCursorPos = 0;
        uint8_t _cursorPos = 0;
        uint8_t _screenCursorPos = 0;
        uint8_t _rowSize;
        uint8_t _colSize;
        bool _isArrowEnabled;
};

#endif