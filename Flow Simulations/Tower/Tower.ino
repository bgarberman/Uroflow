float curve[] = {0,0.82446,1.6476,2.4683,3.2851,4.0969,4.9024,5.7002,6.4894,7.2685,8.0364,8.7919,9.5338,10.261,10.972,11.667,12.343,13.001,13.638,14.255,14.849,15.421,15.969,16.492,16.989,17.461,17.905,18.322,18.711,19.071,19.401,19.702,19.972,20.212,20.42,20.596,20.741,20.854,20.935,20.984,21,20.984,20.935,20.854,20.741,20.596,20.42,20.212,19.972,19.702,19.401,19.017,18.641,18.272,17.91,17.555,17.208,16.867,16.533,16.205,15.885,15.57,15.262,14.96,14.663,14.373,14.088,13.809,13.536,13.268,13.005,12.748,12.495,12.248,12.005,11.768,11.535,11.306,11.082,10.863,10.648,10.437,10.23,10.028,9.8291,9.6345,9.4437,9.2567,9.0734,8.8938,8.7176,8.545,8.3758,8.21,8.0474,7.888,7.7319,7.5788,7.4287,7.2816,7.1374,6.9961,6.8575,6.7218,6.5887,6.4582,6.3303,6.205,6.0821,5.9617,5.8436,5.7279,5.6145,5.5033,5.3943,5.2875,5.1828,5.0802,4.9796,4.881,4.7843,4.6896,4.5967,4.5057,4.4165,4.3291,4.2433,4.1593,4.0769,3.9962,3.9171,3.8395,3.7635,3.689,3.6159,3.5443,3.4741,3.4054,3.3379,3.2718,3.207,3.1435,3.0813,3.0203,2.9605,2.9019,2.8444,2.7881,2.7329,2.6787,2.6257,2.5737,2.5227,2.4728,2.4238,2.3758,2.3288,2.2827,2.2375,2.1932,2.1497,2.1072,2.0655,2.0246,1.9845,1.9452,1.9067,1.8689,1.8319,1.7956,1.7601,1.7252,1.691,1.6576,1.6247,1.5926,1.561,1.5301,1.4998,1.4701,1.441,1.4125,1.3845,1.3571,1.3302,1.3039,1.2781,1.2528,1.228,1.2036,1.1798,1.1564,1.1335,1.1111,1.0891,1.0675,1.0464,1.0257,1.0054,0.98546,0.96594,0.94682,0.92807,0.90969,0.89168,0.87402,0.85671,0.83975,0.82312,0.80682,0.79085,0.77519,0.75984,0.74479,0.73004,0.71559,0.70142,0.68753,0.67392,0.66057,0.64749,0.63467,0.6221,0.60978,0.59771,0.58587,0.57427,0.5629,0.55176,0.54083,0.53012,0.51962,0.50933,0.49925,0.48936,0.47967,0.47017,0.46086,0.45174,0.44279,0.43403,0.42543,0.41701,0.40875,0.40066,0.39272,0.38495,0.37732,0.36985,0.36253,0.35535,0.34831,0.34142,0.33466,0.32803,0.32153,0.31517,0.30893,0.30281,0.29681,0.29094,0.28518,0.27953,0.27399,0.26857,0.26325,0.25804,0.25293,0.24792,0.24301,0.2382,0.23348,0.22886,0.22433,0.21988,0.21553,0.21126,0.20708,0.20298,0.19896,0.19502,0.19116,0.18737,0.18366,0.18003,0.17646,0.17297,0.16954,0.16619,0.16289,0.15967,0.15651,0.15341,0.15037,0.14739,0.14447,0.14161,0.13881,0.13606,0.13337,0.13073};
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
