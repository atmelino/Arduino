<?php
include("login.inc.php");
$table="11_0_0_177";

//connection to the database
$con = mysql_connect($hostname,$username,$password)
or die('Could not connect: ' . mysql_error());

//select the database
mysql_select_db($database, $con)
or die('Could not select database: ' . mysql_error());



//loop to show all the tables
$query1 = mysql_query("SHOW tables FROM $database")
or die ('cannot select tables');
while($table = mysql_fetch_array($query1))
{
	echo "Table: ";
	echo $table[0];
	echo "<br />";


	echo "Data in database:<br>";
	$result = mysql_query("SELECT * FROM $table[0]");
	$num=mysql_numrows($result);

	while($row = mysql_fetch_array($result))
	{
		echo $row['seconds'] . " " .$row['timestamp'] . " " . $row['date'] . " " . $row['temperature'] . " " . $row['humidity'];
		echo "<br />";
	}

}
//$i=0;
//while ($i < $num) {
//$field1=mysql_result($result,$i,"temperature");
//$field2=mysql_result($result,$i,"humidity");
//echo $i,"  ";
//echo $field1, " ";
//echo $field2;
//echo "<br>";
//$i++;
//}

mysql_close($con);

?>

