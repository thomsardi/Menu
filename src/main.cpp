#include <Arduino.h>
#include <MenuEmbedded.h>

Menu myMenu;
Content tempStorage[16];
Vector<Content> buffer(tempStorage);

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

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  delay(2000);
  myMenu.convertToMenu(csv);
  myMenu.printVectorContent(Serial, myMenu.getVector());
  Serial.println("===================");
  myMenu.getContentsByParentId(7, buffer);
  myMenu.printVectorContent(Serial, buffer);
}

void loop() {
  // put your main code here, to run repeatedly:
  // Serial.println("loop");
  
  delay(1);
}