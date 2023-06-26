
#if defined(ENERGIA) // LaunchPad MSP430, Stellaris and Tiva, Experimeter Board FR5739 specific
#include "Energia.h"
#else // error
#error Platform not defined
#endif



#ifndef __CC3200R1M1RGC__
#include <SPI.h>
#endif

#include <LCD_screen.h>
#include <LCD_screen_font.h>
#include <LCD_utilities.h>
#include <Screen_HX8353E.h>
#include <Terminal12e.h>
#include <Terminal6e.h>
#include <Terminal8e.h>
Screen_HX8353E myScreen;



#include "Logo.h" //it contains the matrix of the values of the pixel for the startup image 




// variables containing seconds minutes and hours value in string format for printing on screen

String hc = "00";
String mc = "00";
String sc = "00";

// variables containing seconds minutes and hours value in decimal format
int h=0;
int m=0; 
int s=0; 


const int buttonOne = 33;     // the pin number of the pushbutton 
const int buttonTwo = 32;     // the pin number of the pushbutton

const int jswpin = 5;         //joystick button pin (NOT WORKING WHEN PRESSED BOARD FREEZE
const int jxpin=2;            //joystick x axis pin
const int jypin=26;           //joystick y axis pin

int jxval=0;        //joystick x axis value 
int jyval=0;        //joystick y axis value 


const int xpin = 23;                  // x-axis pin of the accelerometer
const int ypin = 24;                  // y-axis pin of the accelerometer
const int zpin = 25;                  // z-axis pin(only on 3-axis models)
const int posx = 128;
const int posy = 128;

// final string for time
String val = "";
String timer = hc + ":" + mc + ":" + sc;
String previusTimer="99:99:99";
int x, y, z;

int currentOrientation=0;
int previusOrientation=1;


bool startWifiConnection=false;   //when main setup is done is set to true allowing wifi setup to start
bool wifiHasConnected=false;      //when wifi setup is completed is set to true
bool clockRunning=false;          //starts and stops clock that adds one second to the time every 1000ms
bool mainRunning=false;           //is set to true when main loop is running
bool swJoyStickAsGyro=false;       //if false uses accelerometer if true jostick is used to switch the rotation
bool pauseJoystickAsGyro=false;   //used to momntarly use joystick value for somthing else whiout enabling accelerometer
bool offlineModeSelected=false;   //flag true when offline mode is selected at startup, used to chage rgb control IoT to rainbow loop


void setup() {
  
  
  // By default MSP432 has analogRead() set to 10 bits.
  // This Sketch assumes 12 bits. Uncomment to line below to set analogRead()
  // to 12 bit resolution for MSP432.
  analogReadResolution(12);

  Serial.begin(115200);

  //startup routine with display of the logo
  myScreen.begin();
  String s = myScreen.WhoAmI(); 
  myScreen.setOrientation(0);  
  myScreen.clear(whiteColour);
  logo50();
  delay(3000);
  

  pinMode(RED_LED, OUTPUT);      // set the LED pin mode
  pinMode(GREEN_LED,OUTPUT);
  pinMode(BLUE_LED,OUTPUT);
  
  pinMode(buttonOne, INPUT_PULLUP);       //buttons pinmode set
  pinMode(buttonTwo, INPUT_PULLUP);   
  pinMode(jswpin,INPUT); 

  delay(800);
  startWifiConnection=true;   // flag to enable start of wifi connection

  
  while(!wifiHasConnected){         // main stops until wifi has connected
    delay(10);
  }

}



