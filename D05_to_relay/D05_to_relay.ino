
/*
 
 */

unsigned int LED_pin_number =13;
//unsigned int relay_pin_number =5;
#define RELAY_PIN (5)



void setup() {                
  // initialize the digital pin as an output.
  // Pin 13 has an LED connected on most Arduino boards:
  pinMode(LED_pin_number, OUTPUT);     
  pinMode(RELAY_PIN, OUTPUT);     
}

void loop() {

  //  digitalWrite(LED_pin_number, HIGH);   // set the LED on
  //  delay(1500);              // wait for a second
  //  digitalWrite(LED_pin_number, LOW);    // set the LED off

  blink(200,100,3);
  delay(2000);              // wait for a second

    digitalWrite(RELAY_PIN, !digitalRead(RELAY_PIN));

  
}

void blink(int onperiod, int offperiod, int repeats)
{
  for (int i=0;i <repeats;i++)
  {
    digitalWrite(LED_pin_number, HIGH);   // set the LED on
    delay(onperiod);              // wait for a second
    digitalWrite(LED_pin_number, LOW);    // set the LED off
    delay(offperiod);              // wait for a second
  }
}



