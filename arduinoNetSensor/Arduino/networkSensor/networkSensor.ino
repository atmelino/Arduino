
#include <Wire.h>
#include <LibHumidity.h>
#include <SPI.h>
#include <Ethernet.h>
#include <EEPROM.h>
#include "webpage.h"
#include "Parser.h"
#include "Variables.h"
#include "Messages.h"
#define MAX_STRING 50


// Enter a MAC address and IP address for your controller below.
// The IP address will be dependent on your local network:
byte mac[] = { 
  0x00, 0xAA, 0xBB, 0xCC, 0xDE, 0x02 };

IPAddress arduinoip(11 ,0,0, 17);
//IPAddress serverip(11,0,0,100 );
//IPAddress arduinoip(192,168,5,14);
IPAddress serverIP;
EthernetServer server(80); // (port 80 is default for HTTP)
LibHumidity libhumidity = LibHumidity(0);

char buffer[100];
char buffer2[100];

byte s1,s2,s3,s4;
int reqType=R_NONE;
int parsenumber=0; // variable value retrieved
long seconds, lastseconds;
int dots;
int intervalPHP=5;
int intervalPage=10;
boolean traOnOff=false;
//char serverscript[MAX_STRING]="script";
//char serverscript[MAX_STRING]="/arduinoNetSensor/html/ArduinoCall.phpmore";
//char arduinoID[MAX_STRING]="office02";
char serverscript[MAX_STRING];
char arduinoID[MAX_STRING];
float ftemperature;
float fhumidity;
char tBuffer[10];
char hBuffer[10]; 
int pageMessageNumber;
char version[]="03-20-2013";

extern PROGMEM const char *string_table[];
extern PROGMEM const char *script_table[];


void setup() {
  // Open serial communications and wait for port to open:
  Serial.begin(9600);
  while (!Serial) {
    ; // wait for serial port to connect. Needed for Leonardo only
  }
  Serial.print("Program: networkSensor ");
  Serial.println(version);

  // start the Ethernet connection and the server:
  Ethernet.begin(mac, arduinoip);
  //Ethernet.begin(mac);    // DHCP

  // print your local IP address:
  Serial.print("My IP address: ");
  for (byte thisByte = 0; thisByte < 4; thisByte++) {
    // print the value of each byte of the IP address:
    Serial.print(Ethernet.localIP()[thisByte], DEC);
    Serial.print("."); 
  }
  Serial.println();

  server.begin();  

  EEPROMReadValues();
  Serial.println("Variables read from EEPROM:");
  printVariables();
  
  // modern device sensor
  pinMode(16, OUTPUT);
  digitalWrite(16, LOW);  //GND pin
  pinMode(17, OUTPUT);
  digitalWrite(17, HIGH); //VCC pin
}


void loop() 
{
  // no client: time functions
  delay(1);
  timerFunction();


  // listen for incoming clients
  EthernetClient client = server.available();
  if (client) 
  {
    //Serial.println("new client");
    // an http request ends with a blank line
    boolean currentLineIsBlank = true;

    while (client.connected()) 
    {
      if (client.available()) 
      {
        char c = client.read();
        //Serial.write(c);
        parser(c);
        //reqType=R_GET;
        // Wait until the request has been completely received before sending anything
        if (c == '\n' && currentLineIsBlank) {
          break;
          //resetParser2();
        }

        if (c == '\n') {
          // you're starting a new line
          currentLineIsBlank = true;
        } 
        else if (c != '\r') {
          // you've gotten a character on the current line
          currentLineIsBlank = false;
        }

      }
    }
    // give the web browser time to receive the data
    delay(1);
    // Request has been completely received!
    //Serial.print("Request type ");
    //Serial.println(reqType);

    if(reqType==R_POST){
      //Serial.println("POST Request");
      sendDataPHP();
    }

    if(reqType==R_GET){
      //printVariables();
      serverIP=IPAddress(s1,s2,s3,s4);
      printWebpage(client);
    }

    // close the connection:
    client.stop();
    //Serial.println("client disconnected");
    //Serial.println("----------");

  }
}

boolean timerFunction()
{
  seconds=millis()/1000;

  if(seconds-lastseconds>0){
    Serial.print(".");
    //Serial.println(serverIP);
    EEPROMSaveValues();

    getTemperatureHumidity();
    if(seconds%intervalPHP==0){
      if(traOnOff==true)
      {
        sendDataPHP();
      }
    }

    lastseconds=seconds;
  }
  // line break
  dots++;  
  if(dots>40){  
    //Serial.println("");
    dots=0;
  }
}

boolean getTemperatureHumidity()
{
  int pre,post;

  //temperature = analogRead(5);
  //humidity = analogRead(4);
  ftemperature =libhumidity.GetTemperatureF();
  fhumidity = libhumidity.GetHumidity();
  pre=ftemperature;
  post=int(100.0*ftemperature)%100;
  sprintf(tBuffer,"%d.%d",pre,post);
  pre=fhumidity;
  post=int(100.0*fhumidity)%100;
  sprintf(hBuffer,"%d.%d",pre,post);
}


boolean sendDataPHP() {
  EthernetClient client;

  // attempt to connect, and wait a millisecond:
  serverIP=IPAddress(s1,s2,s3,s4);
  Serial.print("connecting to ");
  Serial.println(serverIP);
  if (client.connect(serverIP, 80)) {
    Serial.println("sending temp/humid");
    getTemperatureHumidity();
    delay(50);
    sprintf(buffer,"GET %s?i=ARD%s&t=%s&h=%s",serverscript,arduinoID,tBuffer,hBuffer);
    client.println(buffer);
    client.println();
    Serial.println(buffer);
    client.stop();
  }
  return true;
}


void printVariables()
{
  Serial.println("Variables:");
  Serial.print("arduinoID= ");
  Serial.println(arduinoID);
  Serial.print("intervalPage= ");
  Serial.println(intervalPage);
  sprintf(buffer,"IP=%i.%i.%i.%i",s1,s2,s3,s4);
  Serial.println(buffer);
  Serial.print("intervalPHP= ");
  Serial.println(intervalPHP);
  Serial.print("traOnOff= ");
  Serial.println(traOnOff);
  Serial.print("serverscript= ");
  Serial.println(serverscript);

}




