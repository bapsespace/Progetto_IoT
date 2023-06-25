
/*
  ADXL3xx 3-axis accelerometer example for Educational BoosterPack MK II
  http://boosterpackdepot.info/wiki/index.php?title=Educational_BoosterPack_MK_II

  Absolute rating/conversion can be determined from the ADXL3xx datasheet.
  As a quick reference, for LaunchPads with 12-bit ADC (MSP430F5529, Tiva C, etc.),
  the entire analog  range is [0,4096]. For simple tilting calculation
  [-1g,1g] ~ = [mid-800, mid + 800] = [2048-800,2048+800] = [1248,2848]

  Modified from ADXL3xx example by David A. Mellis & Tom Igoe

  Reads an Analog Devices ADXL3xx accelerometer and communicates the
  acceleration to the computer.  The pins used are designed to be easily
  compatible with the breakout boards from Sparkfun, available from:
  http://www.sparkfun.com/commerce/categories.php?c=80

  http://www.arduino.cc/en/Tutorial/ADXL3xx

  The circuit:

   analog 25: z-axis
   analog 24: y-axis
   analog 23: x-axis

  created 2 Jul 2008
  by David A. Mellis
  modified 30 Aug 2011
  by Tom Igoe
  modified 03 Dec 2013
  by Dung Dang

  This example code is in the public domain.

*/
#include <LCD_screen.h>
#include <LCD_screen_font.h>
#include <LCD_utilities.h>
#include <Screen_HX8353E.h>
Screen_HX8353E myScreen;

String hc = "00";
String mc = "00";
String sc = "00";
int h=00;
int m=00;
int s=00;


const int buttonOne = 33;     // the number of the pushbutton pin
const int buttonTwo = 32;     // the number of the pushbutton pin

int buttonOneState = 0;         // variable for reading the pushbutton #1 status
int buttonTwoState = 0;         // variable for reading the pushbutton #2 status

const int xpin = 23;                  // x-axis of the accelerometer
const int ypin = 24;                  // y-axis
const int zpin = 25;                  // z-axis (only on 3-axis models)
const int posx = 128;
const int posy = 128;
const String base = "Girami per iniziare";
String val = "";
String timer = hc + ":" + mc + ":" + sc;
int x, y, z;
int hasRun = 0;

void setup()
{
  // By default MSP432 has analogRead() set to 10 bits.
  // This Sketch assumes 12 bits. Uncomment to line below to set analogRead()
  // to 12 bit resolution for MSP432.
  analogReadResolution(12);

  // initialize the serial communications:
  Serial.begin(9600);
  myScreen.begin();

  
  pinMode(buttonOne, INPUT_PULLUP);     
  pinMode(buttonTwo, INPUT_PULLUP);     
}

void loop()
{  
  buttonOneState = digitalRead(buttonOne);
  
  x = ((int)analogRead(xpin) - 2048);
  y = ((int)analogRead(ypin) - 2048);
  z = ((int)analogRead(zpin) - 2048);

  Serial.print(x);
  // print a tab between values:
  Serial.print("\t");
  Serial.print(y);
  // print a tab between values:
  Serial.print("\t");
  Serial.print(z);
  Serial.println();
  //delay(100);

  

  //caso 1 x = 90
  if (x >= 700 && x <= 900) {
    if (hasRun != 0){
      h=0;
      m=0;
      s=0;
      tempo();
      myScreen.clear();  
    }
    hasRun = 0;
    myScreen.setOrientation(-1);
    myScreen.gText(posx/2 - ((timer.length()*6)/2), posy/2 - myScreen.fontSizeY()/2, timer, redColour);
    s++;
    tempo();
    delay(1000);
  }
  /*caso 2 z = 90
  if (z >= 700 && z <= 900) {
    if (hasRun != 1) myScreen.clear();
    hasRun = 1;
    myScreen.gText(40, myScreen.fontSizeY() * 3 + 40, "caso 2", redColour);
  }*/
  //caso 3 x =-90
  if (x <= -700 && x >= -900) {
    if (hasRun != 2) {
      h=0;
      m=0;
      s=0;   
      tempo();
      myScreen.clear(); 
    }
    hasRun = 2;
    myScreen.setOrientation(1);
    myScreen.gText(posx/2 - ((timer.length()*6)/2), posy/2 - myScreen.fontSizeY()/2, timer, redColour);
    s++;
    tempo();
    delay(1000);
  }
  /*caso 4 z =-90
  if (z <= -700 && z >= -900) {
    if (hasRun != 3) myScreen.clear();
    hasRun = 3;
    myScreen.gText(40, myScreen.fontSizeY() * 3 + 40, "caso 4", redColour);
  }*/
  //caso 5 y =-90
  if (y <= -700 && y >= -900) {
    if (hasRun != 4) {
      h=0;
      m=0;
      s=0; 
      tempo();
      myScreen.clear();  
   }
    hasRun = 4;
    myScreen.setOrientation(0);
    myScreen.gText(posx/2 - ((timer.length()*6)/2), posy/2 - myScreen.fontSizeY()/2, timer, redColour);
    s++;
    tempo();
    delay(1000);
  }
  //caso 6 y = 90
  if (y >= 700 && y <= 900) {
    if (hasRun != 5) { 
      h=0;
      m=0;
      s=0; 
      tempo();
      myScreen.clear(); 
    }
    hasRun = 5;
    myScreen.setOrientation(2);
    myScreen.gText(posx/2 - ((timer.length()*6)/2), posy/2 - myScreen.fontSizeY()/2, timer, redColour);
    s++;
    tempo();
    delay(1000);
  }
  
  if(z <= -700 && z >= -900 || z >= 700 && z <= 900){
    if (hasRun != 3) {myScreen.clear();
    hasRun = 3;    
    myScreen.setOrientation(0);
    myScreen.gText(posx/2 - ((base.length()*6)/2), posy/2 - myScreen.fontSizeY()/2, base, greenColour);
  }
 }

  if(buttonOneState == LOW){    
      h=0;
      m=0;
      s=0;
      tempo();
      myScreen.clear(); 
  }
 
}

void tempo(){
  if(s==60){
  s=00;
  m=m+1;
 }
 if(m==60)
 {
  m=00;
  h=h+1;
 }
 if(h==24)
 {
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
