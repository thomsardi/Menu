#include <MenuEmbedded.h>

Menu::Menu()
{
    _content.setStorage(_storageArray);
}

void Menu::convertToMenu(const char* csv)
{
    String storageArray[_MAX_ELEMENT_];
    Vector<String> rowList(storageArray);
    String stringCsv(csv);
    splitIntoRows(stringCsv, "\n", rowList);
    for (size_t i = 0; i < rowList.size(); i++)
    {
        size_t arraySize = rowList.at(i).length();
        char buffer[arraySize+1]; 
        strcpy(buffer, rowList.at(i).c_str());
        splitIntoColumns(buffer, ";");
    }
}

Content Menu::getContentById(uint8_t id)
{
    Content content;
    for (size_t i = 0; i < _content.size(); i++)
    {
        if (_content.at(i).id == id)
        {
            content = _content.at(i);
            return content;
        }
    }
    return content;
}

void Menu::getContentsByParentId(uint8_t parentId, Content content[])
{
    uint8_t rows = 0;
    for (size_t i = 0; i < _content.size(); i++)
    {
        if (_content.at(i).parentId == parentId)
        {
            content[rows] = _content.at(i);
            rows++;
        }
    }
}

void Menu::getContentsByParentId(uint8_t parentId, Vector<Content> &content)
{
    content.clear();
    for (size_t i = 0; i < _content.size(); i++)
    {
        if (_content.at(i).parentId == parentId)
        {
            content.push_back(_content.at(i));
        }
    }
}

void Menu::splitIntoRows(String csv, const char* delimiter, Vector<String> &rowList)
{
    size_t arraySize = csv.length();
    char buffer[arraySize+1];
    strcpy(buffer, csv.c_str());
    char* pch;
    pch = strtok (buffer, delimiter);
    while (pch != NULL)
    {
        rowList.push_back(pch);
        pch = strtok (NULL, delimiter);
    }
}

void Menu::splitIntoColumns(String csv, const char* delimiter)
{
    Content content;
    size_t arraySize = csv.length();
    char buffer[arraySize+1];
    strcpy(buffer, csv.c_str());
    uint8_t i = 0;
    char *pch;
    pch = strtok (buffer, delimiter);
    while (pch != NULL)
    {
        switch (i)
        {
            case 0 :
                content.id = atoi(pch);
                break;
            case 1 :
                content.parentId = atoi(pch);
                break;
            case 2 :
                content.endFlag = atoi(pch);
                break;
            case 3 :
                strcpy(content.description, pch);
                _content.push_back(content);
                break;
        }
        i++;
        pch = strtok (NULL, delimiter);
    }
}

Vector<Content>Menu::getVector()
{
    return _content;
}

void Menu::printVectorContent(HardwareSerial &serial, const Vector<Content> &content)
{
    for (size_t i = 0; i < content.size(); i++)
    {
        serial.print(content.at(i).id); 
        serial.print(" ");
        serial.print(content.at(i).parentId); 
        serial.print(" ");
        serial.print(content.at(i).endFlag); 
        serial.print(" ");
        serial.println(content.at(i).description); 
    }
}

Menu::~Menu()
{

}