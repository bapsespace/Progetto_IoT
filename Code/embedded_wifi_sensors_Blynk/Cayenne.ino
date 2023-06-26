
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
    while(!startWifiConnection){        // keeps looping until main setup has complited 
      delay(10);    
    }   
    
    // RGB pins initialization
    pinMode(37,OUTPUT);
    pinMode(38,OUTPUT);
    pinMode(39,OUTPUT);

    // ask to choos between online and offline mode
    Serial.print("Attempting to connect to Network named: ");
    myScreen.clear();
    LCDprintInCenter("SMART CLOCK",0);

    LCDprintInCenter(" 1 CONNECT ->",3);
    LCDprintInCenter("2 NO INTERNET ->",6);

    while(true){    // loops and waits until an option is pressed 

      if(buttonPressed(1)){   // ONLINE mode
        myScreen.clear();
        LCDprintInCenter("Connecting to",2);
        LCDprintInCenter(ssid,3);
        digitalWrite(37,HIGH);   // blue light on for debug
      
        Cayenne.begin(username, password, clientID, ssid, wifiPassword);  // initialization of wifi connection and also connection to the IoT Dashboard server
        
        digitalWrite(37,LOW);   // blue light off for debug
    
        myScreen.clear();
        LCDprintInCenter("CONNECTED","center");
        delay(500);
        break;   // connection succesfull
      
      }
      
      if(buttonPressed(2)){   // OFFLINE mode 
        myScreen.clear();
        LCDprintInCenter("OFFLINE MODE","center");
        offlineModeSelected=true;   // set flags 
        skipValue=true; // this flag blocks the execution of IoT, not needed for offline mode
        delay(500);
        break;
      }

    }
    
    wifiHasConnected=true;   //flags to allow main setup to resume after wifi connection
    
    
}

void loopCayenne()
{
    while(skipValue){   // if offline mode is selected loops forever, no connection
      delay(1000);
    }
    
    Cayenne.loop();

    if (millis() > chrono){   // time alive counter to check connection quality
        chrono = millis() + period_ms;
        Cayenne.virtualWrite(0, chrono/1000); // send counter to the IoT Dashboard
    }

  if(s!=prevs){                   // sends the current saved time to the IoT Dashboard
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

//used to receive from IoT dashboard the slider value to select rgb color
CAYENNE_IN(2)      // This function is called when data is sent from Cayenne.  
{
  int value = getValue.asInt(); // 0 to 255
  CAYENNE_LOG("Channel %d, pin %d, value %d", 2, 37, value);

  LED_slider= value;
}

// not used 
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
