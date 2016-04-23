<?php

// command line call:  php5 DBfunctions.php t=1

include("login.inc.php");

$hostname=$lhostname;
$username=$lusername;
$password=$lpassword;
$database=$ldatabase;

if(defined('STDIN') )
{
	echo("Running from CLI\n");
	parse_str(implode('&', array_slice($argv, 1)), $_GET);
}
else
{
	//echo("Not Running from CLI");
}



if(ISSET($_GET['t']) ){	// print database tables

	//echo "tables";

	//connection to the database
	$con = mysql_connect($hostname,$username,$password)
	or die('Could not connect: ' . mysql_error());

	//select the database
	mysql_select_db($database, $con)
	or die('Could not select database: ' . mysql_error());

	//loop to show all the tables and fields
	$result = mysql_query("SHOW tables FROM $database")
	or die ('cannot select tables');

	//echo $loop;
	$rowcount = mysql_num_rows($result);
	//echo $rowcount;

	$myarray=array();
	for ($i = 0; $i <$rowcount; $i++) {
		$table = mysql_fetch_array($result);
		//echo $i." ".$table[0];
		//echo "\n";
		//$myarray=array("id"=>$i, "object"=>$table[0]);
		//$myarray=array($i, $table[0]);
		//echo json_encode($i,$table[0]);
		$myarray[]=$table[0];
	}
	echo json_encode($myarray);
	
	while($table = mysql_fetch_array($result))
	{
		//echo $table[0];
	}
}

//|| true
?>
