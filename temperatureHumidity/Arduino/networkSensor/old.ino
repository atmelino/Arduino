/*
boolean resetParser()
 {
 currentState=newparse;
 reqType=R_NONE;
 }
 
 
 int parser(char c)
 {
 
 if(currentState>newparse){
 //Serial.print("_");
 //Serial.println(currentState);
 //Serial.print("___state: ");
 //Serial.println(currentState);
 }
 
 if(c=='/' || c==' ')
 return currentState;
 
 switch(currentState) {
 
 case newparse:
 switch(c) {
 case 'G': 
 currentState=G;
 break;
 case 'P': 
 currentState=P;
 break;
 default:
 break;
 }  
 break;
 
 case G:
 if(c=='E')
 currentState=GE;
 else
 currentState=newparse;
 break;  
 
 case GE:
 if(c=='T'){
 currentState=GET;
 reqType=R_GET;
 }
 break;
 
 case GET:
 if(c=='?')
 currentState=QM;
 else
 currentState=newparse;
 break;
 
 case QM:
 if(c=='='){
 currentState=EQ;
 varName[varindex]='\0';
 varindex=0;
 parsenumber=0;
 }
 else{
 varName[varindex++]=c;
 varName[varindex]='\0';
 }
 break;
 
 case EQ:
 // number
 if(c>='0' && c<='9'){
 parsenumber=parsenumber*10+(c-'0');  
 }
 else
 {
 // number complete
 assignVariables();
 if( c=='&'){    
 // another variable
 currentState=QM;
 }      
 else
 // no more variables
 currentState=newparse;
 }
 break;
 
 
 case P:
 if(c=='O')
 currentState=PO;
 else
 currentState=newparse;
 break;  
 
 case PO:
 if(c=='S')
 currentState=POS;
 else
 currentState=newparse;
 break;  
 
 case POS:
 if(c=='T'){
 currentState=POST;
 reqType=R_POST;
 }
 else
 currentState=newparse;
 break;  
 
 default:
 currentState=newparse;
 break;
 
 }  
 return currentState;
 
 }
 */



/*
boolean printWebpage(EthernetClient client)
 {
 int num=100;
 for(int i=0;i<num;i++){
 if(webpage[i][0]=='<' && webpage[i][1]=='/'&& webpage[i][2]=='b'&& webpage[i][3]=='o')
 {
 setIPFields(client,s1,s2,s3,s4);
 }
 
 if(webpage[i][0]=='<' && webpage[i][1]=='/'&& webpage[i][2]=='h'&& webpage[i][3]=='t')
 {
 break;
 }        
 client.println(webpage[i]);
 }    
 }
*/





//delay(1000);
//Serial.print("varnumber1= ");
//Serial.println(varnumber1);
//Serial.print("varnumber2= ");
//Serial.println(varnumber2);


//  char* webpage[] = {
//};      


    //if(buffer[0]=='<' && buffer[1]=='/'&& buffer[2]=='h'&& buffer[3]=='t')

    // if(webpage[i][0]=='<' && webpage[i][1]=='/'&& webpage[i][2]=='b'&& webpage[i][3]=='o')




/*
    switch(c) {
    case 'G': 
      currentState=parse_G;
      break;
    case 'P': 
      currentState=parse_P;
      //Serial.println("state new P");
      Serial.print(" p1_s_");
      Serial.println(currentState);
      break;
    default:
      break;
    }
*/


/*
  if(debugPrint2){
    Serial.print(c);

    if(currentState>parse_new){
      Serial.print(" s_");
      Serial.print(currentState);
      Serial.print("_r_");
      Serial.println(reqType);
    }
  }

*/


  //Serial.print("buffer= ");
  //Serial.println(buffer);
  //Serial.print("serverscript= ");
  //Serial.println(serverscript);


  //Serial.print("aV pn= ");
  //Serial.print(parsenumber);
  //Serial.print("buffer= ");
  //Serial.println(buffer);

    //strcpy(serverscript,scriptvar);



