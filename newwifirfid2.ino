/*
 *  This sketch sends data via HTTP GET requests to data.sparkfun.com service.
 *
 *  You need to get streamId and privateKey at data.sparkfun.com and paste them
 *  below. Or just customize this script to talk to other HTTP servers.
 *
 */
#include <SPI.h>
#include <ESP8266WiFi.h>
#include <MFRC522.h>
const char* ssid     = "4G";
const char* password = "1234567890";
#define SS_PIN 2
#define RST_PIN 0
const char* host = "192.168.0.3";
const char* streamId   = "....................";
const char* privateKey = "....................";
MFRC522 mfrc522(SS_PIN, RST_PIN); 
byte readCard[4];
int _RFID;
String rfo;
void setup() {
 
  Serial.begin(115200);
  delay(10);

  // We start by connecting to a WiFi network

  Serial.println();
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);
  
  WiFi.begin(ssid, password);
  
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("");
  Serial.println("WiFi connected");  
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());

    SPI.begin();      // Init SPI bus
  mfrc522.PCD_Init(); // Init MFRC522 card
  Serial.println("Scan PICC to see UID and type...");
 
}

int value = 0;

void loop() {
 if ( ! mfrc522.PICC_IsNewCardPresent()) {
    // Serial.println("a");
    return;
  }

  // Select one of the cards
 if ( ! mfrc522.PICC_ReadCardSerial()) {
   // Serial.println("b");
    return;
}

  Serial.print("connecting to ");
  Serial.println(host);
  
  // Use WiFiClient class to create TCP connections
  WiFiClient client;
  const int httpPort = 11000;
  if (!client.connect(host, httpPort)) {
    Serial.println("connection failed");
    return;
  }
  
 
  
   
   Serial.println("Scanned PICC's UID:");
 rfo="";
 byte *buffer=mfrc522.uid.uidByte;
   byte bufferSize=mfrc522.uid.size;
 for (byte i = 0; i < bufferSize; i++) {

    _RFID = buffer[i], DEC;
      rfo +=String(_RFID);
       
    
         
  }
//client.println(rfo.toInt());
  client.println(rfo);
 Serial.print(rfo);
  tone(5,4000,1000);
  Serial.println("");
 mfrc522.PICC_HaltA(); // Stop reading
 
}

