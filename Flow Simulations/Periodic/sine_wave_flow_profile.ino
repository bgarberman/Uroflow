int controlPin = 9;
int value = 0;
int i = 0;

int stepVal = 100;
float motorVoltage = 0;

void setup() {
  pinMode(controlPin, OUTPUT);
  Serial.begin(9600);
}

void loop() 
{

motorVoltage = 120 * sin(0.05*i) + 120;
    analogWrite(controlPin, (int)motorVoltage);
    Serial.println(motorVoltage);
    delay(stepVal);

    i +=1;
}
