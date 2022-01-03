#ifndef DataDef_H
#define DataDef_H

#include <stdint.h>

struct Content {
    uint8_t id;
    uint8_t parentId;
    bool endFlag;
    char description[32];
};

#endif