#include <Filters.h> //Filters used to clean up raw sensor data

#define openPin A3 //Pin definition
#define closePin A2
#define buttonPin A1
#define sensorPin A4
#define outputPin A14

int sensorVal; //Integer variable initialization
int buttonState;
int prevButtonState;
int flushState = 0;
int initialReading;

float sensorFiltered; //Float variable initialization
float prevVal;
float timing = 0;
float prevTime = 0;
float derivative;
float flowRate;
float filterFrequency = 3.0;
float valveThreshold = 100.0;

FilterOnePole lowpassFilter(LOWPASS, filterFrequency); //Filter initialization

void setup() {
  pinMode(openPin, OUTPUT); //Pin mode initialization
  pinMode(closePin, OUTPUT);
  pinMode(buttonPin, INPUT);
  pinMode(sensorPin, INPUT);
  pinMode(outputPin, OUTPUT);
  pinMode(13, OUTPUT);
  Serial.begin(9600);

  analogWriteResolution(12); //Sets DAC to higher resolution than default
  initialReading = analogRead(sensorPin);//Reads empty sensor reading for flush sequence  
}

void loop() {
  if (flushState == 0) {

    sensorVal = analogRead(sensorPin);  //Sensor reading and filtering
    Serial.print(sensorVal);
    sensorFiltered = lowpassFilter.input(sensorVal);
    sensorFiltered = sensorFiltered; //Calibration 
 
    timing = millis();  //Derivating
    derivative = (sensorFiltered - prevVal) / (timing - prevTime);
    prevVal = sensorFiltered;
    prevTime = timing;
    flowRate = abs(150*derivative); //Calibration
    Serial.print("  ");
    Serial.print(derivative);
    Serial.print("  ");
    Serial.println(flowRate);
     
    analogWrite(outputPin, flowRate); //Send output to ESP8266 
    delay(10);

    buttonState = digitalRead(buttonPin); //Checks to see if a flush is requested
    if (buttonState == HIGH) { 
        flushState = 1; //Initiates flush sequence
        digitalWrite(13, HIGH);
       } 
    }
    prevButtonState = buttonState;

  if (flushState == 1) { 
     while (sensorVal > valveThreshold*initialReading){  //Waits for fluid to empty
          valveOpen();
          sensorVal = analogRead(sensorPin);  //Refreshes sensor reading to check level
          Serial.println(sensorVal);
        }
        //delay(5000); //Delay for fluid to fully drain
        valveClose(); //Closes valve
        digitalWrite(13, LOW);
        flushState = 0; //Returns code to sensor reading and processing state
  }
}

void valveOpen() { //Opens valve
  digitalWrite(openPin, HIGH);
  digitalWrite(closePin, LOW);
}

void valveClose() { //Closes valve
  digitalWrite(openPin, LOW);
  digitalWrite(closePin, HIGH);
}

