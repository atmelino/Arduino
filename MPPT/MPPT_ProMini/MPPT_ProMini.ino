#include <PWM.h>
#include <SDL_Arduino_INA3221.h>
#include <Wire.h>
#include <Adafruit_RGBLCDShield.h>
#include <utility/Adafruit_MCP23017.h>
#include <Adafruit_SleepyDog.h>
#include <ArduinoJson.h>

Adafruit_RGBLCDShield lcd = Adafruit_RGBLCDShield();

// Options
#define BLINK 0
#define SERIAL 1
#define LCD 1
#define SLEEPMODE 0
#define BUTTON_PWM_MPPT BUTTON_SELECT       // DIP switch 1: 0=MPPT 1=depends on DIP switch 2
#define BUTTON_PWM_POT_SERIAL BUTTON_RIGHT  // DIP switch 2: 1=POT 0=SERIAL
#define BUTTON_SW_VERSION BUTTON_DOWN  // DIP switch 3
#define BUTTON_UNUSED BUTTON_UP  // DIP switch 4
#define MAXPWM 210
#define MAXVOLTAGE 8.4
#define PI_ON_VOLTAGE 7.8
#define PI_OFF_VOLTAGE 7.6
#define SHUTDOWNVOLTAGE 7.5
#define SWVERSION "SW 2016-09-23 17:40"

// Wiring:
#define PWM_OUT 3            // PWM signal pin 
#define PWM_ENABLE_PIN 4    // pin used to control shutoff function of the IR2104 MOSFET driver
#define RELAY_PIN (5)
#define RELAY_PI_PIN (6)
#define CHARGE_LED (7)
#define ARDUINO_LED 13;      // pin for the built-in LED


// These #defines make it easy to set the backlight color
#define WHITE 0x7

int potentiometerPin = A0;    // select the input pin for the potentiometer
int sensorValue = 0;  // variable to store the value coming from the sensor
int incomingByte = 200;   // for incoming serial data

int32_t frequency = 80000; //frequency (in Hz)
byte pulseWidth = 0;
byte requestedPulseWidth = 130;
byte targetPulseWidth;
float pwhist[3] = {1000., 1000., 1000.};
static char line[4][21] = {"                    ", "                    ", "                    ", "                    "};

boolean LED_ON_OFF = true;
boolean MODE_MPPT, MODE_POT, MODE_SER;

SDL_Arduino_INA3221 ina3221;

// the three channels of the INA3221
#define CHANNEL_SOLAR 2 // solar panel on INA channel 3, array position 2
#define CHANNEL_BATTERY 1 // lipo battery on INA channel 2, array position 1



int count = 0;

void setup()
{

  // set all digital pins to output, even if unused, not float= save power
  for (int i = 0; i < 20; i++)
    pinMode(i, OUTPUT);
  // except for potentiometer reading
  pinMode(potentiometerPin, INPUT);


  Serial.begin(9600);
  //Serial.begin(112500);
  Serial.setTimeout(500);  // only need to be set once
  Serial.println("no  Volt     mA   mW     Volt     mA   mW   eff    PWM   target");

  // voltage and current sensor
  ina3221.begin();

  // MPPT LED
  digitalWrite(CHARGE_LED, HIGH);

  // enable MOSFET driver chip
  digitalWrite(PWM_ENABLE_PIN, HIGH);

  // PWM
  pulseWidth = 128;
  InitTimersSafe();
  bool success = SetPinFrequencySafe(PWM_OUT, frequency);


  // LCD
  lcd.begin(20, 4);
  lcd.setCursor(0, 0);            // set the LCD cursor   position
  lcd.print("MPPT");  // print a simple message on the LCD
  //lcd.setBacklight(WHITE);
  lcd.setBacklight(0);

}


