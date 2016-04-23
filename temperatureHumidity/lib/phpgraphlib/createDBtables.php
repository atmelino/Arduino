<?php

$link = mysql_connect('localhost', 'root', '1234')
   or die('Could not connect: ' . mysql_error());
     
mysql_select_db('salestracking') or die('Could not select database');
  


// Create a MySQL table in the selected database
$query="CREATE TABLE sales(id INT NOT NULL AUTO_INCREMENT, PRIMARY KEY(id),salesgroup VARCHAR(100), dollars INT )";
mysql_query($query) or die(mysql_error());
echo "data table created";
echo "<br>";


mysql_close();




?>
