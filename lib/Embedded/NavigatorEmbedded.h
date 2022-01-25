#ifndef NavigatorEmbedded_H
#define NavigatorEmbedded_H

#define MAX_NAVIGATOR_MENU_LIST 64
#define MAX_NAVIGATOR_MENU_LEVEL 16
#define MAX_LISTENER 16
#define MAX_ROW 16

#include <stdint.h>
#include <DataDef.h>
#include <Arduino.h>

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

class NavigatorEmbedded {
    public:
        NavigatorEmbedded(uint8_t col, uint8_t row, Stream *stream); // class constructor
        void run(); // Run the class
        // void setPrinterOutput(Print *print);
        void addListener(uint8_t id, Listener listener); // add listener of class
        void addNotFoundListener(Listener listener);
        void removeListener(uint8_t); // remove listener of class
        void setMenu(const DataList &content); // get the DataList from outside class
        void print(); // print the menu
        void up(); // cursor up
        void down(); // cursor down
        void back(); // cursor back
        void ok(); // cursor ok
        void disableKeypad();
        void enableKeypad();
        void printCursorPos(); // print current cursor position
        void stop();
        ~NavigatorEmbedded(); // class destructor
    private:
        
        // void printList(std::ostream &os); //std::ostream used to test on native environment

        // Private Class Method
        void printList(const DataList &_buffer);
        Listener getEvent(uint8_t id);
        bool getContentsByParentId(uint8_t parentId);
        bool getContentById(uint8_t id, Content &content);
        
        // Struct and vector data type
        Listener _activeListener = nullptr; // function pointer to void function
        Listener _notFoundListener = nullptr; // function pointer for not found listener
        Content _error = {99,99,1, "Not Found"};

        // storage array for vector
        Content _dataMenuStorage[MAX_NAVIGATOR_MENU_LIST];
        Content _bufferStorage[MAX_NAVIGATOR_MENU_LIST];
        ListenerList _listenerListStorage[MAX_LISTENER];
        Cursor _cursorHistoryStorage[MAX_NAVIGATOR_MENU_LEVEL];

        DataList _dataMenu; // vector of Content
        DataList _buffer; // vector of Content
        Vector<ListenerList> _listenerList; // vector of EventList
        Vector<Cursor> _cursorHistory; // vector of Cursor
        
        Stream *_stream;

        // primitive data type
        uint8_t _currentCursorPos = 0;
        uint8_t _cursorPos = 0;
        uint8_t _screenCursorPos = 0;
        uint8_t _rowSize;
        uint8_t _colSize;
        bool _isArrowEnabled;
        bool _isInCustomEvent = false;
        bool _isNeedUpdate = false;
        bool _isKeypadDisabled = false;
        bool _isStop = false;
};

#endif