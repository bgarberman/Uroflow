#include <LiquidCrystal.h>

int controlPin = 9;
int value = 0;

int delayVal = 2000;
int squareHeight = 140;

const int rs = 12, en = 11, d4 = 5, d5 = 4, d6 = 3, d7 = 2;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

void setup() {
  pinMode(controlPin, OUTPUT);
  Serial.begin(9600);
}

void loop() 
{
  //lcd.setCursor(0, 1);
  //lcd.print("Square wave");
  analogWrite(controlPin, squareHeight);
  Serial.println(squareHeight);

  delay(delayVal);
  
  analogWrite(controlPin, 0);
  Serial.println(0);
  
  delay(delayVal);
}

