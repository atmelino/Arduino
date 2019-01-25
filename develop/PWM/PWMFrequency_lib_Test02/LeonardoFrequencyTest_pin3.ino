#include <PWMFrequency.h>

//
// This in an example sketch for the PWM Frequency Library
//
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


  testFrequency(11, 1);
  delay (1000); // 

  while (true)
  {
    //The following can only be tested on an oscilliscope
    //testFrequency(11, testPrescaleTimerValues1, sizeof(testPrescaleTimerValues1) );
    //testFrequency(13, testPrescaleTimerValues2, sizeof(testPrescaleTimerValues2) );
  }
}




void testFrequency(byte pinNumber, uint16_t prescalValue) {

  Serial.println();
  Serial.print("Testing PIN ");
  Serial.println(pinNumber);

  // setup the PIN
  pinMode(pinNumber, OUTPUT);
  Serial.print("Prescale Value = ");
  // set the prescale, and PWM output
  setPWMPrescaler(pinNumber, prescalValue);

  // settle
  delay (10);

  // set the PIN
  analogWrite(pinNumber, 128);

  delay (1000); // RUN THE TEST
  Serial.print(prescalValue);
  Serial.print(" ");
  Serial.println();

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
    analogWrite(pinNumber, 128);

    delay (1000); // RUN THE TEST
    Serial.print(prescalValues[i]);
    Serial.print(" ");

  }
  Serial.println();

}
