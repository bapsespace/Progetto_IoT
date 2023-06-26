
// threshold value to change orientation
const int gyroSensitivityThreshold=600;
const int gyroSensitivityThresholdMAX = 900;



void setupGyro() {    
  while(!mainRunning){  // whait untile main is running to start using accelerometer
    delay(10);
  }                
}


void loopGyro() {

  while(swJoyStickAsGyro){   // stops accelerometer code excecution if joystick mode is used instead
    delay(1);
  } 
  
  // read axis values
  x = ((int)analogRead(xpin) - 2048);
  y = ((int)analogRead(ypin) - 2048);
  z = ((int)analogRead(zpin) - 2048);
  delay(1);

  /*  
  Serial.print(x);
  Serial.print("\t");
  Serial.print(y);
  Serial.print("\t");
  Serial.print(z);
  Serial.println();
  */

  // check and sets correct orientation 

  if (x >= gyroSensitivityThreshold && x <= gyroSensitivityThresholdMAX){
    currentOrientation=3;//to the right
  }

  if (x <= -gyroSensitivityThreshold && x>= -gyroSensitivityThresholdMAX){
    currentOrientation=4;//to the left
  }
  
  if (y <= -gyroSensitivityThreshold && x >= -gyroSensitivityThresholdMAX){
    currentOrientation=1;//upright
  }

  if (y >= gyroSensitivityThreshold && x <= gyroSensitivityThresholdMAX) {
    currentOrientation=2;//upside down
  }

  if (z <= -gyroSensitivityThreshold && z >= -gyroSensitivityThresholdMAX) {
    currentOrientation=-1;//face down
  }

  if (z >= gyroSensitivityThreshold && z <= gyroSensitivityThresholdMAX) {
    currentOrientation=0;//face up
  }
  
}
