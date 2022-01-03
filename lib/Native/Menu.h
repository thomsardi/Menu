#ifndef Menu_H
#define Menu_H

#include <vector>
#include <DataDef.h>
#include <stdio.h>
#include <string.h>
#include <iostream>

class Menu {
    public:
        Menu();
        void convertToMenu(const char* csv);
        void getContentsByParentId(uint8_t parentId, Content content[]);
        void getContentsByParentId(uint8_t parentId, std::vector<Content> &content);
        void printVectorContent(const std::vector<Content> &content);
        std::vector<Content> getVector();
        size_t getRowSize();
        Content getContentById(uint8_t id);
        ~Menu();
    private:
        void splitIntoRows(std::string csv, const char* delimiter, std::vector<std::string> &rowList);
        void splitIntoColumns(std::string csv, const char* delimiter);
        std::vector<Content> _content;        
};

#endif