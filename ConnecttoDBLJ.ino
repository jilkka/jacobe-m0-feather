/*

 This example connects to an unencrypted WiFi network.
 Then it prints the  MAC address of the WiFi shield,
 the IP address obtained, and other network details.

 Circuit:
 * WiFi shield attached

 created 13 July 2010
 by dlf (Metodo2 srl)
 modified 31 May 2012
 by Tom Igoe
 */
#include <SPI.h>
#include <Wire.h>
#include <WiFi101.h>
#include <Adafruit_SSD1306.h>

#include "arduino_secrets.h" 
///////please enter your sensitive data in the Secret tab/arduino_secrets.h
char ssid[] = SECRET_SSID;        // your network SSID (name)
char pass[] = SECRET_PASS;    // your network password (use for WPA, or use as key for WEP)
int status = WL_IDLE_STATUS;     // the WiFi radio's status

// 32u4, M0, M4, nrf52840 and 328p
  #define BUTTON_A  9
  #define BUTTON_B  6
  #define BUTTON_C  5
  #define WIRE Wire
  Adafruit_SSD1306 display = Adafruit_SSD1306(128, 32, &WIRE);

#define VBATPIN A7

int pingResult;

void setup() {
  //Configure pins for Adafruit ATWINC1500 Feather
  WiFi.setPins(8,7,4,2);

  //Initialize serial and wait for port to open:
  Serial.begin(9600);
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C); // Address 0x3C for 128x32

  pinMode(BUTTON_A, INPUT_PULLUP);
  pinMode(BUTTON_B, INPUT_PULLUP);
  pinMode(BUTTON_C, INPUT_PULLUP);

// Show image buffer on the display hardware.
  // Since the buffer is intialized with an Adafruit splashscreen
  // internally, this will display the splashscreen.
  display.display();
  delay(1000);

  // Clear the buffer.
  display.clearDisplay();
  display.display();

  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(0,0);
  display.display();

  // check for the presence of the shield:
  if (WiFi.status() == WL_NO_SHIELD) {
    display.println("WiFi shield not present");
    display.display();

    // don't continue:
    while (true);
  }

  // attempt to connect to WiFi network:
  while ( status != WL_CONNECTED) {
  
    display.println("Connecting to: ");
    display.print(ssid);
    // Connect to WPA/WPA2 network:
    status = WiFi.begin(ssid, pass);
  display.display();

    // wait 10 seconds for connection:
    delay(10000);
  }

  // you're connected now, so print out the data:
  display.clearDisplay();
  display.setCursor(0,0);
  display.println("You're connected to: ");
  display.print(ssid);
  display.display();
}

void loop() {
  if(!digitalRead(BUTTON_A)){
   printWiFiData();
  }
  if(!digitalRead(BUTTON_B)){
   printCurrentNet();
  }
  if(!digitalRead(BUTTON_C)){
   printPowerInfo();
  }
}

void printWiFiData() {
  // print your WiFi shield's IP address:
  IPAddress ip = WiFi.localIP();
  display.clearDisplay(); 
  display.setCursor(0,0);
  display.println("IP Address: ");
  display.println(ip);
  
  pingResult = WiFi.ping("www.google.com");
  if (pingResult >= 0){
    display.println("Internet Connected");
    display.print("Ping: ");
    display.print(pingResult);
    display.print(" ms");
  }
  else {
    display.print("No Internet Connection");
  }  
  display.display();
}

void printCurrentNet() {
  // print the SSID of the network you're attached to:
  display.clearDisplay(); 
  display.setCursor(0,0);
  display.println("SSID: ");
  display.println(WiFi.SSID());

  // print the received signal strength:
  long rssi = WiFi.RSSI();
  display.println("RSSI: ");
  display.print(rssi);
  display.display();
}

void printPowerInfo() {
  float measuredvbat = analogRead(VBATPIN);
  measuredvbat *= 2;    // we divided by 2, so multiply back
  measuredvbat *= 3.3;  // Multiply by 3.3V, our reference voltage
  measuredvbat /= 1024; // convert to voltage
  Serial.print(measuredvbat);
  display.clearDisplay(); 
  display.setCursor(0,0); 
  display.print("Input Voltage: ");
  display.print(measuredvbat);
  display.print(" V");
  display.display();
  }  
