


void setupJoyStick() {
  

  pinMode(jxpin,INPUT);
  pinMode(jypin,INPUT);

 while(!mainRunning){   // wait for main to run 
    delay(10);
  }

}

void loopJoyStick() {

  jxval=analogRead(jxpin)*100/4096;   // read joystick values
  jyval=analogRead(jypin)*100/4096;
  delay(1);

  while(swJoyStickAsGyro && !pauseJoystickAsGyro){     // check if joystick mode is selected and if a pause due to manual change time is requested
    jxval=analogRead(jxpin)*100/4096;
    jyval=analogRead(jypin)*100/4096; // if ok preceed read vlaues and then select orientation accordingly
    
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
