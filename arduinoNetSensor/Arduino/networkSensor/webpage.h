#include <avr/pgmspace.h>

prog_char string_00[] PROGMEM =   "HTTP/1.1 200 OK";
prog_char string_01[] PROGMEM =   "Content-Type: text/html";
prog_char string_02[] PROGMEM =   "Connnection: close";
prog_char string_03[] PROGMEM =   "";
prog_char string_04[] PROGMEM =   "<!DOCTYPE html>";
prog_char string_05[] PROGMEM =   "<html>";
prog_char string_05a[] PROGMEM = "<meta http-equiv=\"refresh\" content=\"20\">";
prog_char string_06[] PROGMEM =   "<head>";
prog_char string_07[] PROGMEM =   "</head>";
prog_char string_08[] PROGMEM =   "<body onload=\"onload_function()\" style=\"color: rgb(0, 0, 0); background-color: rgb(51, 102, 102);\">";
prog_char string_09[] PROGMEM =   "<font color=white>";
prog_char string_10[] PROGMEM =   "<h3 align=center> My hiTECH Systems Arduino Ethernet sensors</h3><hr>";
prog_char string_s00[] PROGMEM =   "<h4>System</h4>"; //system
prog_char string_s01[] PROGMEM =  "<form name=inputscript method=get>";
prog_char string_s02[] PROGMEM =   "Arduino ID: ARD<input name=arduinoID id=aid value=0 size=20><br>";
prog_char string_s03[] PROGMEM =   "Time since boot: ";
prog_char string_s04[] PROGMEM =   "<input type=text style=\"background-color:LightGrey\" id=bti  value=0 size=8>seconds<br>";
prog_char string_s05[] PROGMEM =   "Program version: ";
prog_char string_s06[] PROGMEM =   "<input type=text style=\"background-color:LightGrey\" id=ver  value=0 size=8>";
prog_char string_s07[] PROGMEM =   "<br>Refresh every";
prog_char string_s08[] PROGMEM =  "<input name=intervalPage id=iwp value=20 size=6> seconds<br>";
prog_char string_s20[] PROGMEM =  "<input value=Submit type=submit></form>";
prog_char string_d00[] PROGMEM =   "<h4>Data</h4>"; //system
prog_char string_10a[] PROGMEM =   "Temperature";
prog_char string_10b[] PROGMEM =   "<input type=text style=\"background-color:LightGrey\" name=time id=tem  value=0 size=8>";
prog_char string_10c[] PROGMEM =   "Humidity";
prog_char string_10d[] PROGMEM =   "<input type=text style=\"background-color:LightGrey\" name=time id=hum  value=0 size=8>";
prog_char string_11[] PROGMEM =   "<h4>Database Server Configuration</h4>";
prog_char string_12[] PROGMEM =   "<form name=inputserverip method=get>";
prog_char string_13[] PROGMEM =   "Server IP: ";
prog_char string_14[] PROGMEM =   "<input type=text name=serverip1 id= ip1 value=10 size=2>";
prog_char string_15[] PROGMEM =   "<input type=text name=serverip2 id= ip2 value= 0 size=2>";
prog_char string_16[] PROGMEM =   "<input type=text name=serverip3 id= ip3 value= 0 size=2>";
prog_char string_17[] PROGMEM =   "<input type=text name=serverip4 id= ip4 value=100 size=2>";
prog_char string_18[] PROGMEM =   "<input type=submit value=Submit>";
prog_char string_19[] PROGMEM =   "</form>";
prog_char string_20[] PROGMEM =   "<form name=inputscript method=get>";
prog_char string_21[] PROGMEM =   "Server script path: ";
prog_char string_22[] PROGMEM =   "<input type=text name=serverscript id=scr value=/arduinoTempHumid/ArduinoCall.php size=40>";
prog_char string_23[] PROGMEM =   "<input type=submit value=Submit>";
prog_char string_24[] PROGMEM =   "</form>";
prog_char string_24a[] PROGMEM =  "<form name=inputscript method=get>";
prog_char string_24b[] PROGMEM =  "Data transmission frequency:";
prog_char string_24c[] PROGMEM =  "<input name=intervalPHP id=fre value=5 size=6> seconds <input value=Submit type=submit> </form>";
prog_char string_24d[] PROGMEM = "<form> Data transmission start<br>";
prog_char string_24e[] PROGMEM = "<input type=radio name=transmission id=traOn value=1>On<br>";
prog_char string_24f[] PROGMEM = "<input type=radio name=transmission id=traOff value=0>Off<br>";
prog_char string_24g[] PROGMEM = "<input type=submit value=Submit>";
prog_char string_24h[] PROGMEM = "</form><hr>";
prog_char string_25[] PROGMEM =   "<br>";
prog_char string_26[] PROGMEM =   "</font>";
prog_char string_27[] PROGMEM =   "";
prog_char string_28[] PROGMEM =   "</body>";
prog_char string_29[] PROGMEM =   "</html>";



