<?php
include("login.inc.php");

//connection to the database
$con = mysql_connect($hostname,$username,$password)
or die('Could not connect: ' . mysql_error());

//select the database
mysql_select_db($database, $con)
or die('Could not select database: ' . mysql_error());

echo "Options in database:<br>";
$result = mysql_query("SELECT * FROM ardoption");
$num=mysql_numrows($result);

echo "loopOnOff     Simulation <br>";

while($row = mysql_fetch_array($result))
{

	echo $row['loopOnOff'] . " " . $row['simulation']. " " . $row['debugStr'] ;
		echo "<br>";
}

mysql_close($con);

?>

