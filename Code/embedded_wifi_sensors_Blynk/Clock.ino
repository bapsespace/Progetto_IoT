void setupClock(){
  while(!mainRunning){  // wait until main loop is running
    delay(10);
  }
  
}

void loopClock(){
  while(!clockRunning){    // if clockRunning is set to false stops the clock loop 
    delay(1);
  }
  
  s++;
  delay(1000);
}
