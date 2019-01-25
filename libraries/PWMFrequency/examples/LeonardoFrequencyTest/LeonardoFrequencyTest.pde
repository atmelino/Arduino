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

// holds the frequency count.
volatile long pulseCount;

// interrupt handler
void interruptHandler() {
  pulseCount ++;
}

void setup() {

  Serial.begin(9600);
  
  //leonardo serial startup
  while (!Serial);

  Serial.println("PWM Prescaler Testing");
  Serial.println("=====================");
  Serial.println("");
  Serial.println("When Requested Please ensure Pin 3 is connected");
  Serial.println("to the specified PIN to be tested.");

  // interrupt 0 - Which is actually PIN 3 on Leonardo
  attachInterrupt(0,interruptHandler,RISING);

}

// TEST Prescale Values for Normal and advanced Timer4
uint16_t testPrescaleTimerValues1[] = {1, 8, 64, 256, 1024};
uint16_t testPrescaleTimerValues2[] = {1,2,4,8,16,32,64,128,256,512,1024,2048,4096,8192,16384};

void loop() {

  // automated testting
  testFrequency(5,testPrescaleTimerValues1, sizeof(testPrescaleTimerValues1) );
  testFrequency(6,testPrescaleTimerValues2, sizeof(testPrescaleTimerValues2) );
  testFrequency(9,testPrescaleTimerValues1, sizeof(testPrescaleTimerValues1) );
  testFrequency(10,testPrescaleTimerValues1, sizeof(testPrescaleTimerValues1) );
  testFrequency(13,testPrescaleTimerValues2, sizeof(testPrescaleTimerValues2) );

  // The following can only be tested on an oscilliscope  
  //testFrequency(3,testPrescaleTimerValues1, sizeof(testPrescaleTimerValues1) );
  //testFrequency(11,testPrescaleTimerValues1, sizeof(testPrescaleTimerValues1) );
}

void testFrequency(byte pinNumber, uint16_t *prescalValues, int size) {

  Serial.println();
  Serial.print("Testing PIN ");
  Serial.println(pinNumber);
  Serial.println("Press <SEND> to continue");
  
  // setup the PIN
  pinMode(pinNumber,OUTPUT);
  
  waitforUsertoPressSend();
  
  byte elements = size / sizeof(uint16_t);

  for ( int i = 0; i<elements; i++ ) {

    // set the prescale, and PWM output
    setPWMPrescaler(pinNumber,prescalValues[i]);

    // settle
    delay (10);

    // set the PIN 
    pinMode(pinNumber,OUTPUT);
    analogWrite(pinNumber,128);
    
    // settle
    delay (10);
    
    // clear the count  
    pulseCount = 0;

    delay (1000); // RUN THE TEST
  
    // read the count
    unsigned long testCount = pulseCount; 

    Serial.print("Prescale Value = ");
    Serial.print(prescalValues[i]);    
    Serial.print("; Frequency = ");
    Serial.print(testCount);
    Serial.println("");   

    // wait for serial output
    delay (10);
    
    // If testing on Osciliscope. Uncomment This
    // It gives you time to take a reading manually.
    // waitforUsertoPressSend();

    // return the PIN to Normal
    pinMode(pinNumber,INPUT);
    
    delay(10);
  }
}

void waitforUsertoPressSend() {
  // waits for input
  while ( ! Serial.available() );
  while ( Serial.available() ) Serial.read();
  delay (10);
}





