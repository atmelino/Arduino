<?php

$url = 'http://10.0.0.177';


sendRequesttoArduino();


function sendRequesttoArduino()
{
	$arduino="http://10.0.0.177";

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

?>