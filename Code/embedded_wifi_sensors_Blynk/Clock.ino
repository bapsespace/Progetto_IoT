void setupClock(){
  while(!mainRunning){
    delay(10);
  }
  
}

void loopClock(){
  while(!clockRunning){
    delay(1);
  }
  
  s++;
  delay(1000);
}
