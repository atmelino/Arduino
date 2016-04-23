
#include <Wire.h>
#include <LibHumidity.h>
#include <SPI.h>
#include <Ethernet.h>
#include "webpage.h"
#include "Parser.h"
#include "Variables.h"


// Enter a MAC address and IP address for your controller below.
// The IP address will be dependent on your local network:
byte mac[] = { 
  //  0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED };
  0x00, 0xAA, 0xBB, 0xCC, 0xDE, 0x02 };

IPAddress arduinoip(11,0,0, 177);
IPAddress serverip(11,0,0,100 );
EthernetServer server(80); // (port 80 is default for HTTP)
LibHumidity libhumidity = LibHumidity(0);

char buffer[100];

//byte varnumber1, varnumber2, varnumber3, varnumber4;
byte s1,s2,s3,s4;
int reqType=R_NONE;
int parsenumber=0; // variable value retrieved
long seconds, lastseconds;
int dots;
int intervalPHP=5;
int intervalPage=10;
//boolean traOnOff=false;
boolean traOnOff=true;
char serverscript[50]="/arduinoTempHumid/ArduinoCall.php";
//int temperature;
//int humidity;
float ftemperature;
float fhumidity;
char tBuffer[10];
char hBuffer[10];  

extern PROGMEM const char *string_table[];
extern PROGMEM const char *script_table[];


void setup() {
  // Open serial communications and wait for port to open:
  Serial.begin(9600);
  while (!Serial) {
    ; // wait for serial port to connect. Needed for Leonardo only
  }
  Serial.println("Program: networkSensor 03-04-2013");


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

  s1=serverip[0];
  s2=serverip[1];
  s3=serverip[2];
  s4=serverip[3];

  // modern device sensor
  pinMode(16, OUTPUT);
  digitalWrite(16, LOW);  //GND pin
  pinMode(17, OUTPUT);
  digitalWrite(17, HIGH); //VCC pin
  //Serial.println("Program: PHP_request 01-28-2013");
  //Serial.print("Arduino IP is ");
  //Serial.println(Ethernet.localIP());
}


void loop() 
{
  // no client: time functions
  delay(1);
  timerFunc();


  // listen for incoming clients
  EthernetClient client = server.available();
  if (client) 
  {
    Serial.println("new client");
    // an http request ends with a blank line
    boolean currentLineIsBlank = true;

    while (client.connected()) 
    {
      if (client.available()) 
      {
        char c = client.read();
        Serial.write(c);
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
      //Serial.println("GET Request");
      //s1=varnumber1;
      //s2=varnumber2;
      //s3=varnumber3;
      //s4=varnumber4;
      printVariables();
      serverip=IPAddress(s1,s2,s3,s4);
      printWebpage(client);
    }

    // close the connection:
    client.stop();
    Serial.println("client disonnected");
    Serial.println("----------");

  }
}

boolean timerFunc()
{
  seconds=millis()/1000;

  if(seconds-lastseconds>0){
    Serial.print(".");
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
  //temperature = 5;
  //humidity = 4;
  ftemperature =libhumidity.GetTemperatureF();
  fhumidity = libhumidity.GetHumidity();
  pre=ftemperature;
  post=int(100.0*ftemperature)%100;
  sprintf(tBuffer,"%d.%d",pre,post);
  pre=fhumidity;
  post=int(100.0*fhumidity)%100;
  sprintf(hBuffer,"%d.%d",pre,post);
 
 
  //Serial.print("Humidity: ");
  //Serial.print(fhumidity);
  //Serial.println();
  //Serial.print("Temperature: ");
  //Serial.print(tBuffer);
  //Serial.print(" Humidity: ");
  //Serial.print(hBuffer);
  //Serial.println();
}



void printWebpage(EthernetClient client){

  int num=100;
  for(int i=0;i<num;i++){

    strcpy_P(buffer, (char*)pgm_read_word(&(string_table[i]))); // Necessary casts and dereferencing, just copy. 

    if(strncmp(buffer,"<html",4)==0)
    {
      sprintf(buffer,"<meta http-equiv=\"refresh\" content=\"%i\">",intervalPage);
      client.println(buffer);
    }

    if(strncmp(buffer,"<body",4)==0)
    {
      //Serial.println("body");
      client.println(buffer);
      updateWebPageFields(client,s1,s2,s3,s4); // changes buffer
    }
    //Serial.print(i);
    //Serial.print(" ");
    //Serial.println( buffer );
    client.println(buffer);

    if(strcmp(buffer,"</html>")==0)
    {
      break;
    }        

  }
}


boolean updateWebPageFields(EthernetClient client,byte s1, byte s2, byte s3, byte s4)
{
  int numj=6;
  for(int j=0;j<numj;j++){
    strcpy_P(buffer, (char*)pgm_read_word(&(script_table[j]))); 

    if(j!=3)
      client.println(buffer);
    else{
      sprintf(buffer,"document.getElementById(\"bti\").value = '%i';",seconds);
      client.println(buffer);
      sprintf(buffer,"document.getElementById(\"iwp\").value = '%i';",intervalPage);
      client.println(buffer);
      //getTemperatureHumidity();
      sprintf(buffer,"document.getElementById(\"tem\").value = '%s';",tBuffer);
      client.println(buffer);
      sprintf(buffer,"document.getElementById(\"hum\").value = '%s';",hBuffer);
      client.println(buffer);
      sprintf(buffer,"document.getElementById(\"ip1\").value = '%i';",s1);
      client.println(buffer);
      sprintf(buffer,"document.getElementById(\"ip2\").value = '%i';",s2);
      client.println(buffer);
      sprintf(buffer,"document.getElementById(\"ip3\").value = '%i';",s3);
      client.println(buffer);
      sprintf(buffer,"document.getElementById(\"ip4\").value = '%i';",s4);
      client.println(buffer);
      sprintf(buffer,"document.getElementById(\"fre\").value = '%i';",intervalPHP);
      client.println(buffer);
      sprintf(buffer,"document.getElementById(\"scr\").value = '%s';",serverscript);
      client.println(buffer);
      if(traOnOff==true){

        //Serial.println("traOnOff true");
        client.println("document.getElementById(\"traOn\").checked = true;");
        client.println("document.getElementById(\"traOff\").checked = false;");
      }
      else{
        //Serial.println("traOnOff false");
        client.println("document.getElementById(\"traOn\").checked = false;");
        client.println("document.getElementById(\"traOff\").checked = true;");
      }

    }  
  }
}


boolean sendDataPHP() {
  EthernetClient client;

  // attempt to connect, and wait a millisecond:
  Serial.print("connecting to ");
  Serial.println(serverip);
  if (client.connect(serverip, 80)) {
    Serial.println("sending temperature");
    getTemperatureHumidity();
    delay(50);
    sprintf(buffer,"GET %s?t=%s&h=%s",serverscript,tBuffer,hBuffer);
    client.println(buffer);
    client.println();
    Serial.println(buffer);
    client.stop();

    //char tBuffer[16];
    //char hBuffer[16];  
    //dtostrf(temperature,8,2,tBuffer); 
    //dtostrf(humidity,8,2,hBuffer); 
    //sprintf(buffer,"GET /arduino/arduino_push_output.php?t=%s&h=%s",tBuffer,hBuffer);
    //client.println(buffer);

  }
  return true;
}


void printVariables()
{
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































