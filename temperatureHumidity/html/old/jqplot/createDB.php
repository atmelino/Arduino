<?
$hostname="localhost";
$user="root";
$password="1234";
$database="arduino";

mysql_connect($hostname,$user,$password);
mysql_select_db($database) or die(mysql_error());


echo "database connection established";
echo "<br>";


// Create a MySQL table in the selected database
$query="CREATE TABLE temp(id INT NOT NULL AUTO_INCREMENT, PRIMARY KEY(id), timing varchar(30) NOT NULL,
  temp varchar(10) NOT NULL,date DATETIME,temperature FLOAT, humidity FLOAT)";
mysql_query($query) or die(mysql_error());
echo "data table created";
echo "<br>";

mysql_close();



?>

