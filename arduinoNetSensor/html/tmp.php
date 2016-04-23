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

//echo $pieces[0].'.'.$pieces[1].'.'.$pieces[2];
//echo "<br>";

//for ($i=120; $i<=125; $i++)
//{
//	$testip=$pieces[0].'.'.$pieces[1].'.'.$pieces[2].'.'.$i;
//	echo "Ping " . $testip . "<br>";
//	$last_line = system('ping -c 1 '.$testip, $retval);
//}



/*
 * @Script: IP Scanner
* @Version: 0.1
* @Author: Emad Elsaid
* @Email: blazeeboy@gmail.com
* @Website: http://blazeeboy.blogspot.com
* @What is that ?:
* 	that is a ip acanner script
* 	you can give it a range of IP addresses and it'll
* 	get the website title of that page or notify that
* 	this is not a website at all
* 	i developed it becase when we made a 2011 revolution in Egypt
* 	i cannot access any nameserver but i can access one website
* 	then i made a nslookup command to get the ip of that website and then
* 	created that script to get the available website for me.
* 	i really don't know how to get the facebook.com ip address using that script
*
* @How to use ?
* 	you need to modify the $range variable
*	every octet could be written as 1 number like : 1, 3, 5
*	or you can specify a whole range to enumerate between : 1-255, 24-26
* 	then fire it from terminal not browser, to get a continual output.
*/
function scanIP()
{
	//$range = '12.0.0.122-124';
	$range = '10.0.0.10-12';

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

//echo "dns_get_record:";
//echo "<br>";
//$result = dns_get_record("localhost");
//print_r($result);
//$localIP = gethostbyname(trim('hostname'));
//echo $localIP;


//$last_line = system('netstat', $retval);
//echo "<br>";




function curl_test1()
{
	// create curl resource
	$ch = curl_init();

	// set url
	curl_setopt($ch, CURLOPT_URL, "example.com");

	//return the transfer as a string
	curl_setopt($ch, CURLOPT_RETURNTRANSFER, 1);

	// $output contains the output string
	$output = curl_exec($ch);

	// close curl resource to free up system resources
	curl_close($ch);
}


$phpArray = array(
		0 => 001-1234567,
		1 => 1234567,
		2 => 12345678,
		3 => 12345678,
		4 => 12345678,
		5 => 'AP1W3242',
		6 => 'AP7X1234',
		7 => 'AS1234',
		8 => 'MH9Z2324',
		9 => 'MX1234',
		10 => 'TN1A3242',
		11 => 'ZZ1234'
);
//echo json_encode($phpArray );
?>


