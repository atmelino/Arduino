
<!DOCTYPE html 
     PUBLIC "-//W3C//DTD XHTML 1.0 Strict//EN"
     "http://www.w3.org/TR/xhtml1/DTD/xhtml1-strict.dtd">
<html>
<head>
<title>PHP Test</title>
</head>
<body>
	<?php
	if(!isset($_POST['insert'])  && !isset($_POST['start']) && !isset($_POST['stop'])&& !isset($_POST['startscript'])   && !isset($_POST['showscript'])   ){
		?>


	Show if System Script is running
	<form action="<?php echo $_SERVER['PHP_SELF'] ?>" method="post">
		<input type="submit" name="showscript" value="Go">
	</form>
	<br>Start System Script
	<form action="<?php echo $_SERVER['PHP_SELF'] ?>" method="post">
		<input type="submit" name="startscript" value="Go">
	</form>
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

		if(isset($_POST['showscript']))
			showScriptStatus();
		
		if(isset($_POST['startscript']))
			startSystemScript();

		if(isset($_POST['insert']))
			insertDataPoint();

		if(isset($_POST['start']))
			startSimulation();

		if(isset($_POST['stop']))
			stopSimulation();
	}


	function showScriptStatus()
	{
		echo '<pre>';

		// Outputs all the result of shellcommand "ls", and returns
		// the last output line into $last_line. Stores the return value
		// of the shell command in $retval.
		$last_line = system('ps aux | grep php', $retval);

		// Printing additional info
		echo '
		</pre>
		<hr />Last line of the output: ' . $last_line . '
		<hr />Return value: ' . $retval;
	}
	function startSystemScript()
	{

		system('php5 scripts/dataLoop.php&');
		echo "Script started!";
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
		include("login.inc.php");

		//connection to the database
		$con = mysql_connect($hostname,$username,$password)
		or die('Could not connect: ' . mysql_error());

		//select the database
		mysql_select_db($database, $con)
		or die('Could not select database: ' . mysql_error());


		// Insert a row of information into the table "example"
		mysql_query("INSERT INTO arddata
				(date, temperature,humidity) VALUES(now(), 100*rand(),100*rand() ) ")
				or die(mysql_error());

		echo "Data Inserted!";
	}

	?>
</body>
</html>
