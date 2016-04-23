<?php
include("login.inc.php");

//connection to the database
$con = mysql_connect($hostname,$username,$password)
or die('Could not connect: ' . mysql_error());

//select the database
mysql_select_db($database, $con)
or die('Could not select database: ' . mysql_error());

echo "Debug values:<br>";
$result = mysql_query("SELECT * FROM arddebug");
$num=mysql_numrows($result);

echo "name     value <br>";

while($row = mysql_fetch_array($result))
{

	echo $row['name'] . " " . $row['value'] ;
		echo "<br>";
}

mysql_close($con);
?>

