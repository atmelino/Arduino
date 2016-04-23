<?php
include("login.inc.php");
$debugHTML=true;
$debugCLI=false;
$debugCLI=true;

// Database table name is the IP of the Arduino sensor
$arduinoIP=$_SERVER['REMOTE_ADDR'];
if($arduinoIP!=null)
	$table=str_replace(".", "_", $arduinoIP);


connect($hostname,$username,$password,$database);

$query="CREATE TABLE $table (id INT NOT NULL AUTO_INCREMENT, PRIMARY KEY(id),seconds BIGINT, date DATETIME,temperature FLOAT, humidity FLOAT)";
$success=mysql_query($query) or reportErrorData();
if($success==true)
{
	echo "data table $table created";
	echo "<br>";
}

// if called from command line, for debugging
if($debugCLI)
{
	echo "\nIP address of client:";
	echo $_SERVER['REMOTE_ADDR'];
	//$arduinoIP="11.0.0.177";
	echo $arduinoIP . "\n";
	//$table=str_replace(".", "_", $arduinoIP);
	echo $table . "\n";
}


if(ISSET($_GET['t']) &&ISSET($_GET['h']) ){	// message from the Arduino
	$temp = $_GET['t'];
	$temper=floatval($temp);
	$hum = $_GET['h'];
	$humid=floatval($hum);

	// Make a MySQL Connection
	mysql_connect($hostname, $username, $password) or die(mysql_error());
	mysql_select_db($database) or die(mysql_error());

	// Insert a row of information into the table
	$unixtime=time();
	mysql_query("INSERT INTO $table
		(seconds, date, temperature,humidity) VALUES($unixtime, now(), $temper,$humid ) ")
		or die(mysql_error());

	// debug information
	if($debugHTML)
	{
		mysql_query("UPDATE ardoption
			//SET debugStr='hello'
			SET debugStr='$table'
			WHERE id = 1")
			or die(mysql_error());
	}

	mysql_close();
}


function connect($hostname,$username,$password,$database)
{
	//connection to the database
	echo "connecting to database<br>\n";
	$con = mysql_connect($hostname,$username,$password)
	or die('Could not connect: ' . mysql_error());
	echo "database connection on $hostname established<br>\n";

	//select the database
	mysql_select_db($database, $con)
	or die('Could not select database: ' . mysql_error());
	echo "database $database selected<br>\n";
}

function reportErrorData()
{
	echo mysql_error();
	echo "<br>";
	echo "\n";
}
?>
