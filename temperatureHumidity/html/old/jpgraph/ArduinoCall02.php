<?php
// connect to MySQL

$hostname="localhost";
$username="root";
$password="1234";
$database="arduino";

$arduino="11.0.0.177";



if(ISSET($_GET['t']) && (is_numeric($_GET['t'])) && $_SERVER['REMOTE_ADDR']==$arduino){
	// message from the Arduino
	$temp = $_GET['t'];
	$temper=intval($temp);

	mysql_connect($hostname,$username,$password) or die("Can't connect that way!");
	@mysql_select_db('arduino') or die("Unable to select a database called 'Arduino'");
	//$qry = "INSERT INTO temp(timing, temp) VALUES(".time().",'$temp')";
	$qry = "INSERT INTO temp(timing, temp, temperature) VALUES(".time().",'$temp','$temper')";
	mysql_query($qry);
	mysql_close();


	//insertData();
	
	
	// Make a MySQL Connection
	mysql_connect("localhost", "root", "1234") or die(mysql_error());
	mysql_select_db("ardtemphumid") or die(mysql_error());
	
	// Insert a row of information into the table
	mysql_query("INSERT INTO arddata
			(date, temperature,humidity) VALUES(now(), $temper,$temper ) ")
			or die(mysql_error());
	
	mysql_close();
	
}


function insertData()
{

	// Make a MySQL Connection
	mysql_connect("localhost", "root", "1234") or die(mysql_error());
	mysql_select_db("ardtemphumid") or die(mysql_error());

	// Insert a row of information into the table
	mysql_query("INSERT INTO arddata
		(date, temperature,humidity) VALUES(now(), 100*rand(),100*rand() ) ")
		or die(mysql_error());

	mysql_close();

}

?>
