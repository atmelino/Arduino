<?php

//echo "scanIP called\n";
// if called from command line, put args into GET variable
// example: 
if(defined('STDIN') )
{
	echo("Running from CLI\n");
	parse_str(implode('&', array_slice($argv, 1)), $_GET);
}
else
{
	//echo("Not Running from CLI");
}


if(ISSET($_GET['e']) ){
	echo "e ";
	eth0IP();
}

if(!(_isCurl()))
  echo "CURL not found";
//else
  //echo "CURL found";


if(ISSET($_GET['w']) ){
	//echo "w ";
	wlan0IP();
}

if(ISSET($_GET['i']) ){
	$ip = $_GET['i'];
	testIP($ip);
	//echo $ip;
	//testIP(14,2,1,$i);
}

function eth0IP()
{
	//echo "Internet IP of Ethernet interface of this computer:";
	$eth0IP = system('ip addr list eth0 |grep "inet " |cut -d\' \' -f6|cut -d/ -f1');
	echo $eth0IP;
	//$pieces = explode(".", $eth0IP);
}

function wlan0IP()
{
	//echo "Internet IP of Ethernet interface of this computer:";
	$wlan0IP = system('ip addr list wlan0 |grep "inet " |cut -d\' \' -f6|cut -d/ -f1');
	//echo $wlan0IP;
}


//function testIP($octet1,$octet2,$octet3,$octet4)
function testIP($ip)
{
	//echo "testIP called";
	// assemble the IP address
	//$ip = $octet1.".".$octet2.".".$octet3.".".$octet4;
	//echo $ip;

	//$ip = "10.0.0.11";
	
	// initialise the URL
	$x = curl_init( $ip );

	// output buffer start becase it damn output the page HTML
	ob_start();
	// get page HTML
	curl_exec( $x );
	// get HTML from output buffer
	$buffer = ob_get_contents();
	// clean buffer
	ob_end_clean();

	// get the title position
	$title_start = strpos( $buffer, '<title>')+strlen('<title>');
	$title_end = strpos( $buffer, '</title>');

	// print the result for that IP address
	echo $ip." : ";
	if( $title_end!==false ){ // if title tag exists
		$shortTitle=trim(substr( $buffer, $title_start, $title_end-$title_start ));
		echo trim(substr( $buffer, $title_start, $title_end-$title_start ))."\n"; // print title
		//echo "<a href=\"http://".$ip."/\">http://".$ip."/</a>\n";

	}else if( strlen($buffer)>0 ) // if there is a response
		echo "Cannot get title\n";
	//echo "Cannot get title\n<br>";
	else
		echo "[Not a site]\n"; // if the isn't any response
	//echo "[Not a site]\n<br>"; // if the isn't any response


}

function _isCurl(){
    return function_exists('curl_version');
}


//echo "IP test";
//echo date("H:i:s");

?>
