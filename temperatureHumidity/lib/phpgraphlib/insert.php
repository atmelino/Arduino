<?php

connect();

insertData();

mysql_close();

echo "Data Inserted!";


function connect()
{
	//connection to the database
	$con = mysql_connect('localhost','root','1234')
	or die('Could not connect: ' . mysql_error());

	//select the database
	mysql_select_db('salestracking', $con)
	or die('Could not select database: ' . mysql_error());

}

function insertData()
{

	// Insert a row of information into the table "example"
	mysql_query("INSERT INTO sales(salesgroup, dollars) VALUES( 'xmen', 120) ")
		or die(mysql_error());


}


?>