void loop()
{
  float sv[3], bv[3], cmA[3], lv[3], pw[3];
  float powerConsumption;
  int ontime, offtime;
  StaticJsonBuffer<200> jsonBuffer;

  count++;

  for (int i = 0; i < 3; i++) {
    bv[i] = ina3221.getBusVoltage_V(i + 1);
    sv[i] = ina3221.getShuntVoltage_mV(i + 1);
    cmA[i] = ina3221.getCurrent_mA(i + 1);
    lv[i] = bv[i] + (sv[i] / 1000);
    pw[i] = bv[i] * cmA[i];
  }

  // Is battery voltage high enough to power Arduino?
  if (bv[CHANNEL_BATTERY] > SHUTDOWNVOLTAGE) {
    lcd.setCursor(10, 3);
    lcd.print("batt ok ");
    digitalWrite(RELAY_PIN, HIGH);
  } else {
    lcd.setCursor(10, 3);
    lcd.print("batt low");
    digitalWrite(RELAY_PIN, LOW);
  }

  // Is battery voltage high enough to power Pi?
  if (bv[CHANNEL_BATTERY] > PI_ON_VOLTAGE) {
    digitalWrite(RELAY_PI_PIN, HIGH);
  }
  if (bv[CHANNEL_BATTERY] < PI_OFF_VOLTAGE) {
    digitalWrite(RELAY_PI_PIN, LOW);
  }

  // check if pi is running
  pwhist[0] = pwhist[1];
  pwhist[1] = pwhist[2];
  pwhist[2] = pw[CHANNEL_SOLAR] + pw[CHANNEL_BATTERY];
  //Serial.print(pwhist[0]);
  //Serial.print(" ");
  //Serial.print(pwhist[1]);
  //Serial.print(" ");
  //Serial.print(pwhist[2]);
  //Serial.print(" ");

  // if 3 consecutive measurements below 900mW
  if (bv[CHANNEL_BATTERY] > PI_ON_VOLTAGE && pwhist[0] < 900.0 && pwhist[1] < 900.0 && pwhist[2] < 900.0 )
  {
    powerCyclePi();
    //lcd.setCursor(2, 17);
    //lcd.print("C+");
    line[2][16] = 'C';
    line[2][17] = '+';
  }
  else
  {
    //lcd.setCursor(2, 17);
    //lcd.print("C-");
    line[2][16] = 'C';
    line[2][17] = '-';
  }

  //Evaluate DIP switches
  uint8_t buttons = lcd.readButtons();
  MODE_MPPT = false;
  MODE_POT = false;
  MODE_SER = false;
  if (!(buttons & BUTTON_PWM_MPPT)) // means MPPT yes
  {
    //Serial.println("MPPT");
    MODE_MPPT = true;
  }
  else {
    if (buttons & BUTTON_PWM_POT_SERIAL)
    {
      MODE_POT = true;
    }
    else {
      MODE_SER = true;
    }
  }

  // Is sun shining?
  if (SLEEPMODE && bv[CHANNEL_SOLAR] < 9.5) {
    // No: go to sleep at night
    lcd.setCursor(0, 3);
    lcd.print("SLEEP ON ");

    int sleepMS = Watchdog.sleep();

    // first command after wakeup
    lcd.setCursor(0, 3);
    lcd.print("SLEEP OFF");


  }
  else {
    // Yes: charge battery
    //Serial.println("alive");


    if (MODE_MPPT)
    {
      lcd.setCursor(0, 3);
      lcd.print("MPPT MODE");

      requestedPulseWidth = MAXPWM;
    }

    if (MODE_POT)
    {
      // Set PWM duty cycle
      lcd.setCursor(0, 3);
      lcd.print("POT MODE ");
      // read potentiometer value
      sensorValue = analogRead(potentiometerPin);
      //Serial.println(sensorValue);
      requestedPulseWidth = sensorValue / 4;
    }

    if (MODE_SER)
    {
      char json[50];
      String str;
      lcd.setCursor(0, 3);
      lcd.print("SER MODE ");
      // send data only when you receive data:
      while (Serial.available() > 0) {
        // read the incoming byte:
        //incomingByte = Serial.read();
        // say what you got:
        //Serial.print("I received: ");
        //Serial.println(incomingByte);


        str = Serial.readStringUntil('\n');
        Serial.println(str);
      }
      str.toCharArray(json, 50);
      JsonObject& root = jsonBuffer.parseObject(json);


      if (!root.success()) {
        //Serial.println("parseObject() failed");
      }
      else
      {
        //{"PWM":213}
        int pwmint = root["PWM"];
        Serial.println(pwmint);
        incomingByte = (byte)pwmint;
      }


      requestedPulseWidth = incomingByte;
    }

    //Serial.println(requestedPulseWidth);
    if ( requestedPulseWidth > 244)
      requestedPulseWidth = 244;

    // calculate target PWM
    if (bv[CHANNEL_BATTERY] < MAXVOLTAGE)
      targetPulseWidth = requestedPulseWidth;
    if (bv[CHANNEL_BATTERY] >= MAXVOLTAGE)
      targetPulseWidth = 0;
    //Serial.print("computed targetPulseWidth: ");
    //Serial.println(targetPulseWidth);
  }


  // Change PWM if required
  if (pulseWidth < targetPulseWidth ) {
    if (abs(pulseWidth - targetPulseWidth) > 10)
      pulseWidth += 10;
    else
      pulseWidth++;
    pwmWrite(PWM_OUT, pulseWidth);
  }
  if (pulseWidth > targetPulseWidth ) {
    if (abs(pulseWidth - targetPulseWidth) > 10)
      pulseWidth -= 5;
    else
      pulseWidth--;
    pwmWrite(PWM_OUT, pulseWidth);
  }




  printValues(bv, cmA, pw) ;
  //Serial.println("after printValues()");

  if (buttons & BUTTON_SW_VERSION)
  {
    lcd.setCursor(0, 1);
    lcd.print(SWVERSION);
  }


  // yellow LED and loop period
  if (bv[CHANNEL_BATTERY] <= 7.5)
    ontime = 10;
  if (bv[CHANNEL_BATTERY] > 7.5 && bv[CHANNEL_BATTERY] <= 8.35)
    ontime = 2000 * (bv[CHANNEL_BATTERY] - 7.5);
  if (bv[CHANNEL_BATTERY] > 8.35)
    ontime = 1950;
  offtime = 2000 - ontime;
  //Serial.print(ontime);
  //Serial.print(" ");
  //Serial.println(offtime);
  digitalWrite(CHARGE_LED, HIGH);
  delay(ontime);
  digitalWrite(CHARGE_LED, LOW);
  delay(offtime);

} // end loop

