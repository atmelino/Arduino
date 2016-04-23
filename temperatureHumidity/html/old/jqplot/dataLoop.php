<?php


$loopCount=1000;
$loopSleep=5;


ob_start();
for ( $i = 0; $i < $loopCount; $i++) {

	getloopOnOff();
	sleep($loopSleep);


	if(getloopOnOff()==1)
	{
		sendRequesttoArduino();
		//insertData();
	}

	echo time();
	echo "\n";
	ob_flush();
	flush();
}


echo "Data Inserted!";


function getloopOnOff()
{

	// Make a MySQL Connection
	mysql_connect("localhost", "root", "1234") or die(mysql_error());
	mysql_select_db("ardtemphumid") or die(mysql_error());

	//
	$result = mysql_query("SELECT * FROM ardoption");
	$row = mysql_fetch_array($result);
	//while($row = mysql_fetch_array($result))
	//{
	//		echo $row['loopOnOff'] . " " . $row['simulation'] ;
	//echo "\n";
	//}

	mysql_close();
	
	$total=$row['loopOnOff'];
	echo $total;
	echo "\n";

	return $total;
}



function sendRequesttoArduino()
{
	$arduino="http://11.0.0.177";

	$data='Request: temperature PHP';
	//$data='Request: temperature console';


	//open connection
	$ch = curl_init();

	//set the url, number of POST vars, POST data
	curl_setopt($ch,CURLOPT_URL, $arduino);
	curl_setopt($ch,CURLOPT_POST, 1);
	curl_setopt($ch,CURLOPT_POSTFIELDS, $data);

	//execute post
	$result = curl_exec($ch);

	//close connection
	curl_close($ch);
}



function insertData()
{

	// Make a MySQL Connection
	mysql_connect("localhost", "root", "1234") or die(mysql_error());
	mysql_select_db("ardtemphumid") or die(mysql_error());

	// Insert a row of information into the table "example"
	mysql_query("INSERT INTO arddata
			(date, temperature,humidity) VALUES(now(), 100*rand(),100*rand() ) ")
			or die(mysql_error());

	mysql_close();
	
	
}

?>



