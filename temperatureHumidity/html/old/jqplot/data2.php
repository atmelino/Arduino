<?php
$con = mysql_connect("localhost","peter","abc123");
if (!$con)
  {
  die('Could not connect: ' . mysql_error());
  }

mysql_select_db("my_db", $con);

$result = mysql_query("SELECT * FROM Persons");

while($row = mysql_fetch_array($result))
  {
  echo $row['FirstName'] . " " . $row['LastName'];
  echo "<br />";
  }

mysql_close($con);
?>












<?php

//connection variables
$host = "localhost";
$database = "ardtemphumid";
$user = "root";
$pass = "1234";


echo "retrieve data";

//connection to the database
mysql_connect($host, $user, $pass)
or die ('cannot connect to the database: ' . mysql_error());

//select the database
mysql_select_db($database)
or die ('cannot select database: ' . mysql_error());

//loop to show all the tables and fields
$loop = mysql_query("SELECT * FROM example")
or die ('cannot select tables');



$query="SELECT * FROM example";





?>
