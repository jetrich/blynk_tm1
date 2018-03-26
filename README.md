# blynk_tm1
Temperature / Humidity monitor built on ESP8266 with DHT22 and Serial OLED using local Blynk installation

Based on NodeMCU EXP8266 ESP-12E board http://amzn.to/2pxwlC0, OLED Module http://amzn.to/2pwC4I8, DHT22 sensor

Arduino Libraries:
ESP8266 addon: https://learn.sparkfun.com/tutorials/esp8266-thing-hookup-guide/installing-the-esp8266-arduino-addon
Arduino master: https://codeload.github.com/esp8266/Arduino/zip/master
Blynk: https://codeload.github.com/blynkkk/blynk-library/zip/master
adafruit: https://github.com/adafruit/Adafruit_Sensor
adafruit: https://github.com/adafruit/DHT-sensor-library
esp8266: https://github.com/esp8266/Arduino
SimpleTimer: http://playground.arduino.cc/Code/SimpleTimer


The intention of this project is to have a DHT22 sensor constantly monitor the temperature and humidity in a room and send an email/SMS
message when the readings are out of range. A screen with a constant readout of the readings is desired as well. A local Blynk 
installation will be utilized and the readings shall be logged to an on-site mysql/mariadb database.

Releases
v.1 - Basic operation reporting the temperature and humidity to the server and relay to app