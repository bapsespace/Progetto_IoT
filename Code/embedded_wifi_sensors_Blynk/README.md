# Code Structure


The Code is subdivided into separete tasks written in differnt files, that execute in paralell with differnt time of recurrence
-  "embedded_wifi_sensors_Blynk.ino" -> Start Up and Main routines (loops every 1ms)
    - Starup Routine
    - Button pressed functions
    - screen orientation update
    - time values margines and format check
    - LCD print layout functions
    - logo print subroutine
 
- "Cayenne.ino" -> Internet connectivity Start up and main routines (internal delay)
   - Select ONLINE and OFFLINE mode
   - Connect to wifi and to IoT Dashboard
   - update Iot Dashboard

- "Clock.ino" -> Increment 1 seconds every second (loops every 1s)
  - Can be stopped with flag
  - Runs only while main is running

- "Debug.ino" -> RGB LED Control (loops every 10 ms)
  - In OFFLINE mode RGB rainbow cycle
  - In ONLINE mode RGB set by IoT Dashboard slider
 
- "Gyro.ino" -> Control accelerometer orientation (loops every 1ms)
  - Can be disabled with flag
  - Runs only while main is running
  - Reads accelerometers data and convert to correct orientation

- "JoyStick.ino" -> Control Joystick orientation (loops evrery 1ms)
  - Can be disabled with flag
  - Runs only while main is running
  - Reads joystick values and convert to correct orientation
 
- "Logo.h" -> Start up logo Matrix RGB values

- "Microphone.ino" -> Controls Clap light (loops every 1ms)
  - Performs reading of background noise at starup
  - if there is a peak in volume toggles light on and off
 
- "Music.ino" -> Play Start up song
  - vector of notes and vectore of duration values are read and played
 
- "pitchis.h" -> Defines all the note used by "Music" to the corresponding frequency in Hz
