#include <Arduino.h>
#include <unity.h>
#include <MenuEmbedded.h>
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

LiquidCrystal_I2C lcd;

void dummy_test()
{
    Menu myMenu;
    myMenu.convertToMenu(csv);
    Content storage[64];
    Vector<Content> buffer(storage);
    TEST_ASSERT_EQUAL(18, 18);
}

void dummy_test2()
{
    Menu myMenu;
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
    Menu myMenu;
    myMenu.convertToMenu(csv);
    // myMenu.printVectorContent(Serial, myMenu.getVector());
    TEST_ASSERT_EQUAL(18, myMenu.getVector().size());
}


void test_get_content_id()
{
    Content content;
    Menu myMenu;
    myMenu.convertToMenu(csv);
    content = myMenu.getContentById(18);
    TEST_ASSERT_EQUAL(18, content.id);
    TEST_ASSERT_EQUAL(7, content.parentId);
    TEST_ASSERT_EQUAL(1, content.endFlag);
    TEST_ASSERT_EQUAL_STRING("Sub Sub Menu 2.4", content.description);
}

void test_parent_id()
{
    Menu myMenu;
    myMenu.convertToMenu(csv);
    Content storageArray[32];
    Vector<Content> buffer(storageArray);
    myMenu.getContentsByParentId(1, buffer); // this will cause the reset on device
    TEST_ASSERT_EQUAL(3, buffer.at(0).id);
    TEST_ASSERT_EQUAL(1, buffer.at(0).parentId);
    TEST_ASSERT_EQUAL(0, buffer.at(0).endFlag);
    TEST_ASSERT_EQUAL_STRING("Sub Menu 1.1", buffer.at(0).description);
}

void setup() {
    // NOTE!!! Wait for >2 secs
    // if board doesn't support software reset via Serial.DTR/RTS
    delay(2000);
    UNITY_BEGIN();    // IMPORTANT LINE!
    RUN_TEST(dummy_test);
    RUN_TEST(dummy_test2);
    RUN_TEST(dummy_test3);
    RUN_TEST(test);
    RUN_TEST(test_get_content_id);
    RUN_TEST(test_parent_id);
    UNITY_END();
}


void loop() {

   
}