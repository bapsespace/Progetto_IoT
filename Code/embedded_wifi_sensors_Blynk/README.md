# Code Structure


The Code is subdivided into separete tasks written in differnt files, that execute in paralell with differnt time of recurrence
-  "embedded_wifi_sensors_Blynk" -> Start Up and Main routines (loops every 1ms)
    - Starup Routine
    - Button pressed functions
    - screen orientation update
    - time values margines and format check
    - LCD print layout functions
    - logo print subroutine
 
- "Cayenne" -> Internet connectivity Start up and main routines (internal delay)
   - Select ONLINE and OFFLINE mode
   - Connect to wifi and to IoT Dashboard
   - update Iot Dashboard

- "Clock" -> Increment 1 seconds every second (loops every 1s)
  - Can be stopped with flag
  - Runs only while main is running

- "Debug" -> RGB LED Control (loops every 10 ms)
  - In OFFLINE mode RGB rainbow cycle
  - In ONLINE mode RGB set by IoT Dashboard slider
 
- "Gyro" -> Control accelerometer (loops every 1ms)
  - Can be desabled with flag
  - Reads accelerometers data and convert to correct orientation

- "JoyStick"
