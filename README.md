# blynk_tm1
Temperature / Humidity monitor built on ESP8266 with DHT22 and Serial OLED using local Blynk installation

Code derived from other samples
http://www.instructables.com/id/ESP8266-12-blynk-wireless-temperature-e-humidity-D-1/
https://community.blynk.cc/t/blynk-esp8266-dht22/2715
https://iot-playground.com/blog/2-uncategorised/80-esp8266-wifi-ds18b20-temperature-sensor-easyiot-cloud-rest-api-v1-and-email-alarm

The intention of this project is to have a DHT22 sensor contstantly monitor the temperature and humidity in a room and send an email/SMS
message when the readings are out of range. A screen with a constant readout of the readings is desired as well. A local Blynk 
installation will be utilized and the readings shall be logged to an on-site mysql/mariadb database.
