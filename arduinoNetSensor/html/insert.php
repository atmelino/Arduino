<?php
include("login.inc.php");


connect();

insertData();

mysql_close();

echo "Data Inserted!";


function connect()
{
	//connection to the database
	$con = mysql_connect($hostname,$username,$password)
	or die('Could not connect: ' . mysql_error());

	//select the database
	mysql_select_db($database, $con)
	or die('Could not select database: ' . mysql_error());

}

function insertData()
{

	// Make a MySQL Connection
	mysql_connect($hostname, $username, $password) or die(mysql_error());
	mysql_select_db($database) or die(mysql_error());

	// Insert a row of information into the table "example"
	mysql_query("INSERT INTO arddata
		(seconds, date, temperature,humidity) VALUES(12345,now(), 100*rand(),100*rand() ) ")
		or die(mysql_error());


}


?>

