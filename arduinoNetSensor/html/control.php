<!DOCTYPE html 
     PUBLIC "-//W3C//DTD XHTML 1.0 Strict//EN"
     "http://www.w3.org/TR/xhtml1/DTD/xhtml1-strict.dtd">
<html>
<head>
<title>PHP Test</title>
</head>
<body>
	<?php

	$table='11_0_0_178';
	
	if(!isset($_POST['insert'])  && !isset($_POST['start']) && !isset($_POST['stop'])&& !isset($_POST['startscript'])   && !isset($_POST['showscript'])   ){
		?>

	<br>Start Simulation
	<form action="<?php echo $_SERVER['PHP_SELF'] ?>" method="post">
		<input type="submit" name="start" value="Go">
	</form>
	<br> Stop Simulation
	<form action="<?php echo $_SERVER['PHP_SELF'] ?>" method="post">
		<input type="submit" name="stop" value="Go">
	</form>

	<br> Add Data Point
	<form action="<?php echo $_SERVER['PHP_SELF'] ?>" method="post">
		<input type="submit" name="insert" value="Go">
	</form>
	<br>Clear all measurement data
	<form action="clearData.php" method="post">
		<input type="submit">
	</form>
	<br>

	<?php 
	} else {


		if(isset($_POST['insert']))
			insertDataPoint();

		if(isset($_POST['start']))
			startSimulation();

		if(isset($_POST['stop']))
			stopSimulation();
	}


	function startSimulation()
	{

		include("login.inc.php");

		//connection to the database
		$con = mysql_connect($hostname,$username,$password)
		or die('Could not connect: ' . mysql_error());

		//select the database
		mysql_select_db($database, $con)
		or die('Could not select database: ' . mysql_error());


		// change mode
		mysql_query("UPDATE ardoption
			SET loopOnOff='1'
			WHERE id = 1")
			or die(mysql_error());

		echo '<pre>';
		echo "Simulation started!";

	}

	function stopSimulation()
	{

		include("login.inc.php");

		//connection to the database
		$con = mysql_connect($hostname,$username,$password)
		or die('Could not connect: ' . mysql_error());

		//select the database
		mysql_select_db($database, $con)
		or die('Could not select database: ' . mysql_error());


		// change mode
		mysql_query("UPDATE ardoption
			SET loopOnOff='0'
			WHERE id = 1")
			or die(mysql_error());

		echo "Simulation stopped!";

	}

	function insertDataPoint()
	{
		global $table;
		
		include("login.inc.php");

		//connection to the database
		$con = mysql_connect($hostname,$username,$password)
		or die('Could not connect: ' . mysql_error());

		//select the database
		mysql_select_db($database, $con)
		or die('Could not select database: ' . mysql_error());


		// Insert a row of information into the table "example"
		$unixtime=time();
		mysql_query("INSERT INTO $table
			(seconds, date, temperature,humidity) VALUES($unixtime,now(), 100*rand(),100*rand() ) ")
			or die(mysql_error());

		echo "Data Inserted!";
	}

	?>
</body>
</html>