void powerCyclePi() {
  delay(1000);
  digitalWrite(RELAY_PI_PIN, LOW);
  delay(1000);
  digitalWrite(RELAY_PI_PIN, HIGH);
}



void printValues(  float bv[], float cmA[], float pw[]) {
  static char bvstr[10];
  static char cmAstr[10];
  static char pwstr[10];
  static char pwmstr[10];
  static char tapwmstr[10];

  float eff = pw[CHANNEL_BATTERY] / pw[CHANNEL_SOLAR];

  if (LCD || SERIAL)
  {
    int i;
    i = CHANNEL_SOLAR;
    dtostrf(bv[i], 5, 2, bvstr);
    dtostrf(cmA[i], 7, 2, cmAstr);
    dtostrf(pw[i], 7, 2, pwstr);
    memcpy(line[0], bvstr, 5);
    line[0][5] = ' ';
    memcpy(&line[0][6], cmAstr, 6);
    line[0][12] = ' ';
    memcpy(&line[0][13], pwstr, 6);

    i = CHANNEL_BATTERY;
    dtostrf(bv[i], 5, 2, bvstr);
    dtostrf(cmA[i], 7, 2, cmAstr);
    dtostrf(pw[i], 7, 2, pwstr);
    memcpy(line[1], bvstr, 5);
    line[1][5] = ' ';
    memcpy(&line[1][6], cmAstr, 6);
    line[1][12] = ' ';
    memcpy(&line[1][13], pwstr, 6);

    dtostrf(pulseWidth, 5, 2, pwmstr);
    dtostrf(targetPulseWidth, 5, 2, tapwmstr);
    memcpy(line[2], pwmstr, 5);
    line[2][5] = ' ';
    memcpy(&line[2][6], tapwmstr, 6);
  }


  if (LCD)
  {
    lcd.setCursor(0, 0);
    lcd.print(line[0]);  // solar panel

    lcd.setCursor(0, 1);
    lcd.print(line[1]);  // MPPT output

    lcd.setCursor(0, 2);
    lcd.print(line[2]);  // buck converter output and battery input

  }

  if (SERIAL)
    printINA(count, line[0], line[1], eff, pulseWidth, targetPulseWidth);
}

void printINA(int count, char* line1, char* line2, float eff, float pulseWidth, float targetPulseWidth)
{

  Serial.print(count);
  Serial.print(" ");
  Serial.print(line1);
  Serial.print(" ");
  Serial.print(line2);
  Serial.print(" ");
  Serial.print(eff);
  Serial.print(" ");
  Serial.print(pulseWidth);
  Serial.print(" ");
  Serial.print(targetPulseWidth);
  Serial.println();

}


void printHEX(char* cp, int num)
{
  int i;
  for (i = 0; i < num; i++)
    Serial.print(cp[i], HEX);

}


void charcpy(char* from, char* to, int num)
{
  int i;
  for (i = 0; i < num; i++)
    to[i] = from[i];

}






