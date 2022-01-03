#include <unity.h>
#include <iostream>
#include <string.h>
#include <Menu.h>
#include <vector>
#include <Navigator.h>

const char* csv = R"LONGSTRING(1;0;0;Menu 1
2;0;0;Menu 2
3;1;0;Sub Menu 1.1
4;1;0;Sub Menu 1.2
5;1;0;Sub Menu 1.3
6;1;0;Sub Menu 1.4
7;2;0;Sub Menu 2.1
8;2;0;Sub Menu 2.2
9;2;0;Sub Menu 2.3
10;2;0;Sub Menu 2.4
11;3;1;Sub Sub Menu 1.1
12;3;1;Sub Sub Menu 1.2
13;3;1;Sub Sub Menu 1.3
14;3;1;Sub Sub Menu 1.4
15;7;1;Sub Sub Menu 2.1
16;7;1;Sub Sub Menu 2.2
17;7;1;Sub Sub Menu 2.3
18;7;1;Sub Sub Menu 2.4)LONGSTRING";

void test()
{
    std::cout << "convert test" << std::endl;
    Menu myMenu;
    myMenu.convertToMenu(csv);
    TEST_ASSERT_EQUAL(18, myMenu.getVector().size());
}

void test_get_content_id()
{
    std::cout << "test id" << std::endl;
    Content content;
    Menu myMenu;
    myMenu.convertToMenu(csv);
    content = myMenu.getContentById(18);
    TEST_ASSERT_EQUAL(18, content.id);
    TEST_ASSERT_EQUAL(7, content.parentId);
    TEST_ASSERT_EQUAL(1, content.endFlag);
    TEST_ASSERT_EQUAL_STRING("Sub Sub Menu 2.4", content.description);
}

void test_get_contents_parent_id()
{
    std::cout << "test parent id" << std::endl;
    std::vector<Content> testContent;
    Menu myMenu;
    myMenu.convertToMenu(csv);
    myMenu.getContentsByParentId(1, testContent);
    TEST_ASSERT_EQUAL(3, testContent.at(0).id);
    TEST_ASSERT_EQUAL(1, testContent.at(0).parentId);
    TEST_ASSERT_EQUAL(0, testContent.at(0).endFlag);
    TEST_ASSERT_EQUAL_STRING("Sub Menu 1.1", testContent.at(0).description);
}

void test_navigator_down()
{
    std::cout << "test navigator down" << std::endl;
    std::vector<Content> testContent;
    Menu myMenu;
    myMenu.convertToMenu(csv);
    myMenu.getContentsByParentId(1, testContent);
    Navigator navigator(20, 4);
    navigator.setMenu(testContent);
    // navigator.show();
    navigator.showScreen();
    navigator.printCursorPos();
    std::cout << "===============" << std::endl;
    navigator.down();
    // navigator.show();
    navigator.showScreen();
    navigator.printCursorPos();
    std::cout << "===============" << std::endl;
    navigator.down();
    // navigator.show();
    navigator.showScreen();
    navigator.printCursorPos();
    std::cout << "===============" << std::endl;
    navigator.down();
    // navigator.show();
    navigator.showScreen();
    navigator.printCursorPos();
    std::cout << "===============" << std::endl;
    navigator.down();
    // navigator.show();
    navigator.showScreen();
    navigator.printCursorPos();
    std::cout << "===============" << std::endl;
}

void test_navigator_up()
{
    std::cout << "test navigator up" << std::endl;
    std::vector<Content> testContent;
    Menu myMenu;
    myMenu.convertToMenu(csv);
    myMenu.getContentsByParentId(1, testContent);
    Navigator navigator(20, 4);
    navigator.setMenu(testContent);
    // navigator.show();
    navigator.showScreen();
    navigator.printCursorPos();
    std::cout << "===============" << std::endl;
    navigator.up();
    // navigator.show();
    navigator.showScreen();
    navigator.printCursorPos();
    std::cout << "===============" << std::endl;
    navigator.up();
    // navigator.show();
    navigator.showScreen();
    navigator.printCursorPos();
    std::cout << "===============" << std::endl;
    navigator.up();
    // navigator.show();
    navigator.showScreen();
    navigator.printCursorPos();
    std::cout << "===============" << std::endl;
    navigator.up();
    // navigator.show();
    navigator.showScreen();
    navigator.printCursorPos();
    std::cout << "===============" << std::endl;
}

