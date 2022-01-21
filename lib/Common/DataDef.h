#ifndef DataDef_H
#define DataDef_H

#include <stdint.h>

typedef void (*Listener)();

struct Content {
    uint8_t id;
    uint8_t parentId;
    bool endFlag;
    char description[32];
};

struct Cursor {
    uint8_t cursorPos;
    uint8_t screenCursorPos;
};

struct ListenerList {
    uint8_t id;
    Listener listener;
};

#endif