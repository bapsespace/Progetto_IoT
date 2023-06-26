int calibration=99999;
int calibrationSamples=2000;
int microphoneVal=0;
bool a=false;


void setup() {

  pinMode(6,INPUT);

  for(int i=0;i<calibrationSamples;i++){              // at startup reads some samples to determine the background noise level
    microphoneVal=analogRead(6);
    calibration+=microphoneVal;
    
    delay(1);
  }
  calibration=calibration/calibrationSamples;
  
}

void loop() {
  

  microphoneVal=analogRead(6);

  
  if(microphoneVal<calibration-calibration/2){ //  After clibration in normal code execution if noise level is highr then background toggles the white light, also sends status to the IoT dashboard
    if(a){
      digitalWrite(RED_LED,HIGH);
      digitalWrite(GREEN_LED,HIGH);
      digitalWrite(BLUE_LED,HIGH);
      Cayenne.virtualWrite(15, 1);
      a=false;
      delay(100);
      }else{
      digitalWrite(RED_LED,LOW);
      digitalWrite(GREEN_LED,LOW);
      digitalWrite(BLUE_LED,LOW);
      Cayenne.virtualWrite(15, 0);
      a=true;
      delay(100);
      }
  }
  delay(1);

  
}
