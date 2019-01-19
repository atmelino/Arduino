#include <PWM.h>
#include <SDL_Arduino_INA3221.h>
#include <Wire.h>
#include <Adafruit_RGBLCDShield.h>
#include <utility/Adafruit_MCP23017.h>
#include <Adafruit_SleepyDog.h>

Adafruit_RGBLCDShield lcd = Adafruit_RGBLCDShield();

// Options
#define BLINK 1
#define SERIAL 1
#define LCD 1
#define POTENTIOMETER 0
#define MAXPWM 210
#define MAXVOLTAGE 8.4
#define TAPEROFFVOLTAGE 8.35


// Wiring:
#define PIN_RESET 8
#define PIN_SCE   9
#define PIN_DC    10
#define PIN_SDIN  11
#define PIN_SCLK  12
#define PWM_OUT 3            // PWM signal pin 
#define PWM_ENABLE_PIN 4    // pin used to control shutoff function of the IR2104 MOSFET driver


// These #defines make it easy to set the backlight color
#define WHITE 0x7

int potentiometerPin = A0;    // select the input pin for the potentiometer
int ledPin = 13;      // select the pin for the LED
int sensorValue = 0;  // variable to store the value coming from the sensor

int32_t frequency = 80000; //frequency (in Hz)
byte pulseWidth = 0;
byte newpulseWidth = 130;
byte targetPulseWidth;
boolean PWMGoUp = true;
boolean PWMOnOff = true;

boolean LED_ON_OFF = true;

SDL_Arduino_INA3221 ina3221;

// the three channels of the INA3221
#define CHANNEL_SOLAR 2 // solar panel
#define CHANNEL_BATTERY 1 // lipo battery



int count = 0;

void setup()
{

  //Serial.begin(9600);
  Serial.begin(112500);
  Serial.println("no  Volt     mA   mW     Volt     mA   mW   eff    PWM   target");

  // voltage and current sensor
  ina3221.begin();

  // LED
  pinMode(13, OUTPUT);

  // enable MOSFET driver chip
  pinMode(PWM_ENABLE_PIN, OUTPUT);     // sets the digital pin as output
  digitalWrite(PWM_ENABLE_PIN, HIGH);

  // PWM
  pulseWidth = 128;
  InitTimersSafe();
  bool success = SetPinFrequencySafe(PWM_OUT, frequency);


  // LCD
  lcd.begin(20, 4);
  lcd.setCursor(0, 0);            // set the LCD cursor   position
  lcd.print("MPPT");  // print a simple message on the LCD
  lcd.setBacklight(WHITE);

}


void loop()
{
  float sv[3], bv[3], cmA[3], lv[3], pw[3];


  for (int i = 0; i < 3; i++) {
    bv[i] = ina3221.getBusVoltage_V(i + 1);
    sv[i] = ina3221.getShuntVoltage_mV(i + 1);
    cmA[i] = ina3221.getCurrent_mA(i + 1);
    lv[i] = bv[i] + (sv[i] / 1000);
    pw[i] = bv[i] * cmA[i];

  }


  // Is sun shining?
  if (bv[CHANNEL_SOLAR] < 9.5) {
    // No: go to sleep at night
    digitalWrite(13, LOW);    // turn the LED off
    lcd.setCursor(0, 3);
    lcd.print("SLEEP ON ");
    int sleepMS = Watchdog.sleep();
    // brief LED on when wakeup
    digitalWrite(13, HIGH);   // turn the LED on
    delay(10);
    digitalWrite(13, LOW);    // turn the LED off

  }
  else {
    // Yes: charge battery

    //Serial.println("alive");
    // blink as sign of life
    if (BLINK)
    {
      if (LED_ON_OFF == true)
        digitalWrite(13, HIGH);   // turn the LED on
      else
        digitalWrite(13, LOW);    // turn the LED off
      LED_ON_OFF = !LED_ON_OFF;
    }

    // Set PWM duty cycle
    if (POTENTIOMETER)
    {
      // read potentiometer value
      sensorValue = analogRead(potentiometerPin);
      newpulseWidth = sensorValue / 4;
      if ( newpulseWidth > 244)
        newpulseWidth = 244;
      pulseWidth = newpulseWidth;
    }
    else
    {

      // calculate target PWM
      if (bv[CHANNEL_BATTERY] <= TAPEROFFVOLTAGE)
        targetPulseWidth = MAXPWM;
      if (bv[CHANNEL_BATTERY] >= MAXVOLTAGE)
        targetPulseWidth = 0;
      if (bv[CHANNEL_BATTERY]  > TAPEROFFVOLTAGE && bv[CHANNEL_BATTERY]  < MAXVOLTAGE)
        targetPulseWidth = MAXPWM * (MAXVOLTAGE - bv[CHANNEL_BATTERY]) / (MAXVOLTAGE - TAPEROFFVOLTAGE);


      // Determine if PWM change is required

      if ((targetPulseWidth - pulseWidth) > 40)
        PWMGoUp = true;
      if ((pulseWidth - targetPulseWidth) > 40)
        PWMGoUp = false;

      if (pulseWidth < targetPulseWidth ) {
        if (PWMGoUp == true) {
          if (abs(pulseWidth - targetPulseWidth) > 10)
            pulseWidth += 5;
          else
            pulseWidth++;
          pwmWrite(PWM_OUT, pulseWidth);
        }
      }
      if (pulseWidth > targetPulseWidth ) {
        if (PWMGoUp == false) {
          if (abs(pulseWidth - targetPulseWidth) > 10)
            pulseWidth -= 5;
          else
            pulseWidth--;
          pwmWrite(PWM_OUT, pulseWidth);
        }
      }
    }
  }

  lcd.setCursor(0, 3);        
  lcd.print("SLEEP OFF");  
  printValues(bv, cmA, pw) ;


  count++;
  //delay(700);
  //delay(200);
  delay(500);
}



void printValues(  float bv[], float cmA[], float pw[]) {
  static char bvstr[10];
  static char cmAstr[10];
  static char pwstr[10];
  static char line[4][21] = {"                    ", "                    ", "                    ", "                    "};
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
    if (PWMOnOff == true)
      memcpy(&line[2][13], "ON ", 3);
    else
      memcpy(&line[2][13], "OFF", 3);


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






