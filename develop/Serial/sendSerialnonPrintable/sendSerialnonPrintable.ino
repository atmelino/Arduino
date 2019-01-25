

// the setup routine runs once when you press reset:
void setup() {
  // initialize serial communication at 9600 bits per second:
  Serial.begin(9600);
}

// the loop routine runs over and over again forever:
void loop() {

  int x = 14;
  

  Serial.println('hello');
  delay(500);
  
  
  Serial.write( (uint8_t *) &x, sizeof( x ) );
  //Serial.write(5, BYTE);
  delay(500);
}
