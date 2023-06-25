
#define CAYENNE_PRINT Serial
#include <CayenneMQTTWiFi.h>

// WiFi network info.
char ssid[] = "Vodafone-C01560209";
char wifiPassword[] = "tT29fapETnZF3qn7";

// Cayenne authentication info. This should be obtained from the Cayenne Dashboard.
char username[] = "ff9d91a0-aeba-11ed-b72d-d9f6595c5b9d";
char password[] = "175e8f3c89db98e4b06b5cdca3bd50e8bc5f627b";
char clientID[] = "c8b71f90-aec8-11ed-b0e7-e768b61d6137";

// Edit period_ms
const uint32_t period_ms = 1000;
uint32_t chrono = 0;

bool skipValue=false;


int LED_slider=0;
int prevs=0;

void setupCayenne()
{
    while(!startWifiConnection){
      delay(10);    
    }   

    pinMode(37,OUTPUT);
    pinMode(38,OUTPUT);
    pinMode(39,OUTPUT);

    
    Serial.print("Attempting to connect to Network named: ");
    myScreen.clear();
    LCDprintInCenter("SMART CLOCK",0);

    LCDprintInCenter(" 1 CONNECT ->",3);
    LCDprintInCenter("2 NO INTERNET ->",6);

    while(true){

      if(buttonPressed(1)){
        myScreen.clear();
        LCDprintInCenter("Connecting to",2);
        LCDprintInCenter(ssid,3);
        digitalWrite(37,HIGH);
      
        Cayenne.begin(username, password, clientID, ssid, wifiPassword);
        
        digitalWrite(37,LOW);
    
        myScreen.clear();
        LCDprintInCenter("CONNECTED","center");
        delay(500);
        break;
      
      }
      
      if(buttonPressed(2)){
        myScreen.clear();
        LCDprintInCenter("OFFLINE MODE","center");
        offlineModeSelected=true;
        skipValue=true;
        delay(500);
        break;
      }

    }
    
    wifiHasConnected=true;
    
    
}

void loopCayenne()
{
    while(skipValue){
      delay(1000);
    }
    
    Cayenne.loop();

    if (millis() > chrono){
        chrono = millis() + period_ms;
        Cayenne.virtualWrite(0, chrono/1000);
    }

  if(s!=prevs){
    Cayenne.virtualWrite(10, s);
    Cayenne.virtualWrite(11, m);
    Cayenne.virtualWrite(12, h);
    prevs=s;
  }
    
}


//Default function for processing actuator commands from the Cayenne Dashboard.
//You can also use functions for specific channels, e.g CAYENNE_IN(1) for channel 1 commands.
CAYENNE_IN_DEFAULT()
{
    CAYENNE_LOG("CAYENNE_IN_DEFAULT(%u) - %s, %s", request.channel, getValue.getId(), getValue.asString());
    //Process message here. If there is an error set an error message using getValue.setError(), e.g getValue.setError("Error message");
}

CAYENNE_IN(2)      // This function is called when data is sent from Cayenne.
{
  int value = getValue.asInt(); // 0 to 255
  CAYENNE_LOG("Channel %d, pin %d, value %d", 2, 37, value);

  LED_slider= value;
}
CAYENNE_IN(3)      // This function is called when data is sent from Cayenne.
{
  int value = getValue.asInt(); // 0 to 255
  CAYENNE_LOG("Channel %d, pin %d, value %d", 3, 38, value);

  //analogWrite(38, value);
}
CAYENNE_IN(4)      // This function is called when data is sent from Cayenne.
{
  int value = getValue.asInt(); // 0 to 255
  CAYENNE_LOG("Channel %d, pin %d, value %d", 4, 39, value);

  //analogWrite(39, value);
}
