<?php


serverIP();
echo "<hr>";
route();
echo "<hr>";
routeGrep();
echo "<hr>";
curlCheck();
echo "<hr>";
deviceSearch();
echo "<hr>";



function serverIP()
{
	$ip = getenv("REMOTE_ADDR") ;
	Echo "This server's IP: " . $ip;
	echo "<br>";
}

function route()
{
	echo "ip route command:";
	echo "<br>";
	$last_line = system('ip route', $retval);
	echo "<br>";
}

function routeGrep()
{
	echo "ip route | grep eth0 command:";
	echo "<br>";
	$last_line = system('ip route | grep eth0', $retval);
	echo "<br>";
	echo "<br>";
	//echo $last_line;
}


function eth0IP()
{
	echo "Internet IP of Ethernet interface of this computer:";
	echo "<br>";
	$eth0IP = system('ip addr list eth0 |grep "inet " |cut -d\' \' -f6|cut -d/ -f1');
	echo "<br>";
	$pieces = explode(".", $eth0IP);
}


function curlCheck()
{
	if(cURLcheckBasicFunctions()==true)
		echo "curl ok<br>";
	else
		echo "curl not ok<br>";
}



function deviceSearch()
{
	echo "Scan of IP address range:";
	echo "<br>";
	scanIP();
}



//echo "<hr>";

//echo "Local Network:";
//echo "<br>";


function scanIP()
{
	//$range = '12.0.0.122-124';
	$range = '192.168.1.100-104';

	$range = explode('.', $range );
	foreach( $range as $index=>$octet )
		$range[$index] = array_map( 'intval', explode('-',$octet) );

	// 4 for loops to generate the ip address 4 octets
	for( $octet1=$range[0][0]; $octet1<=(($range[0][1])? $range[0][1]:$range[0][0]); $octet1++ )
		for( $octet2=$range[1][0]; $octet2<=(($range[1][1])? $range[1][1]:$range[1][0]); $octet2++ )
		for( $octet3=$range[2][0]; $octet3<=(($range[2][1])? $range[2][1]:$range[2][0]); $octet3++ )
		for( $octet4=$range[3][0]; $octet4<=(($range[3][1])? $range[3][1]:$range[3][0]); $octet4++ )
		{
			// assemble the IP address
			$ip = $octet1.".".$octet2.".".$octet3.".".$octet4;

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
				echo "<a href=\"http://".$ip."/\">http://".$ip."/</a><br>";

			}else if( strlen($buffer)>0 ) // if there is a response
				echo "Cannot get title\n<br>";
			else
				echo "[Not a site]\n<br>"; // if the isn't any response
		}

}


function pingTest()
{
	echo "ping command:";
	echo "<br>";
	$last_line = system('ping -c 1 12.0.0.123', $retval);
	echo "<br>";
	echo "<br>";

}


function cURLcheckBasicFunctions()
{
	if( !function_exists("curl_init") &&
		!function_exists("curl_setopt") &&
		!function_exists("curl_exec") &&
		!function_exists("curl_close") ) return false;
	else return true;
}

function a()
{
	// create curl resource
	$ch = curl_init();

	// set url
	curl_setopt($ch, CURLOPT_URL, "www.google.com");

	//return the transfer as a string
	curl_setopt($ch, CURLOPT_RETURNTRANSFER, 1);

	// $output contains the output string
	$output = curl_exec($ch);

	// close curl resource to free up system resources
	curl_close($ch);

}


?>



