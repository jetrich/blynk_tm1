#define BLYNK_PRINT Serial // Comment this out to disable prints and save space
//#define BLYNK_DEBUG 4
#include <SPI.h>;
#include <ESP8266WiFi.h>;
#include <BlynkSimpleEsp8266.h>;
#include <SimpleTimer.h>;
#include <DHT.h>;

#define DHTPIN 2 // What digital pin we're connected to

WidgetTerminal terminal(V0); // Set port number for Terminal

char auth[] = "";                // Auth token (Projct Settings page)
char ssid[] = "";                // Wifi SSID
char pass[] = "";                // WIFI Password ("" for open network)
IPAddress blynk_server(X,X,X,X); // IP Address for local blynk server

// Uncomment whatever type you're using!
//#define DHTTYPE DHT11 // DHT 11
#define DHTTYPE DHT22 // DHT 22, AM2302, AM2321
//#define DHTTYPE DHT21 // DHT 21, AM2301

DHT dht(DHTPIN, DHTTYPE);
SimpleTimer timer;

void send_sensor()
{
 // This function sends Arduino's up time every second to Virtual Pin (5, 6, 7, and 8).
 // In the app, Widget's reading frequency should be set to PUSH. This means
 // that you define how often to send data to Blynk App.
 float h = dht.readHumidity();
 //float t = dht.readTemperature(); // Celsius 
 float t = dht.readTemperature(true); // Fahrenheit

 if (isnan(h) || isnan(t)) {
 Serial.println("Failed to read from DHT sensor!");
 return;
 }
 // You can send any value at any time.
 // Please don't send more that 10 values per second.
 Blynk.virtualWrite(V5, h); // Humidity for gauge
 Blynk.virtualWrite(V6, t); // Temperature for gauge
 Blynk.virtualWrite(V7, h); // Humidity for graph
 Blynk.virtualWrite(V8, t); // Temperature for graph
 Serial.print(F("T: ")); Serial.print(t); Serial.print(F(", H: ")); Serial.println(h);
 }

void sent_serial()
{
  // Sent serial data to Blynk terminal - Unlimited string read
  String content = ""; // null string constant (empty string)
  char character;
  while(Serial.available()) {
    character = Serial.read();
    content.concat(character);
  }
  if (content != "") {
    Blynk.virtualWrite (V0, content);
  }
}

void setup()
{
 Serial.begin(115200); // See the connection status in Serial Monitor
 Blynk.begin(auth, ssid, pass, blynk_server, 8080);

 dht.begin();
 
 // Setup a function to be called every second
 timer.setInterval(2000L, send_sensor);
 timer.setInterval(500L, sent_serial);
}

void loop()
{
 Blynk.run(); // Initiates Blynk
 timer.run(); // Initiates SimpleTimer
}

