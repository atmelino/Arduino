<?php


error_log("PHP script was called from Arduino on ", 3, "/var/tmp/my-errors.log");
error_log(strftime('%c'), 3, "/var/tmp/my-errors.log");
error_log("\n", 3, "/var/tmp/my-errors.log");

echo "dataRequest:". 116;
echo "hello";
echo "numberValue:". 54;


//if(ISSET($_GET['t']) && (is_numeric($_GET['t'])) && $_SERVER['REMOTE_ADDR']=='192,168,1,177'){
// message from the Arduino
//$temp = $_GET['t'];
//$qry = "INSERT INTO temp(timing, temp) VALUES(".time().",'$temp')";

//}




?>