PROGMEM const char *string_table[] = 
{   
  string_00, 
  string_01, 
  string_02, 
  string_03, 
  string_04, 
  string_05, 
  //string_05a, 
  string_06, 
  string_07, 
  string_08, 
  string_09, 
  string_10, 
  string_s00,
  string_s01,
  string_s02,
  string_s03,
  string_s04,
  string_s05,
  string_s06,
  string_s07,
  string_s08,
  string_s20,
  string_d00,
  string_10a, 
  string_10b, 
  string_10c, 
  string_10d, 
  string_11, 
  string_12, 
  string_13, 
  string_14, 
  string_15, 
  string_16, 
  string_17, 
  string_18, 
  string_19, 
  string_20, 
  string_21, 
  string_22, 
  string_23, 
  string_24,
  string_24a, 
  string_24b, 
  string_24c, 
  string_24d, 
  string_24e, 
  string_24f, 
  string_24g, 
  string_24h, 
  string_25, 
  string_26, 
  string_27, 
  string_28, 
  string_29 
};


prog_char script_00[] PROGMEM =   "<script type=\"text/javascript\">";
prog_char script_01[] PROGMEM =   "function onload_function() {";
prog_char script_02[] PROGMEM =   "";
prog_char script_03[] PROGMEM =   "return true;";
prog_char script_04[] PROGMEM =   "}";
prog_char script_05[] PROGMEM =   "</script>";

PROGMEM const char *script_table[] =
{   
  script_00, 
  script_01, 
  script_02, 
  script_03, 
  script_04, 
  script_05
};


#define MAX_CMD_LEN 52

prog_char  PROGMEM messages[17][MAX_CMD_LEN] = {
  "document.getElementById(\"traOn\").checked = true;",
  "document.getElementById(\"traOff\").checked = false;", 
  "document.getElementById(\"traOn\").checked = false;",
  "document.getElementById(\"traOff\").checked = true;",
  "document.getElementById(\"bti\").value='%i',",
  "document.getElementById(\"iwp\").value='%i',",
  "document.getElementById(\"tem\").value='%s',",
  "document.getElementById(\"hum\").value='%s',",
  "document.getElementById(\"ip1\").value='%i',",
  "document.getElementById(\"ip2\").value='%i',",
  "document.getElementById(\"ip3\").value='%i',",
  "document.getElementById(\"ip4\").value='%i',",
  "document.getElementById(\"fre\").value='%i',",
  "document.getElementById(\"scr\").value='%s';",
  "document.getElementById(\"aid\").value='%s';",
  "document.getElementById(\"ver\").value='%s';"

};

/*
prog_char* webpage[] PROGMEM =   {
 "HTTP/1.1 200 OK",
 "Content-Type: text/html"
 "Connnection: close",
 "",
 "<!DOCTYPE html>",
 "<html>",
 "page",
 "/<html>"
 };
 
 PROGMEM const char webpage_table[] =
 {   
 webpage[0],
 webpage[1],
 webpage[2],
 webpage[3],
 webpage[4],
 webpage[5],
 webpage[6],
 webpage[7]
 };
 */




