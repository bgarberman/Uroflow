float curve[] = {0,0.31411,0.62791,0.94108,1.2533,1.5643,1.8738,2.1814,2.4869,2.7899,3.0902,3.3874,3.6812,3.9715,4.2578,4.5399,4.8175,5.0904,5.3583,5.6208,5.8779,6.1291,6.3742,6.6131,6.8455,7.0711,7.2897,7.5011,7.7051,7.9016,8.0902,8.2708,8.4433,8.6074,8.7631,8.9101,9.0483,9.1775,9.2978,9.4088,9.5106,9.6029,9.6858,9.7592,9.8229,9.8769,9.9211,9.9556,9.9803,9.9951,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,9.9951,9.9803,9.9556,9.9211,9.8769,9.8229,9.7592,9.6858,9.6029,9.5106,9.4088,9.2978,9.1775,9.0483,8.9101,8.7631,8.6074,8.4433,8.2708,8.0902,7.9016,7.7051,7.5011,7.2897,7.0711,6.8455,6.6131,6.3742,6.1291,5.8779,5.6208,5.3583,5.0904,4.8175,4.5399,4.2578,3.9715,3.6812,3.3874,3.0902,2.7899,2.4869,2.1814,1.8738,1.5643,1.2533,0.94108,0.62791,0.31411,0};
int red = 3;
int blue = 2;
int buttonPin = 12;
int buttonState = 0;
int prevButtonState = 0;
int outPin = 10;
int outputVals[sizeof(curve)*sizeof(int)/sizeof(float)];

//float inputVals[] = Bell1;
//float outputVals[sizeof(Bell1[])];

void pinSetup(){
  analogWriteResolution(12);
  Serial.begin(9600);
  Serial.println(sizeof(curve)/sizeof(float));
  //Serial.println(sizeof(int));
  //Serial.println(sizeof(float));
  pinMode(red, OUTPUT);
  pinMode(blue, OUTPUT);
  pinMode(outPin, OUTPUT);
  pinMode(buttonPin, INPUT);
  pinMode(13, OUTPUT);
}

int flowToVolt(float flow){
  float out;
  out = 98.11*flow+1733.5;
  out = int(out);
  return out;
}

void setup() {
  pinSetup();
  //analogWriteFrequency(20, 490);
   // analogWriteResolution(12);
  
  for (int i = 0; i < sizeof(curve)/sizeof(float); i++){
    outputVals[i] = flowToVolt(curve[i]);
  }

  digitalWrite(blue, HIGH);
      digitalWrite(13, HIGH);
}

void loop() {
  buttonState = digitalRead(buttonPin);
  if (buttonState == 0 && prevButtonState == 1){
    digitalWrite(blue, LOW);
    digitalWrite(red, HIGH);
    //Serial.println(sizeof(outputVals)/(4*sizeof(int)));
    
    for (int i = 0; i < sizeof(curve)/(sizeof(int)); i++){
      analogWrite(outPin, outputVals[i]);
      Serial.println(outputVals[i]);
      delay(50);
    }
    digitalWrite(red, LOW); 
    digitalWrite(blue, HIGH);
    analogWrite(outPin, 0);  
  }
  
  prevButtonState = buttonState;


}

