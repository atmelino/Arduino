<?php
include("login.inc.php");

//connection to the database
$con = mysql_connect($hostname,$username,$password) 
or die('Could not connect: ' . mysql_error());

//select the database
mysql_select_db($database, $con)
or die('Could not select database: ' . mysql_error());


$still_running=true;
if($still_running){
	echo "database connection established";
	echo "<br>";


	// Create a MySQL table in the selected database
	$query="DROP TABLE arddata";
	mysql_query($query) or die(mysql_error()); 
	echo "data table dropped";
	echo "<br>";

	mysql_close();



}


?>

