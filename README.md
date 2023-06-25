## Progetto_IoT
Progetto per il corso Embedded Software for IoT UNITN


# SMART CLOCK
This project consist in a smart multifunctional clock / timer made to experiment with the different feature built into the Texas Instruments MSP-EXP432P401R Development kit with the CC3100BOOST module and Educational BoosterPack MKII

## Start:

- Plug the power and the start up senquence begins 
- First menù allows to choose between " 1 connect " and " 2 no internet " (use the top or lower button to select the option)
    - " 1 connect " tries to connect to the internally saved WiFi settings (in the file Cayenne.ino)
    - " no internet " skips the connection, IoT Dashboard will not be available

## Main functionalities:

- To switch between the 2 modes while the screen is in "Girami per iniziare" State press simultaniusly the two buttons a text will appear saying the current selected mode

### Accelerometer Mode:
- screen shows the text "girami per iniziare", no cloks are running
- rotating the screen to any of the 4 sides starts a clock
- changing side resets the time
- while the timer is running pressing both buttons resets the timer
- holding the top button and moving the joystick up or down fast forwords or reverse the time 
- pressing the top button stops and restarts the clock

### Joystick Mode:
- screen shows the text "girami per iniziare", no cloks are running
- use joystick to select the side to run the clock
- press lower button brings back to center
- while the timer is running pressing both buttons resets the timer
- holding the top button and moving the joystick up or down fast forwords or reverse the time (BUG up in minuts down in seconds and clock stops)
- pressing the top button stops and restarts the clock 

## Side Functionalities:

- the rgb led rainbow cicles repetedly
- clapping hads or loud noises will toggle the white light on or off (calibration of the acustic noise level is done during start up, avoid loud sounds )

## IoT Dashboard with Cayenne:

If WiFi connection is Succesfull you can access the device Dashboard on https://cayenne.mydevices.com/ (requiers account and device association and to build the dashboard)

- 3 sliders for changing the RGB value of the LED
- Microphone light status monitoring (NOTE it's correct only when there is good connection)
- Current indicated time is shown (NOTE might take some time to refresh to the correct value)
- Time alive in seconds to check connection, if it incremets every seconds informations are real time and correct