void loop(){  
  mainRunning=true;  // flag used by other fuction to know when the main loop is running
  
  if(buttonPressed(1)&& buttonPressed(2)){  // check if both button are pressed at the same time to trigger switch joystick to gyro
    if(currentOrientation==0){
      myScreen.setOrientation(0);
      myScreen.clear();
      if(swJoyStickAsGyro){
        swJoyStickAsGyro=false;
        LCDprintInCenter("Accelerometer","center");
      }
      else{
        swJoyStickAsGyro=true;
        LCDprintInCenter("JoyStick","center");
      }

      delay(500);
      myScreen.clear();
      LCDprintInCenter("Girami per iniziare","center");
    }
    
    tempo(0,0,0);   // reset swtich 
    
  }else{
    if(buttonPressed(1)){    // check if only button 1 is pressed to enter manual time adjustment mode 
      pauseJoystickAsGyro=true; // flag to pause joystick reading used as gyro in case is running in joystick mode, because now it needs to be used as a value incremet
      clockRunning=false;   // flag to stop the clock
       
      if(jyval<48){  // if value is lower then dead zone threshold seconds are reduced faster as more bend is the joystick
        s--; 
        delay(map(jyval,0,50,0,1000));
      }
      if(jyval>52){ // if value is higher then dead zone threshold secods are incremented faster as more bend is the joystick 
        s++;
        delay(map(jyval,50,100,1000,0));
      }      
      
    }else{
      pauseJoystickAsGyro=false;  // resme normale operation
      clockRunning=true;   // resume the clock
    }
      
    if(buttonPressed(2)){     // check if only second button is pressed, sets orientation to center only in joystick mode
      if(swJoyStickAsGyro){
        currentOrientation=0;
      }       
    }
      
  }

 // checks the decimal time stored is never below zero, and adjust value accordingly if needed
  if(s<0){
    if(m>0)
      s=59;
    else
      s=0;
    m--;
  }  
  if(m<0){
    if(h>0)
      m=59;
    else
      m=0;
    h--;
  }
  if(h<0)
    h=0;


  if(currentOrientation != previusOrientation){  // check if orientation is changed 
    myScreen.clear();
    tempo(0,0,0);   // if it is changed reset timer
    switch (currentOrientation){    // select correct orientation on the screen and print the timer or the appropriate String
      
      case 0:
        myScreen.setOrientation(0);
        LCDprintInCenter("Girami per iniziare","center");
        clockRunning=false;
        break;
      case -1:
        myScreen.setOrientation(0);
        LCDprintInCenter("Turn me face up","center");
        clockRunning=false;
        break;

      case 1:
        myScreen.setOrientation(0);
        LCDprintInCenter(timer,"center",redColour);
        clockRunning=true;
        break;
      case 2:
        myScreen.setOrientation(2);
        LCDprintInCenter(timer,"center",redColour);
        clockRunning=true;
        break;
      case 3:
        myScreen.setOrientation(-1);
        LCDprintInCenter(timer,"center",redColour);
        clockRunning=true;
        break;
      case 4:
        myScreen.setOrientation(1);
        LCDprintInCenter(timer,"center",redColour);
        clockRunning=true;
        break;
        
    }
    
    previusOrientation=currentOrientation; // used to check if orientation is changed
  }else{
    if(currentOrientation!=0 && currentOrientation!=-1){    // refresh timer string on screen at each cicle when orientation doesn't change
      //clockRunning=true;
      tempo();
      if(!timer.equals(previusTimer)){
        LCDprintInCenter(timer,"center",redColour);
        previusTimer=timer;
      }
    }
  }
  delay(1);

   
    
    
    
}

void tempo(int x,int y, int z){
    h=x;
    m=y;
    s=z;
}



void tempo(){  // check timer value is in the correct margins increment if needed. Also convert decimal to string adding 0 padding if needed
  
  if(s>=60){
    s=00;
    m=m+1;
 }
  if(m>=60){
    m=00;
    h=h+1;
    }
  if(h>=24){
    h=0;
  } 

  if(h<10){
    hc = "0" + String(h);
  } else hc = h;

  
  if(m<10){
    mc = "0" + String(m);
  } else mc = m;

  
  if(s<10){
    sc = "0" + String(s);
  } else sc = s;
  
  timer = hc + ":" + mc + ":" + sc;
}



