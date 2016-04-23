void EEPROMReadValues()
{
  int address=10;
  intervalPage=EEPROMReadInt(address);
  address+=2;
  s1 = EEPROM.read(address);
  address++;
  s2 = EEPROM.read(address);
  address++;
  s3 = EEPROM.read(address);
  address++;
  s4 = EEPROM.read(address);
  address++;
  intervalPHP=EEPROMReadInt(address);
  address+=2;
  traOnOff=EEPROM.read(address);
  address++;
  EEPROMReadString(address,serverscript);
  address+=MAX_STRING;
  EEPROMReadString(address,arduinoID);


}

int EEPROMSaveValues()
{
  int address=10;
  if(intervalPage!=EEPROMReadInt(address))
  {
    pageMessageNumber=0;
    EEPROMWriteInt(address,intervalPage);
  }  
  address+=2;  
  if(s1 != EEPROM.read(address))
  {
    pageMessageNumber=1;
    EEPROMwriteCheck(address, s1);
  }
  address++;
  if(s2 != EEPROM.read(address))
  {
    pageMessageNumber=2;
    EEPROMwriteCheck(address, s2);
  }
  address++;
  if(s3 != EEPROM.read(address))
  {
    pageMessageNumber=3;
    EEPROMwriteCheck(address, s3);
  }
  address++;
  if(s4 != EEPROM.read(address))
  {
    pageMessageNumber=4;
    EEPROMwriteCheck(address, s4);
  }
  address++;
  if(intervalPHP!=EEPROMReadInt(address))
  {
    pageMessageNumber=5;
    EEPROMWriteInt(address,intervalPHP);
  }  
  address+=2;  
  if(traOnOff != EEPROM.read(address))
  {
    pageMessageNumber=6;
    EEPROMwriteCheck(address, traOnOff);
  }
  address++;
  //printVariables();
  //Serial.println("save serverscript: ");
  int len=EEPROMWriteString(address,serverscript);
  //Serial.println(len);
  address+=MAX_STRING;  // includes one byte for the \0 character
  //Serial.println("save arduinoID");
  len=EEPROMWriteString(address,arduinoID);

  return 1;
}

int EEPROMReadInt(int address){
  int value = 0x0000;
  value = value | (EEPROM.read(address) << 8);
  value = value | EEPROM.read(address+1);
  return value;
}

void EEPROMWriteInt(int address, int value){
  EEPROMwriteCheck(address, (value >> 8) & 0xFF );
  EEPROMwriteCheck(address+1, value & 0xFF);
}

void EEPROMReadString(int address, char* dest){
  char c;
  int i=0;

  // bug to fix: if new string has same characters as old, but is shorter, does not change
  while('\0'!=(c=EEPROM.read(address+i))){
    dest[i]=c;
    i++;
    //Serial.print(c);
    // If EEPROM not initialized:
    if(i>=MAX_STRING)break;
  }
  //Serial.println();
}

// returns number of bytes written
int EEPROMWriteString(int address, char* source){

  char c;
  int i=0;
  boolean changed=false;
  int len=strlen(source);
  if(len>MAX_STRING) len=MAX_STRING;
  for(i=0;i<len;i++){
    c=EEPROM.read(address+i);
    //sprintf(buffer,"comparison address: %d EEPROM: %c %x var: %c %x",address+i,c,c,source[i],source[i]);
    //Serial.println(buffer);

    if(c!=source[i]){
      //pageMessage="serverscript saved to EEPROM";
      pageMessageNumber=7;
      //Serial.println("string changed, saving to EEPROM");
      changed=true;
      EEPROMwriteCheck(address+i, source[i]);
    }
  }
  //Serial.print("i ");
  //Serial.print(i);
  //Serial.print(" len ");
  //Serial.println(len);

  if(changed==true)
    EEPROMwriteCheck(address+len, '\0');
  return len;

}


int count;

void EEPROMwriteCheck(int address, byte b)
{

  if(count<100){
    Serial.print("writing to EEPROM: ");
    Serial.print(b);
    Serial.print(" ");
    EEPROM.write(address, b);
  }
  else
    Serial.print("Maximum allowed writes to EEPROM exceeded ");
  Serial.print("count: ");
  Serial.println(count++);

}

































