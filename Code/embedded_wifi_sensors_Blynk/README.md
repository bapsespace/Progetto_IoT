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