void test_navigator_up_down()
{
    std::cout << "test navigator up down" << std::endl;
    std::vector<Content> testContent;
    Menu myMenu;
    myMenu.convertToMenu(csv);
    myMenu.getContentsByParentId(1, testContent);
    Navigator navigator(20, 4);
    navigator.setMenu(testContent);
    // navigator.show();
    navigator.showScreen();
    navigator.printCursorPos();
    std::cout << "===============" << std::endl;
    navigator.up();
    // navigator.show();
    navigator.showScreen();
    navigator.printCursorPos();
    std::cout << "===============" << std::endl;
    navigator.down();
    // navigator.show();
    navigator.showScreen();
    navigator.printCursorPos();
    std::cout << "===============" << std::endl;
    navigator.down();
    // navigator.show();
    navigator.showScreen();
    navigator.printCursorPos();
    std::cout << "===============" << std::endl;
    navigator.down();
    // navigator.show();
    navigator.showScreen();
    navigator.printCursorPos();
    std::cout << "===============" << std::endl;
    navigator.down();
    // navigator.show();
    navigator.showScreen();
    navigator.printCursorPos();
    std::cout << "===============" << std::endl;
    navigator.down();
    // navigator.show();
    navigator.showScreen();
    navigator.printCursorPos();
    std::cout << "===============" << std::endl;
    for (int i = 0; i < 4; i++)
    {
        navigator.up();
        // navigator.show();
        navigator.showScreen();
        navigator.printCursorPos();
        std::cout << "===============" << std::endl;
    }
}

void test_print_after_before()
{
    std::cout << "test navigator" << std::endl;
    std::vector<Content> testContent;
    Menu myMenu;
    myMenu.convertToMenu(csv);
    myMenu.getContentsByParentId(1, testContent);
    Navigator navigator(20, 4);
    navigator.setMenu(testContent);
    navigator.printAfterCursor(0);
    std::cout << "Print After" << std::endl;
    std::cout << "==================" << std::endl;
    navigator.printAfterCursor(1);
    std::cout << "==================" << std::endl;
    navigator.printAfterCursor(2);
    std::cout << "==================" << std::endl;
    navigator.printAfterCursor(3);
    std::cout << "==================" << std::endl;
    std::cout << "Print Before" << std::endl;
    navigator.printBeforeCursor(0);
    std::cout << "==================" << std::endl;
    navigator.printBeforeCursor(1);
    std::cout << "==================" << std::endl;
    navigator.printBeforeCursor(2);
    std::cout << "==================" << std::endl;
    navigator.printBeforeCursor(3);
    std::cout << "==================" << std::endl;

}

void test_print_around_cursor()
{
    std::cout << "test navigator" << std::endl;
    std::vector<Content> testContent;
    Menu myMenu;
    myMenu.convertToMenu(csv);
    myMenu.getContentsByParentId(1, testContent);
    Navigator navigator(20, 4);
    navigator.setMenu(testContent);
    std::cout << "Print Around Cursor" << std::endl;
    navigator.printAroundCursor(0, 3);
    std::cout << "==================" << std::endl;
    std::cout << "Print Around Cursor" << std::endl;
    navigator.printAroundCursor(3, 3);
    std::cout << "==================" << std::endl;
}


int main(int argc, char **argv) {
    UNITY_BEGIN();
    // RUN_TEST(test);
    // RUN_TEST(test_get_content_id);
    // RUN_TEST(test_get_contents_parent_id);
    // RUN_TEST(test_navigator_down);
    // RUN_TEST(test_navigator_up);
    RUN_TEST(test_navigator_up_down);
    // RUN_TEST(test_print_after_before);
    // RUN_TEST(test_print_around_cursor);
    UNITY_END();
    std::cout << "test finished" << std::endl;
    return 0;
}