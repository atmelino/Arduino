#include <PWMFrequency.h>

//
// This in an example sketch for the PWM Frequency Library
//
// It is special purpose, as it allows you to test the frequencies
// produced by the Arduino, automatically by connecting a test PWM PIN
// to PIN 3. PIN 3 then reads then counts and displays the frequency
// to you.
//
// Note: PWM pins 3 and 11, cannot be tested in this way because the code
// relies on millis() to function.
//

void setup() {

  Serial.begin(9600);

  //leonardo serial startup
  while (!Serial);

  Serial.println("PWM Prescaler Testing");
  Serial.println("=====================");
  Serial.println("");


}

// TEST Prescale Values for Normal and advanced Timer4
uint16_t testPrescaleTimerValues1[] = {1, 8, 64, 256, 1024};
uint16_t testPrescaleTimerValues2[] = {1, 2, 4, 8, 16, 32, 64, 128, 256, 512, 1024, 2048, 4096, 8192, 16384};

void loop() {

//  testFrequency(9, testPrescaleTimerValues1, sizeof(testPrescaleTimerValues1) );
//  testFrequency(10, testPrescaleTimerValues1, sizeof(testPrescaleTimerValues1) );
//  testFrequency(13, testPrescaleTimerValues2, sizeof(testPrescaleTimerValues2) );

  // The following can only be tested on an oscilliscope
  testFrequency(3,testPrescaleTimerValues1, sizeof(testPrescaleTimerValues1) );
  //testFrequency(11,testPrescaleTimerValues1, sizeof(testPrescaleTimerValues1) );
}

void testFrequency(byte pinNumber, uint16_t *prescalValues, int size) {

  Serial.println();
  Serial.print("Testing PIN ");
  Serial.println(pinNumber);

  // setup the PIN
  pinMode(pinNumber, OUTPUT);

  byte elements = size / sizeof(uint16_t);

  Serial.print("Prescale Value = ");
  for ( int i = 0; i < elements; i++ ) {

    // set the prescale, and PWM output
    setPWMPrescaler(pinNumber, prescalValues[i]);

    // settle
    delay (10);

    // set the PIN
    pinMode(pinNumber, OUTPUT);
    analogWrite(pinNumber, 128);

    // settle
    delay (10);

    delay (1000); // RUN THE TEST

    Serial.print(prescalValues[i]);
    Serial.print(" ");

    // wait for serial output
    delay (10);
  }
  Serial.println("");
}
