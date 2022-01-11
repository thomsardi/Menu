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
        Navigator(uint8_t col, uint8_t row); // class constructor
        void run(); // Run the class
        void addListener(uint8_t id, Event event); // add listener of class
        void removeListener(uint8_t); // remove listener of class
        void setMenu(const DataList &content); // get the DataList from outside class
        void setArrow(bool enabled = true); // set the custom arrow character
        void print(); // print the menu
        void up(); // cursor up
        void down(); // cursor down
        void back(); // cursor back
        void ok(); // cursor ok
        void disableKeypad();
        void enableKeypad();
        void printCursorPos(); // print current cursor position
        ~Navigator(); // class destructor
    private:
        
        // void printList(std::ostream &os); //std::ostream used to test on native environment

        // Private Class Method
        void printList(const DataList &_buffer);
        Event getEvent(uint8_t id);
        bool getContentsByParentId(uint8_t parentId);
        bool getContentById(uint8_t id, Content &content);
        
        // Struct and vector data type
        Event _activeEvent = nullptr; // function pointer to void function
        Content _error = {99,99,1, "Not Found"};
        DataList _dataMenu;
        DataList _buffer;
        const DataList *_contentptr = nullptr;
        std::vector<EventList> _eventList; // vector of EventList
        std::vector<Cursor> _cursorHistory; // vector of Cursor
        
        // primitive data type
        uint8_t _currentCursorPos = 0;
        uint8_t _cursorPos = 0;
        uint8_t _screenCursorPos = 0;
        uint8_t _rowSize;
        uint8_t _colSize;
        bool _isArrowEnabled;
        bool _isInCustomEvent;
        bool _isNeedUpdate;
        bool _isKeypadDisabled;
};

#endif