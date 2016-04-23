void printWebpage(EthernetClient client){

  int num=100;
  for(int i=0;i<num;i++){

    strcpy_P(buffer, (char*)pgm_read_word(&(string_table[i]))); // Necessary casts and dereferencing, just copy. 

    if(strncmp(buffer,"<html",4)==0)
    {
      sprintf(buffer,"<meta http-equiv=\"refresh\" content=\"%i\">",intervalPage);
      client.println(buffer);
    }

    if(strncmp(buffer,"<head",4)==0)
    {
      client.println(buffer);
      sprintf(buffer,"<title>ARD%s</title>",arduinoID);
    }

    if(strncmp(buffer,"<body",4)==0)
    {
      //Serial.println("body");
      client.println(buffer);
      updateWebPageFields(client,s1,s2,s3,s4); // changes buffer
    }
    //Serial.print(i);
    //Serial.print(" ");
    //Serial.println( buffer );
    client.println(buffer);

    if(strcmp(buffer,"</html>")==0)
    {
      strcpy_P(buffer2, EEPROMmessages[pageMessageNumber]);
      client.println(buffer2);
      break;
    }        

  }
}

boolean updateWebPageFields(EthernetClient client,byte s1, byte s2, byte s3, byte s4)
{
  int numj=6;
  for(int j=0;j<numj;j++){
    strcpy_P(buffer, (char*)pgm_read_word(&(script_table[j]))); 

    if(j!=3)
      client.println(buffer);
    else{
      setFieldInt(client,4,seconds);
      setFieldInt(client,5,intervalPage);
      setFieldString(client,6,tBuffer);
      setFieldString(client,7,hBuffer);
      setFieldInt(client,8,s1);
      setFieldInt(client,9,s2);
      setFieldInt(client,10,s3);
      setFieldInt(client,11,s4);
      setFieldInt(client,12,intervalPHP);
      setFieldString(client,13,serverscript);
      setFieldString(client,14,arduinoID);
      setFieldString(client,15,version);

      if(traOnOff==true){
        setField(client,0);
        setField(client,1);
      }
      else{
        setField(client,2);
        setField(client,3);
      }

    }  
  }
}

void setFieldInt(EthernetClient client, int number, int value)
{
  strcpy_P(buffer, messages[number]);
  sprintf(buffer2,buffer,value);
  client.println(buffer2);
}

void setFieldString(EthernetClient client, int number, char* value)
{
  strcpy_P(buffer, messages[number]);
  sprintf(buffer2,buffer,value);
  client.println(buffer2);
}

void setField(EthernetClient client, int number)
{
  strcpy_P(buffer, messages[number]);
  client.println(buffer);

}

//void printPageMessage(EthernetClient client, char* message)
//{
//  pageMessage=message;
//  printWebpage(client);
//}




