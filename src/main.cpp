#include <Arduino.h>
#include <MenuEmbedded.h>
#include <LiquidCrystal_I2C.h>
#include <NavigatorEmbedded.h>

NavigatorEmbedded navigator(20,2);
int iteration = 0;
String readBuffer;
bool stringReady = false;

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

const char* menuTest = R"LONGSTRING(1;0;0;Status
2;0;0;Parameter
3;1;1;Event Status
4;2;0;Blink Delay
5;2;0;Pid Tuning
6;2;0;Interval
7;4;1;Event Blink
8;5;0;Kp
9;5;0;Ki
10;5;0;Kd
11;6;1;Event Interval
12;8;1;Event Kp
13;9;1;Event Ki
14;10;1;Event Kd)LONGSTRING";

void my_custom_event()
{
  Serial.print("iteration = ");
  Serial.println(iteration);
  iteration++;
}

void event_status()
{
  Serial.println("this is status event");
}

void event_blink()
{
  Serial.println("this is blink event");
}

void event_interval()
{
  Serial.println("this is interval event");
}

void event_kp()
{
  Serial.println("this is kp event");
}

void event_ki()
{
  Serial.println("this is ki event");
}

void event_kd()
{
  Serial.println("this is kd event");
}

void notFound()
{
  Serial.println("Listener Not Found");
}

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  delay(2000);
  MenuEmbedded myMenu;
  // myMenu.convertToMenu(csv);
  myMenu.convertToMenu(menuTest);
  navigator.setMenu(myMenu.getVector());
  navigator.addListener(3, event_status);
  navigator.addListener(7, event_blink);
  navigator.addListener(11, event_interval);
  navigator.addListener(12, event_kp);
  navigator.addListener(13, event_ki);
  navigator.addListener(14, event_kd);
  // navigator.addListener(15, my_custom_event);
  navigator.addNotFoundListener(notFound);
  navigator.setPrinterOutput(&Serial);
}

void loop() {
  // put your main code here, to run repeatedly:
  // Serial.println("loop");
  navigator.run();
  if (Serial.available() > 0)
  {
    char ch = Serial.read();
    if (ch != '\n')
    {
      readBuffer += ch;
    }
    else
    {
      stringReady = true;
    }
  }

  if (stringReady)
  {
    if (readBuffer == "w")
    {
      navigator.up();
    }
    else if (readBuffer == "s")
    {
      navigator.down();
    }
    else if (readBuffer == "a")
    {
      navigator.back();
    }
    else if (readBuffer == "d")
    {
      navigator.ok();
    }
    readBuffer = "";
  }

}