#include <Arduino.h>
#include <unity.h>
#include <MenuEmbedded.h>
#include <NavigatorEmbedded.h>
#include <Vector.h>
#include <LiquidCrystal_I2C.h>

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

void dummy_test()
{
    MenuEmbedded myMenu;
    myMenu.convertToMenu(csv);
    Content storage[64];
    Vector<Content> buffer(storage);
    TEST_ASSERT_EQUAL(18, 18);
}

void dummy_test2()
{
    MenuEmbedded myMenu;
    myMenu.convertToMenu(csv);
    Content storage[64];
    Vector<Content> buffer(storage);
    TEST_ASSERT_EQUAL(18, 18);
}

void dummy_test3()
{
    Content storage1 = {1, 2, 0, "storage 1"};
    Content storage2 = storage1;
    Serial.print(storage2.id);
    Serial.print(" ");
    Serial.print(storage2.parentId);
    Serial.print(" ");
    Serial.print(storage2.endFlag);
    Serial.print(" ");
    Serial.println(storage2.description);
    TEST_ASSERT_EQUAL(storage1.id, storage2.id);
    TEST_ASSERT_EQUAL(storage1.parentId, storage2.parentId);
    TEST_ASSERT_EQUAL(storage1.endFlag, storage2.endFlag);
    TEST_ASSERT_EQUAL_STRING(storage1.description, storage2.description);
}

void test()
{
    MenuEmbedded myMenu;
    myMenu.convertToMenu(csv);
    // myMenu.printVectorContent(Serial, myMenu.getVector());
    TEST_ASSERT_EQUAL(18, myMenu.getVector().size());
}


void test_get_content_id()
{
    Content content;
    MenuEmbedded myMenu;
    myMenu.convertToMenu(csv);
    content = myMenu.getContentById(18);
    TEST_ASSERT_EQUAL(18, content.id);
    TEST_ASSERT_EQUAL(7, content.parentId);
    TEST_ASSERT_EQUAL(1, content.endFlag);
    TEST_ASSERT_EQUAL_STRING("Sub Sub Menu 2.4", content.description);
}

void test_parent_id()
{
    MenuEmbedded myMenu;
    myMenu.convertToMenu(csv);
    Content storageArray[32];
    Vector<Content> buffer(storageArray);
    myMenu.getContentsByParentId(1, buffer); // this will cause the reset on device
    TEST_ASSERT_EQUAL(3, buffer.at(0).id);
    TEST_ASSERT_EQUAL(1, buffer.at(0).parentId);
    TEST_ASSERT_EQUAL(0, buffer.at(0).endFlag);
    TEST_ASSERT_EQUAL_STRING("Sub Menu 1.1", buffer.at(0).description);
}

void my_custom_event()
{
    Serial.println("You are now in custom event");
    for (int i = 0; i < 50; i ++)
    {
        Serial.print("iteration = ");
        Serial.println(i);
    }
}

void my_custom_event1()
{
    Serial.println("You are now in custom event1");
    for (int i = 0; i < 100; i ++)
    {
        Serial.print("iteration = ");
        Serial.println(i);
    }
}

void test_simple()
{
    Serial.println("Simple Test");
    MenuEmbedded myMenu;
    myMenu.convertToMenu(csv);
    myMenu.printVectorContent(Serial, myMenu.getVector());
    NavigatorEmbedded navigator(20,2, &Serial);
    navigator.setMenu(myMenu.getVector());
    navigator.addListener(15, my_custom_event);
    Serial.println("Print Main Menu");
    navigator.run();
}

void test_navigator_custom_event()
{
    Serial.println("test navigator custom event");
    MenuEmbedded myMenu;
    myMenu.convertToMenu(csv);
    NavigatorEmbedded navigator(20, 2, &Serial);
    navigator.setMenu(myMenu.getVector());
    navigator.addListener(15, my_custom_event);
    navigator.addListener(11, my_custom_event1);
    Serial.println("Print Main Menu");
    navigator.run();
    navigator.printCursorPos();
    //navigator.stop();
    Serial.println("===============");
    Serial.println("Cursor Down");
    navigator.down();
    navigator.run();
    navigator.printCursorPos();
    Serial.println("===============");
    Serial.println("Ok Button");
    navigator.ok();
    navigator.run();
    navigator.printCursorPos();
    Serial.println("===============");
    Serial.println("Ok Button");
    navigator.ok();
    navigator.run();
    navigator.printCursorPos();
    Serial.println("===============");
    Serial.println("Ok Button");
    navigator.ok();
    navigator.run();
    navigator.ok();
    navigator.up();
    navigator.down();
    navigator.printCursorPos();
    Serial.println("===============");
    // navigator.run();
    Serial.println("===============");
    navigator.back();
    navigator.run();
    Serial.println("===============");
    navigator.back();
    navigator.run();
    Serial.println("===============");
    navigator.back();
    navigator.run();
    Serial.println("===============");
    navigator.back();
    navigator.run();
    Serial.println("===============");
}

void setup() {
    // NOTE!!! Wait for >2 secs
    // if board doesn't support software reset via Serial.DTR/RTS
    delay(2000);
    UNITY_BEGIN();    // IMPORTANT LINE!
    // RUN_TEST(dummy_test);
    // RUN_TEST(dummy_test2);
    // RUN_TEST(dummy_test3);
    // RUN_TEST(test);
    // RUN_TEST(test_get_content_id);
    // RUN_TEST(test_parent_id);
    RUN_TEST(test_navigator_custom_event);
    // RUN_TEST(test_simple);
    UNITY_END();
}


void loop() {

   
}