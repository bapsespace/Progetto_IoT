# Code Structure


###The code is subdivided into separate tasks written in different files that execute in parallel with different times of recurrence:

#- "embedded_wifi_sensors_Blynk.ino" -> Start Up and Main routines (loops every 1ms)
    - Startup Routine
    - Button pressed functions
    - Screen orientation update
    - Time values margins and format check
    - LCD print layout functions
    - Logo print subroutine
 
- "Cayenne.ino" -> Internet connectivity Start up and main routines (internal delay)
   - Select ONLINE and OFFLINE mode
   - Connect to Wi-Fi and IoT Dashboard
   - Update IoT Dashboard

- "Clock.ino" -> Increment 1 second every second (loops every 1s)
  - Can be stopped with a flag
  - Runs only while the main is running

- "Debug.ino" -> RGB LED Control (loops every 10 ms)
  - In OFFLINE mode, RGB rainbow cycle
  - In ONLINE mode, RGB set by IoT Dashboard slider
 
- "Gyro.ino" -> Control accelerometer orientation (loops every 1ms)
  - Can be disabled with a flag
  - Runs only while the main is running
  - Reads accelerometer data and converts it to the correct orientation

- "Joystick.ino" -> Control Joystick orientation (loops every 1ms)
  - Can be disabled with a flag
  - Runs only while the main is running
  - Reads joystick values and converts them to the correct orientation
 
- "Logo.h" -> Start-up logo Matrix RGB values

- "Microphone.ino" -> Controls Clap light (loops every 1ms)
  - Performs reading of background noise at startup
  - If there is a peak in volume, toggles the light on and off
 
- "Music.ino" -> Play Start-up song
  - Vector of notes and vector of duration values are read and played
 
- "pitchis.h" -> Defines all the notes used by "Music" to the corresponding frequency in Hz
