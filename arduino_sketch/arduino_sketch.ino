#include "Adafruit_SI1145.h"
#include "rn2xx3.h"
#include <SoftwareSerial.h>
#include <Wire.h>
#include <ESP8266WiFi.h>

//#define D4 2
//#define D5 14
//#define D6 12
//#define D7 13
#define RST D7
#define RainPIN D4

SoftwareSerial mySerial(D6, D5); // RX, TX

//create an instance of the rn2483 library,
//giving the software UART as stream to use,
//and using LoRa WAN
rn2xx3 myLora(mySerial);


Adafruit_SI1145 uv = Adafruit_SI1145();


// the setup routine runs once when you press reset:
void setup() {
  //lets waste less energy
  WiFi.forceSleepBegin();
  delay (10);


  // Open serial communications and wait for port to open:
  Serial.begin(9600);
  mySerial.begin(9600);
  delay(1);
  
  Serial.println("Startup");


if (! uv.begin()) {
    Serial.println("Can't find light sensor (GY1145)");
}
else Serial.println("GY1145 light sensor found");




  //reset rn2483
  pinMode(RST, OUTPUT);
  digitalWrite(RST, LOW);
  delay(500);
  digitalWrite(RST, HIGH);

  //initialise the rn2483 module
  myLora.autobaud();
  
  //print out the HWEUI so that we can register it via ttnctl
  Serial.println("When using OTAA, register this DevEUI: ");
  Serial.println(myLora.hweui());
  Serial.println("RN2483 version number:");
  Serial.println(myLora.sysver());


  myLora.setFrequencyPlan(TTN_EU);
//  Serial.println(myLora.sendRawCommand("radio set pwr 15"));
//  Serial.println(myLora.sendRawCommand("radio set sf sf12"));
//  Serial.println(myLora.sendRawCommand("radio set cr 4/8"));
//  Serial.println(myLora.sendRawCommand("radio set bw 125"));
  Serial.println(myLora.sendRawCommand("mac set dr 0"));
  Serial.println(myLora.sendRawCommand("mac set pwridx 1"));

  
String AppEUI="70B3D57EF0003876";
String AppKey= "707DE06A996CD71708FF6EE95D1581A4";
String DeviceEUI = "00E268DA4B2887B3";

  //OTAA: init(String AppEUI, String AppKey);
  Serial.print("Connecting ");
//  bool result = myLora.initOTAA(AppEUI, AppKey, DeviceEUI);/
  bool result = myLora.initABP("26011DB3", "6CDA909E0683EF4FA26C0FA7B4A5BC0E", "9A1AE4093749510BC43E9F3F04602118");

  Serial.println();
  Serial.println("Device connected!");
  delay(2000);
}

// the loop routine runs over and over again forever:
void loop() {

  Serial.println("===================");
  int Visible=uv.readVisible(), IR=uv.readIR();
  Serial.print("Vis: "); Serial.println(Visible);
  Serial.print("IR: "); Serial.println(IR);
  
  int UVindex = uv.readUV();
  UVindex;  
  Serial.print("UV: "); Serial.println(UVindex/100.0);

bool rain=1-digitalRead(RainPIN);
int rainAnalog = 1023-analogRead(A0);

    //sending as less data as possible
byte toSend[3]; //<20b payload
toSend[0] = rain<<7|rainAnalog/8;
toSend[1] = UVindex/10;
toSend[2] = Visible/257;

Serial.print(toSend[0]);
Serial.print(toSend[1]);
Serial.println(toSend[2]);

myLora.txBytes(toSend, 3);

    for (int i=0; i<(5*60); i++) delay(1000); //Send every minute (maybe you need to tune this)
}
