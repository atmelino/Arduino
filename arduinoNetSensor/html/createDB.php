<?
include("login.inc.php");

//$table="arddata";
$table1="11_0_0_177";
$table2="11_0_0_178";


echo "connecting to database<br>";
mysql_connect($hostname,$username,$password);
echo "database connection on $hostname established<br>";
mysql_select_db($database) or die(mysql_error());
echo "database $database selected<br>";


createTable($table1);
createTable($table2);
//createTable($table3);
//createTable($table4);


$query2="CREATE TABLE arddebug(id INT NOT NULL AUTO_INCREMENT, PRIMARY KEY(id),name VARCHAR(30), value VARCHAR(30))";
$success=mysql_query($query2) or reportErrorData();
if($success==true)
{
	echo "data table arddebug created";
	echo "<br>";
}
mysql_query("INSERT INTO arddebug VALUES (1,'IPString','n') ") or reportErrorData();




mysql_close();


function createTable($table)
{
	// Create a MySQL table in the selected database
	$query1="CREATE TABLE $table (id INT NOT NULL AUTO_INCREMENT, PRIMARY KEY(id),seconds BIGINT, date DATETIME,temperature FLOAT, humidity FLOAT)";
	$success=mysql_query($query1) or reportErrorData();
	if($success==true)
	{
		echo "data table $table created";
		echo "<br>";
	}
}



function reportErrorData()
{
	echo mysql_error();
	echo "<br>";
}


?>

