/* */

//#define DEBUG  1


char stringVar[100];
int stringVarIndex;
int currentState;
//boolean debugPrint1=false;
//boolean debugPrint2=false;
char varName[15];
int varindex=0;


boolean parser(char c)
{

#ifdef DEBUG
  if(debugPrint1){
    Serial.print(" enter parser");
    Serial.print(" char ");
    Serial.print(c);
    Serial.print(" state ");
    Serial.println(currentState);
  }
  if(debugPrint2){
    Serial.print(" in prs");
    Serial.print(" s ");
    Serial.println(currentState);
  }
#endif

  switch(currentState) {
  case parse_new:
    if(c=='G')
      currentState=parse_G;
    if(c=='P')
      currentState=parse_P;
    break;  

  case parse_G:
    if(c=='E')
      currentState=parse_GE;
    else
      currentState=parse_new;
    break;

  case parse_GE:
    if(c=='T'){
      currentState=parse_GET;
      reqType=R_GET;
    }
    else
      currentState=parse_new;
    break;

  case parse_GET:
    if(c=='?'){
      // for now
      currentState=parse_QM;
    }
    else
      if(c==' ' || c=='/')
        break;
      else
        currentState=parse_new;
    break;

  case parse_QM:
    if(c=='='){
      currentState=parse_EQ;
      varName[varindex]='\0';
      varindex=0;
      parsenumber=0;
      stringVarIndex=0;
    }
    else{
      varName[varindex++]=c;
      varName[varindex]='\0';
    }
    break;

  case parse_EQ:
    //Serial.println("parse_EQ enter");
    if(c==' '){
      assignVariables(); // variable complete
      currentState=parse_new; // no more variables
      break;
    }
    else
    {
      if( c=='&'){
        currentState=parse_QM; // another variable
        assignVariables(); // variable complete
      }        // number
      if(c>='0' && c<='9'){
        parsenumber=parsenumber*10+(c-'0');  
        //Serial.println("parse_EQ parsenumber assignment");          
      }   
      if(c>' ')
        // String
        stringVar[stringVarIndex++]=c;  

    }
    break;

  case parse_P:
    if(c=='O')
      currentState=parse_PO;
    else
      currentState=parse_new;
    break;

  case parse_PO:
    if(c=='S')
      currentState=parse_POS;
    else
      currentState=parse_new;
    break;

  case parse_POS:
    if(c=='T'){
      currentState=parse_POST;
      reqType=R_POST;
    }
    else
      currentState=parse_new;

  case parse_POST:
    // later: parse numbers
    if(c==' ')
      currentState=parse_new;
    else
      currentState=parse_new;
    break;

  default:  
    break;
  }

#ifdef DEBUG
  if(debugPrint1){
    Serial.print("  exit  parser");
    Serial.print(" _st_");
    Serial.println(currentState);
  }
  if(debugPrint2){
    Serial.print("  ex prs");
    Serial.print("  s ");
    Serial.println(currentState);
  }
#endif

  return true;

}

boolean resetParser2()
{
  currentState=parse_new;
  reqType=R_NONE;
}


boolean assignVariables()
{
  for(int i=0;i<var_table_length;i++)
  {
    strcpy_P(buffer, (char*)pgm_read_word(&(var_table[i]))); // Necessary casts and dereferencing, just copy. 
    if(strcmp(buffer,varName)==0){
      //Serial.println();
      //Serial.println("found: ");
      //Serial.println(i);

      switch(i){
      case 0:
        intervalPage=parsenumber;
        break;
      case 1:
        s1=parsenumber;
        break;
      case 2:
        s2=parsenumber;
        break;
      case 3:
        s3=parsenumber;
        break;
      case 4:
        s4=parsenumber;
        break;
      case 5:
        intervalPHP=parsenumber;
        break;
      case 6:
        traOnOff=(parsenumber==1?true:false);
        break;
      }

    }
  }

  // String processing  
  if(strcmp(scr,varName)==0)
  {
    stringVar[stringVarIndex]='\0';  
    copyStringVar(serverscript);
  }

  // String processing  
  if(strcmp(aid,varName)==0)
  {
    //Serial.println("arduinoID found");
    stringVar[stringVarIndex]='\0';  
    copyStringVar(arduinoID);
  }

  //Serial.println("parser assign values");
  //printVariables();

  return true;
}

void copyStringVar(char* dest)
{
  int i=0; // index for parser variable
  int j=0; // index for result string 
  while(i<stringVarIndex){
    if(stringVar[i]=='%') // convert '%2F' to '/'
    {
      dest[j]='/';
      i+=3;
      j++;  
    }
    else
    {
      dest[j]=stringVar[i];
      i++;
      j++;
    }
  }
  dest[j]='\0';  

}













































