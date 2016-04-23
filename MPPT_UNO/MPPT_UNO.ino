#include <PWM.h>
#include <SDL_Arduino_INA3221.h>
#include <Wire.h>
#include <Adafruit_RGBLCDShield.h>
#include <utility/Adafruit_MCP23017.h>

Adafruit_RGBLCDShield lcd = Adafruit_RGBLCDShield();

// Options
#define BLINK 0
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
#define RED 0x1
#define YELLOW 0x3
#define GREEN 0x2
#define TEAL 0x6
#define BLUE 0x4
#define VIOLET 0x5
#define WHITE 0x7

int potentiometerPin = A0;    // select the input pin for the potentiometer
int ledPin = 13;      // select the pin for the LED
int sensorValue = 0;  // variable to store the value coming from the sensor

int32_t frequency = 80000; //frequency (in Hz)
byte pulseWidth = 0;
byte newpulseWidth = 130;
byte targetPulseWidth;
boolean PWMGoUp = true;

boolean LED_ON_OFF = true;

SDL_Arduino_INA3221 ina3221;

// the three channels of the INA3221
#define CHANNEL_1 1
#define CHANNEL_2 2 // lipo battery
#define CHANNEL_3 3 // solar panel

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
  float sv1 = 0;
  float bv1 = 0;
  float cmA1 = 0;
  float lv1 = 0;
  float pw1 = 0;
  float sv2 = 0;
  float bv2 = 0;
  float cmA2 = 0;
  float lv2 = 0;
  float pw2 = 0;
  float sv3 = 0;
  float bv3 = 0;
  float cmA3 = 0;
  float lv3 = 0;
  float pw3 = 0;
  float eff;
  static char bv1str[10];
  static char cmA1str[10];
  static char pw1str[10];
  static char bv2str[10];
  static char cmA2str[10];
  static char pw2str[10];
  static char bv3str[10];
  static char cmA3str[10];
  static char pw3str[10];
  static char pwmstr[10];
  static char tapwmstr[10];
  static char line1[21] = "                    ";
  static char line2[21] = "                    ";
  static char line3[21] = "                    ";
  static char line4[21] = "                    ";
  static char blank[21] = "                    ";

  //Serial.println("alive");

  // blink as sign of life
  if (BLINK)
  {
    if (LED_ON_OFF == true)
      digitalWrite(13, HIGH);   // turn the LED on (HIGH is the voltage level)
    else
      digitalWrite(13, LOW);    // turn the LED off by making the voltage LOW
    LED_ON_OFF = !LED_ON_OFF;
  }



  bv1 = ina3221.getBusVoltage_V(CHANNEL_1);
  sv1 = ina3221.getShuntVoltage_mV(CHANNEL_1);
  cmA1 = ina3221.getCurrent_mA(CHANNEL_1);
  lv1 = bv1 + (sv1 / 1000);
  pw1 = bv1 * cmA1;

  bv2 = ina3221.getBusVoltage_V(CHANNEL_2);
  sv2 = ina3221.getShuntVoltage_mV(CHANNEL_2);
  cmA2 = ina3221.getCurrent_mA(CHANNEL_2) * 1.0;
  lv2 = bv2 + (sv2 / 1000);
  pw2 = bv2 * cmA2;

  bv3 = ina3221.getBusVoltage_V(CHANNEL_3);
  sv3 = ina3221.getShuntVoltage_mV(CHANNEL_3);
  cmA3 = ina3221.getCurrent_mA(CHANNEL_3) * 1.0;
  lv3 = bv3 + (sv3 / 1000);
  pw3 = bv3 * cmA3;
  eff = pw2 / pw3;

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
    if (bv2 <= TAPEROFFVOLTAGE)
      targetPulseWidth = MAXPWM;
    if (bv2 >= MAXVOLTAGE)
      targetPulseWidth = 0;
    if (bv2  > TAPEROFFVOLTAGE && bv2  < MAXVOLTAGE)
      targetPulseWidth = MAXPWM * (MAXVOLTAGE - bv2) / (MAXVOLTAGE - TAPEROFFVOLTAGE);


    // Determine if PWM change is required

    if ((targetPulseWidth - pulseWidth) > 40)
      PWMGoUp = true;
    if ((pulseWidth - targetPulseWidth) > 40)
      PWMGoUp = false;

    if (pulseWidth < targetPulseWidth ) {
      if (PWMGoUp == true) {
        pulseWidth++;
        pwmWrite(PWM_OUT, pulseWidth);
      }
    }
    if (pulseWidth > targetPulseWidth ) {
      if (PWMGoUp == false) {
        pulseWidth--;
        pwmWrite(PWM_OUT, pulseWidth);
      }
    }

  }



  //if (pulseWidth > 200)
  //pulseWidth = 200;





  if (LCD || SERIAL)
  {
    dtostrf(bv1, 5, 2, bv1str);
    dtostrf(cmA1, 7, 2, cmA1str);
    dtostrf(pw1, 7, 2, pw1str);
    dtostrf(bv2, 5, 2, bv2str);
    dtostrf(cmA2, 7, 2, cmA2str);
    dtostrf(pw2, 7, 2, pw2str);
    dtostrf(bv3, 5, 2, bv3str);
    dtostrf(cmA3, 7, 2, cmA3str);
    dtostrf(pw3, 7, 2, pw3str);
    dtostrf(pulseWidth, 5, 2, pwmstr);
    dtostrf(targetPulseWidth, 5, 2, tapwmstr);

    memcpy(line1, bv3str, 5);
    line1[5] = ' ';
    memcpy(&line1[6], cmA3str, 6);
    line1[12] = ' ';
    memcpy(&line1[13], pw3str, 6);

    memcpy(line2, bv2str, 5);
    line2[5] = ' ';
    memcpy(&line2[6], cmA2str, 6);
    line2[12] = ' ';
    memcpy(&line2[13], pw2str, 6);

    memcpy(line3, bv1str, 5);
    line3[5] = ' ';
    memcpy(&line3[6], cmA1str, 6);
    line3[12] = ' ';
    memcpy(&line3[13], pw1str, 6);

    memcpy(line4, pwmstr, 5);
    line4[5] = ' ';
    memcpy(&line4[6], tapwmstr, 6);
  }


  if (LCD)
  {
    lcd.setCursor(0, 0);            // set the LCD cursor   position
    lcd.print(line1);  // solar panel

    lcd.setCursor(0, 1);            // set the LCD cursor   position
    lcd.print(line2);  // MPPT output

    lcd.setCursor(0, 2);            // set the LCD cursor   position
    lcd.print(line3);  // buck converter output and battery input

    lcd.setCursor(0, 3);            // set the LCD cursor   position
    lcd.print(line4);  //
  }

  if (SERIAL)
    printINA(count, line1, line2, eff, pulseWidth, targetPulseWidth);

  count++;
  //delay(700);
  delay(200);
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






