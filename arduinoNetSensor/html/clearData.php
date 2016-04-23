<?
include("login.inc.php");

$con = mysql_connect($hostname,$username,$password) or  die('Could not connect: ' . mysql_error());

mysql_select_db($database, $con) or die('Could not select database: ' . mysql_error());


$still_running=true;
if($still_running){
	echo "database connection established";
	echo "<br>";


	// Create a MySQL table in the selected database
	$query="DELETE FROM arddata";
	mysql_query($query) or die(mysql_error()); 
	echo "data rows dropped";
	echo "<br>";




	mysql_close($con);



}



//mysql_query("CREATE TABLE example(id INT NOT NULL AUTO_INCREMENT, PRIMARY KEY(id),date DATETIME,temperature FLOAT, humidity FLOAT)")
// or die(mysql_error()); 


?>

