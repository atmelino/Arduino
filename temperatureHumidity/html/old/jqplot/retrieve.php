<?php
include("login.inc.php");

//connection to the database
$con = mysql_connect($hostname,$username,$password) 
or die('Could not connect: ' . mysql_error());

//select the database
mysql_select_db($database, $con)
or die('Could not select database: ' . mysql_error());

$result = mysql_query("SELECT * FROM arddata");
//echo '{"min":';


$rows = mysql_num_rows($result);
 
echo '{"data":[[';
while($row = mysql_fetch_array($result))
{
//  echo $row['temperature'] . " " . $row['humidity'];

  $index+=1;
  echo '["';
  $datetime = strtotime($row['date']);
  $mysqldate = date("m-d-Y h:i:sA", $datetime);
  echo $mysqldate;
  //echo $row['date'];
  echo '",';
  echo $row['humidity'];
  echo ']';

  if($index<$rows)
  { 
    echo ',';
  }
  //echo $index;

}

echo ']]}';


mysql_close($con);



//$rows = array();
//while($r = mysql_fetch_assoc($result)) {
//    $rows[] = $r;
//}
//print json_encode($rows);
//exit();



?>
