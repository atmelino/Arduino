


int count = 0;

void setup() {

  pinMode(13, OUTPUT);

  //Initialize serial and wait for port to open:
  Serial.begin(9600);
  while (!Serial) {
    ; // wait for serial port to connect. Needed for native USB port only
  }

  // prints title with ending line break
  Serial.println("sending characters every second");
}



void loop() {


  count++;
  Serial.print(count);
  Serial.println();



  digitalWrite(13, HIGH);   // turn the LED on (HIGH is the voltage level)
  delay(700);              // wait for a second
  digitalWrite(13, LOW);    // turn the LED off by making the voltage LOW
  delay(300);              // wait for a second


}
