<?php
include("login.inc.php");
include ("../lib/jpgraph/src/jpgraph.php");
include ("../lib/jpgraph/src/jpgraph_line.php");
require_once("../lib/jpgraph/src/jpgraph_date.php");

//error line below is VERY helpful tracking down blank graph errors.
error_reporting(E_ALL); ini_set('display_errors', '1');


echo "start<br>";

connect($hostname,$username,$password,$database);

$datay = array();
//$query=("SELECT * FROM arddata ORDER BY datetimeinserted DESC LIMIT 10080"); //5760 for a day@ 15 second insert rate.
$query=("SELECT * FROM arddata"); 
$result=mysql_query($query);

while($row = mysql_fetch_array($result))
{
	echo $row['date'] . " " . $row['temperature'] . " " . $row['humidity'];
	echo "<br />";
}


$rowcount = mysql_num_rows($result);

echo $rowcount;
echo "<br />";


$result=mysql_query($query);
if ($rowcount == 10080){
	// if the DB has enough data to make a complete graph fill array and go
	while($row = mysql_fetch_array($result)) {

		$datay[] = $row['temperature'];

	}
}else{
	echo "else";
	echo "<br />";	
	
	// if the DB does not have enough data to make a complete graph
	// add what's in DB so far to the array and fill the rest with 0 values
	while($row = mysql_fetch_array($result)){
		echo $row['temperature'];
		echo "<br />";
		$datay[] = $row['temperature'];
	}
}


echo "<br>";
var_dump($datay);











mysql_close();

echo "<br>end<br>";


function connect($hostname,$username,$password,$database)
{
	
	echo "connect<br>";
	echo $hostname;
	echo "<br>";
	echo $username;
	echo "<br>";
	
	//connection to the database
	$con = mysql_connect($hostname,$username,$password,$database)
	or die('Could not connect: ' . mysql_error());

	//select the database
	mysql_select_db($database, $con)
	or die('Could not select database: ' . mysql_error());

}

//else
//$table="11_0_0_177";
//if(ISSET($_GET['t']) && (is_numeric($_GET['t'])) && $_SERVER['REMOTE_ADDR']==$arduino){
//if(ISSET($_GET['t']) && (is_numeric($_GET['t']))){
//		<!--img.src = PHPcommand;-->
//$query="CREATE TABLE 11_0_0_177 (id INT NOT NULL AUTO_INCREMENT, PRIMARY KEY(id),seconds BIGINT, date DATETIME,temperature FLOAT, humidity FLOAT)";
//$query1="CREATE TABLE $table (id INT NOT NULL AUTO_INCREMENT, PRIMARY KEY(id),seconds BIGINT, date DATETIME,temperature FLOAT, humidity FLOAT)";
//$query="IF NOT EXISTS (SELECT * from sys.tables where name='11_0_0_77') CREATE TABLE '11_0_0_77' (id INT NOT NULL AUTO_INCREMENT, PRIMARY KEY(id),seconds BIGINT, date DATETIME,temperature FLOAT, humidity FLOAT)";



?>


