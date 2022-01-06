#include <Menu.h>

Menu::Menu()
{

}

void Menu::convertToMenu(const char* csv)
{
    std::vector<std::string> rowList;
    std::string stringCsv(csv);
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
            std::cout << content[rows].id << " ";
            std::cout << content[rows].parentId << " ";
            std::cout << content[rows].description << std::endl;
            rows++;
        }
    }
}

void Menu::getContentsByParentId(uint8_t parentId, std::vector<Content> &content)
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

void Menu::splitIntoRows(std::string csv, const char* delimiter, std::vector<std::string> &rowList)
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

void Menu::splitIntoColumns(std::string csv, const char* delimiter)
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

std::vector<Content>Menu::getVector()
{
    return _content;
}

void Menu::printVectorContent(const std::vector<Content> &content)
{
    for (size_t i = 0; i < content.size(); i++)
    {
        std::cout << unsigned(content.at(i).id) << " ";
        std::cout << unsigned(content.at(i).parentId) << " ";
        std::cout << content.at(i).endFlag << " ";
        std::cout << content.at(i).description << std::endl;
    }
}

Menu::~Menu()
{

}