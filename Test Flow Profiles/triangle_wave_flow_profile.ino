int controlPin = 9;
int value = 0;
float printValue = 0;
float flow = 0;

int delayVal = 50;
int maxVal = 160;
int minVal = 75;

void setup() {
pinMode(controlPin, OUTPUT);
Serial.begin(9600);
}

void loop() {
  // fade in from min to max in increments of 5 points:
  for (int fadeValue = minVal ; fadeValue <= maxVal; fadeValue += 1) {
    // sets the value (range from 0 to 125):
    analogWrite(controlPin, fadeValue);
    Serial.println(fadeValue);
    // wait for [delay] milliseconds to see the dimming effect
    value = fadeValue;
    delay(delayVal);
    
  }

  // fade out from max to min in increments of 5 points:
  for (int fadeValue = maxVal ; fadeValue >= minVal; fadeValue -= 1) {
    // sets the value (range from 0 to 125):
    analogWrite(controlPin, fadeValue);
    Serial.println(fadeValue);
    // wait for [delay] milliseconds to see the dimming effect
    value = fadeValue;

    delay(delayVal);
  }
}

