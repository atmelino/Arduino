<?php
include("login.inc.php");

if(ISSET($_GET['t']) ){	// print database tables

	//connection to the database
	$con = mysql_connect($hostname,$username,$password)
	or die('Could not connect: ' . mysql_error());

	//select the database
	mysql_select_db($database, $con)
	or die('Could not select database: ' . mysql_error());

	//loop to show all the tables and fields
	$loop = mysql_query("SHOW tables FROM $database")
	or die ('cannot select tables');
	
	echo $loop;
}

//connection to the database
$con = mysql_connect($hostname,$username,$password)
or die('Could not connect: ' . mysql_error());

//select the database
mysql_select_db($database, $con)
or die('Could not select database: ' . mysql_error());

//loop to show all the tables and fields
$loop = mysql_query("SHOW tables FROM $database")
or die ('cannot select tables');

while($table = mysql_fetch_array($loop))
{
	echo "
	<table cellpadding=\"2\" cellspacing=\"2\" border=\"0\" width=\"75%\">
	<tr bgcolor=\"#666666\">
	<td colspan=\"5\" align=\"center\"><b><font color=\"#FFFFFF\">" . $table[0] . "</font></td>
	</tr>
	<tr>
	<td>Field</td>
	<td>Type</td>
	<td>Key</td>
	<td>Default</td>
	<td>Extra</td>
	</tr>";

	$i = 0; //row counter
	$row = mysql_query("SHOW columns FROM " . $table[0])
	or die ('cannot select table fields');

	while ($col = mysql_fetch_array($row))
	{
		echo "<tr";

		if ($i % 2 == 0)
			echo " bgcolor=\"#CCCCCC\"";

		echo ">
		<td>" . $col[0] . "</td>
		<td>" . $col[1] . "</td>
		<td>" . $col[2] . "</td>
		<td>" . $col[3] . "</td>
		<td>" . $col[4] . "</td>
		</tr>";

		$i++;
	} //end row loop

	echo "</table><br/><br/>";
} //end table loop

;

while ($row = mysql_fetch_row($result)) {
	echo "Table: {$row[0]}\n";
}

mysql_close($con);

?>