//Function to write a text at the center of the screen orizontally and let adjust vertical allignemnt
//"top" at the top "center" in the middle of the screen or input a number from 0 to n for the raw number already spaced with the raw above

void LCDprintInCenter(String text,String pos){
  if(pos.equals("top"))
    myScreen.gText(posx/2 - ((text.length()*6)/2), myScreen.fontSizeY(), text, greenColour);
  if(pos.equals("center"))
    myScreen.gText(posx/2 - ((text.length()*6)/2), posy/2 - myScreen.fontSizeY()/2, text, greenColour);
}

void LCDprintInCenter(String text,int raw){
   myScreen.gText(posx/2 - ((text.length()*6)/2), (myScreen.fontSizeY()+3)*(raw+1), text, greenColour);   
}

void LCDprintInCenter(String text,String pos, int color){
  if(pos.equals("top"))
    myScreen.gText(posx/2 - ((text.length()*6)/2), myScreen.fontSizeY(), text, color);
  if(pos.equals("center"))
    myScreen.gText(posx/2 - ((text.length()*6)/2), posy/2 - myScreen.fontSizeY()/2, text, color);
}

void LCDprintInCenter(String text,int raw, int color){
   myScreen.gText(posx/2 - ((text.length()*6)/2), (myScreen.fontSizeY()+3)*(raw+1), text, color);  
}



bool buttonPressed(){    // functino return true if any button has been pressed, with debounce
  int count=0;
  const int maxCount=10;
  
  while(digitalRead(buttonOne)==LOW || digitalRead(buttonTwo)==LOW && count<maxCount ){
    count++;
    delay(1);
  }
  if(count>=maxCount){
    count = 0;
    return true;
  }           
  count=0;
  return false;
}

bool buttonPressed(int button){   // function returns selected button status, pressed or not, with debounce 
  int count=0; 
  int pin=0;
  const int maxCount=10;
  if(button==1)
    pin=buttonOne;
  if(button==2)
    pin=buttonTwo;
  if(button==3)
    pin=jswpin;
  
  
  while(digitalRead(pin)==LOW && count<maxCount ){
    count++;
    delay(1);
  }
  if(count>=maxCount){
    count = 0;
    return true;
  }           
  count=0;
  return false;
}



void logo50()   // this function is called at startup, loads image matrix from the logo.h and prints it on screen
{
    uint32_t p;
    uint16_t c;
    uint16_t x00 = 0;
    uint16_t y00 = 0;
    uint16_t i00 = 0;
    uint16_t j00 = 0;
    
    if ((myScreen.screenSizeX() > x_Energia_logo_100_132_bmp)) {
        x00 = (myScreen.screenSizeX() - x_Energia_logo_100_132_bmp) / 2;
    } else {
        i00 = (x_Energia_logo_100_132_bmp - myScreen.screenSizeX()) / 2;
    }
    if ((myScreen.screenSizeY() > y_Energia_logo_100_132_bmp)) {
        y00 = (myScreen.screenSizeY() - y_Energia_logo_100_132_bmp) / 2;
    } else {
        j00 = (y_Energia_logo_100_132_bmp - myScreen.screenSizeY()) / 2;
    }
    p = (uint32_t)x_Energia_logo_100_132_bmp * y_Energia_logo_100_132_bmp;
    
    for (uint16_t i=0; i<x_Energia_logo_100_132_bmp; i++) {
        for (uint16_t j=0; j<y_Energia_logo_100_132_bmp; j++) {
            if ((x00+i < myScreen.screenSizeX()) && (y00+j < myScreen.screenSizeY())) {
                c = pic_Energia_logo_100_132_bmp[i*y_Energia_logo_100_132_bmp + j];
                myScreen.point(x00+i-i00, y00+j-j00, c);
            }
        }
        delay(1);
    }
}
