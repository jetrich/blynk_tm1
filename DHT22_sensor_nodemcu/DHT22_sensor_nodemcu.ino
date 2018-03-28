#define BLYNK_PRINT Serial // Comment this out to disable prints and save space
//#define BLYNK_DEBUG 4
#include <SPI.h>;
#include <ESP8266WiFi.h>;           // Use this for WiFi instead of Ethernet.h
#include <BlynkSimpleEsp8266.h>;
#include <SimpleTimer.h>;
#include <DHT.h>;
#include <MySQL_Connection.h>;
#include <MySQL_Cursor.h>;

#define DHTPIN 2 // What digital pin we're connected to

WidgetTerminal terminal(V0); // Set port number for Terminal

char debug[] = "no";                              // yes/no additional information via serial for debugging

char auth[] = ""; // Auth token (Projct Settings page)
char ssid[] = "";                                 // Wifi SSID
char pass[] = "";                                 // WIFI Password ("" for open network)
IPAddress blynk_server(X,X,X,X);                  // IP Address for local blynk server
const int blynk_port = 8080;                      // Specify blynk port
const int t_gauge = V6;                           // Blynk virtual port for temperature gauge
const int h_gauge = V5;                           // Blynk virtual port for humidity gauge
const int t_chart = V8;                           // Blynk virtual port for temperature chart
const int h_chart = V7;                           // Blynk virtual port for humidity chart
const int b_term = V0;                            // Blynk virtual port for terminal
const int sensor_delay = 2000L;                   // Time delay for sensor read (must end with "L")
const int serial_delay = 500L;                    // Time delay for serial read (must end with "L")

char log_db[] = "yes";                            // yes/no for database logging
IPAddress db_server(X,X,X,X);                     // Database server IP address
const int db_port = 3306;                         // Database server port
char db_user[] = "";                              // Database user
char db_pass[] = "";                              // Database password
char db_name[] = "";                              // Database name
char db_table[] = "";                             // Table name
WiFiClient client;                                // Use this for WiFi instead of EthernetClient
MySQL_Connection conn((Client*)&client); 

// Uncomment whatever type you're using!
//#define DHTTYPE DHT11   // DHT 11
#define DHTTYPE DHT22     // DHT 22, AM2302, AM2321
//#define DHTTYPE DHT21   // DHT 21, AM2301

DHT dht(DHTPIN, DHTTYPE);
SimpleTimer timer;

void sent_serial()
{
  // Sent serial data to Blynk terminal - Unlimited string read
  String content = ""; // null string constant (empty string)
  char character;
  while(Serial.available()) 
  {
    character = Serial.read();
    content.concat(character);
  }
  if (content != "") 
  {
    Blynk.virtualWrite (b_term, content);
  }
}

void send_sensor()
{
 // This function sends Arduino's up time every second to Virtual Pin (5, 6, 7, and 8).
 // In the app, Widget's reading frequency should be set to PUSH. This means
 // that you define how often to send data to Blynk App.
 float h = dht.readHumidity();
 //float t = dht.readTemperature(); // Celsius 
 float t = dht.readTemperature(true); // Fahrenheit

 if (isnan(h) || isnan(t)) 
 {
  Serial.println("Failed to read from DHT sensor!");
  return;
 }
 // You can send any value at any time.
 // Please don't send more that 10 values per second.
 Blynk.virtualWrite(h_gauge, h); // Humidity for gauge
 Blynk.virtualWrite(t_gauge, t); // Temperature for gauge
 Blynk.virtualWrite(h_chart, h); // Humidity for chart
 Blynk.virtualWrite(t_chart, t); // Temperature for chart
 Serial.print(F("T: ")); Serial.print(t); Serial.print(F(", H: ")); Serial.println(h); // Feedback via serial
 if(strcmp(log_db, "yes") == 0)
 {
  if(strcmp(debug, "yes") == 0)
  {
   Serial.println(F("Log to database: yes"));
  }
  char sql_query[255];
  sprintf(sql_query, "INSERT INTO %s.%s (Temperature, Humidity) VALUES (%f, %f)",db_name,db_table,t,h);
  if(strcmp(debug, "yes") == 0)
  {
   Serial.println(sql_query);
  }
  MySQL_Cursor *cur_mem = new MySQL_Cursor(&conn);
  cur_mem->execute(sql_query);
 }
 else
 {
  if(strcmp(debug, "yes") == 0)
  {
   Serial.println(F("Log to database: no"));
  }
 }
}

void setup()
{
 Serial.begin(115200); // See the connection status in Serial Monitor
 Blynk.begin(auth, ssid, pass, blynk_server, blynk_port);
 if(strcmp(log_db, "yes") == 0)
 {
  Serial.println("Connecting to SQL... ");
  if (conn.connect(db_server, db_port, db_user, db_pass)) 
  {
    Serial.println("OK."); // Success message
  }
 }
 else 
 {
   Serial.println("FAILED!!!!"); // Failure message
 }

 dht.begin();
 
 // Setup a function to be called every second
 timer.setInterval(sensor_delay, send_sensor);
 timer.setInterval(serial_delay, sent_serial);
}

void loop()
{
 Blynk.run(); // Initiates Blynk
 timer.run(); // Initiates SimpleTimer
}

