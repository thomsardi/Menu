#ifndef MenuEmbedded_H
#define MenuEmbedded_H

#define _MAX_ELEMENT_ 64

#include <Arduino.h>
#include <Vector.h>
#include <DataDef.h>

class Menu {
    public:
        Menu();
        void convertToMenu(const char* csv);
        void getContentsByParentId(uint8_t parentId, Content content[]);
        void getContentsByParentId(uint8_t parentId, Vector<Content> &content);
        void printVectorContent(HardwareSerial &serial, const Vector<Content> &content);
        Vector<Content> getVector();
        size_t getRowSize();
        Content getContentById(uint8_t id);
        ~Menu();
    private:
        void splitIntoRows(String csv, const char* delimiter, Vector<String> &rowList);
        void splitIntoColumns(String csv, const char* delimiter);
        Content _storageArray[_MAX_ELEMENT_];
        Content _storageBuffer[_MAX_ELEMENT_];
        Vector<Content> _content;
};

#endif