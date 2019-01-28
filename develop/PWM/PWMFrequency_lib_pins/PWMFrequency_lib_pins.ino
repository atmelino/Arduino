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

  testFrequency(5, 1);
  testFrequency(6, 1);
  testFrequency(9, 1);
  testFrequency(10, 1);
  testFrequency(11, 1);
  testFrequency(13, 1);
  while (true)
  {
    delay (1000); //
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
