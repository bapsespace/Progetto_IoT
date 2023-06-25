# Cayenne MQTT LaunchPad CC3200 Library
The Cayenne MQTT LaunchPad CC3200 Library provides functions to easily connect to the [Cayenne IoT project builder](https://www.cayenne-mydevices.com). This library is designed to work with the LaunchPad CC3200 WiFi board and other LaunchPads using the CC3100 WiFi BoosterPack. With it you can send data to and receive data from Cayenne.

![alt text](https://cdn-business2.discourse.org/uploads/mydevices/original/2X/c/cde6a60b89efd4d01163e1a2c5335b454cc948a6.jpg)

## Requirements
### Hardware
* Either [LaunchPad CC3200 WiFi](http://embeddedcomputing.weebly.com/launchpad-wifi-cc3200.html).
* Or [BoosterPack CC3100](http://embeddedcomputing.weebly.com/cc3100-wifi-launchpad.html) for any other LaunchPad.
* And optionally [Sensors BoosterPack](http://embeddedcomputing.weebly.com/sensors-boosterpack.html), required for the CC3200_Sensors example.

### Software
* Either [Energia IDE](http://energia.nu/download) for Windows, Linux or macOS or [embedXcode](http://embedxcode.weebly.com) on macOS.
* [This library](https://github.com/myDevicesIoT/Cayenne-MQTT-LaunchPadCC3200/archive/master.zip).
* And optionally [Sensors BoosterPack library](https://github.com/rei-vilo/SensorsWeather_Library) for weather sensors, required for the CC3200_Sensors example.

## Getting Started
### Environment Setup
1. Download and install a compatible IDE. For this example we use the [Energia IDE](http://energia.nu/download).
2. Install the **Energia CC3200 boards**. This is done via **Tools -> Board -> Boards Manager**.
3. Download this library as a zip file [here](https://github.com/myDevicesIoT/Cayenne-MQTT-LaunchPadCC3200/archive/master.zip).
4. Install the downloaded zip library. This is done via **Sketch -> Include Library -> Add .ZIP Library**.
5. Make sure your board is connected and select the correct board and port from the **Tools** menu.

### Cayenne Setup
1. Create your Cayenne account at https://www.cayenne-mydevices.com.
2. Add a new device using the Bring Your Own Thing API selection.

### Building Examples
1. Open one of the included example sketches from **File -> Examples -> Cayenne-MQTT-LaunchPadCC3200**.
2. Modify the included sketch with your network info, and the Cayenne authentication info you received when adding your device.
3. Compile and upload the sketch to your device.
4. Check the Cayenne dashboard to ensure it is receiving sample data from your device.

![alt text](https://cdn-business2.discourse.org/uploads/mydevices/original/2X/b/b5eebfa7a8680b3c25969fc98a7ba391b9b6c624.png)

## Contributions
* This library includes the [Eclipse Paho MQTT C/C++ client](https://github.com/eclipse/paho.mqtt.embedded-c).
* Contributions to this library were made by Rei Vilo (rei-vilo).

## Cayenne MQTT Libraries
Additional libraries are available for connecting to Cayenne on other platforms and devices. These can be found at https://github.com/myDevicesIoT.
