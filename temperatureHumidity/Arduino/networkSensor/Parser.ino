/* */

//#define DEBUG  1


char scriptvar[100];
int scriptvarindex;
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
      scriptvarindex=0;
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
        scriptvar[scriptvarindex++]=c;  

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
  for(int i=0;i<8;i++)
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
  /*
  if(strcmp(iwp,varName)==0)
   intervalPage=parsenumber;
   if(strcmp(st1,varName)==0)
   s1=parsenumber;
   if(strcmp(st2,varName)==0)
   s2=parsenumber;
   if(strcmp(st3,varName)==0)
   s3=parsenumber;
   if(strcmp(st4,varName)==0)
   s4=parsenumber;
   if(strcmp(fre,varName)==0)
   intervalPHP=parsenumber;
   if(strcmp(tra,varName)==0)
   traOnOff=(parsenumber==1?true:false);
   
   */

  // String processing  
  if(strcmp(scr,varName)==0)
  {
    scriptvar[scriptvarindex]='\0';  

    //Serial.print("scriptvar=");
    //Serial.println(scriptvar);

    int i=0; // index for parser variable
    int j=0; // index for result string 
    while(i<scriptvarindex){
      if(scriptvar[i]=='%'){
        serverscript[j]='/';
        i+=3;
        //scriptvarindex-=2;
        j++;  
      }
      else
      {
        serverscript[j]=scriptvar[i];
        i++;
        j++;
      }
    }
    serverscript[j]='\0';  
  }

  //printVariables();

  return true;
}












































