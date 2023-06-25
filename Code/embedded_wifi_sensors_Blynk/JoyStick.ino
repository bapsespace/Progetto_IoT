


void setupJoyStick() {
  

  pinMode(jxpin,INPUT);
  pinMode(jypin,INPUT);

 while(!mainRunning){
    delay(10);
  }

}

void loopJoyStick() {

  jxval=analogRead(jxpin)*100/4096;
  jyval=analogRead(jypin)*100/4096;
  delay(1);

  while(swJoyStickAsGyro && !pauseJoystickAsGyro){
    jxval=analogRead(jxpin)*100/4096;
    jyval=analogRead(jypin)*100/4096;
    
    if(jxval>80)
      currentOrientation=3;
    if(jxval<20)
      currentOrientation=4;
    if(jyval>80)
      currentOrientation=2;
    if(jyval<20)
      currentOrientation=1;
    delay(10);
  } 
  
/*
  Serial.print(jxval);
  Serial.print("\t");
  Serial.print(jyval);
  Serial.print("\t");
  Serial.println(jswval);
  */
  
}
