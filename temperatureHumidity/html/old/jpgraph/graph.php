<?php
//header('Content-Type: text/javascript; charset=UTF-8');


require_once("../lib/jpgraph/src/jpgraph.php");
require_once("../lib/jpgraph/src/jpgraph_bar.php");
//require_once("./login.inc.php");

$hostname="localhost";


//error line below is VERY helpful tracking down blank graph errors.
error_reporting(E_ALL); ini_set('display_errors', '1');

require_once("./login.inc.php");
//test();

require_once("./login.inc.php");
getmySQLdata($hostname,$username,$password,$database);
function getmySQLdata($hostname,$username,$password,$database)
{

	connect($hostname,$username,$password,$database);
	$datay = array();
	$query=("SELECT * FROM arddata");
	$result=mysql_query($query);

	$rowcount = mysql_num_rows($result);
	echo $rowcount;
	echo "<br />";


	if ($rowcount == 10080){
		// if the DB has enough data to make a complete graph fill array and go
		while($row = mysql_fetch_array($result)) {

			$datay[] = $row['temperature'];

		}
	}else{
		echo "else";
		echo "<br />";

		// if the DB does not have enough data to make a complete graph
		// add what's in DB so far to the array and fill the rest with 0 values
		while($row = mysql_fetch_array($result)){
			echo $row['temperature'];
			echo "<br />";
			$datay[] = $row['temperature'];
		}
	}

	mysql_close();

	echo "<br>";
	var_dump($datay);

}

function test()
{

	$data1y=array(-8,8,9,3,5,6);
	$data2y=array(18,2,1,7,5,4);

	// Create the graph. These two calls are always required
	$graph = new Graph(500,400);
	$graph->SetScale("textlin");

	$graph->SetShadow();
	$graph->img->SetMargin(40,30,20,40);

	// Create the bar plots
	$b1plot = new BarPlot($data1y);
	$b1plot->SetFillColor("orange");
	$b1plot->value->Show();
	$b2plot = new BarPlot($data2y);
	$b2plot->SetFillColor("blue");
	$b2plot->value->Show();

	// Create the grouped bar plot
	$gbplot = new AccBarPlot(array($b1plot,$b2plot));

	// ...and add it to the graPH
	$graph->Add($gbplot);

	$graph->title->Set("Accumulated bar plots");
	$graph->xaxis->title->Set("X-title");
	$graph->yaxis->title->Set("Y-title");

	$graph->title->SetFont(FF_FONT1,FS_BOLD);
	$graph->yaxis->title->SetFont(FF_FONT1,FS_BOLD);
	$graph->xaxis->title->SetFont(FF_FONT1,FS_BOLD);

	// Display the graph
	$graph->Stroke();
}



function connect($hostname,$username,$password,$database)
{

	echo "connect<br>";
	echo $hostname;
	echo "<br>";
	echo $username;
	echo "<br>";

	//connection to the database
	$con = mysql_connect($hostname,$username,$password,$database)
	or die('Could not connect: ' . mysql_error());

	//select the database
	mysql_select_db($database, $con)
	or die('Could not select database: ' . mysql_error());

}

?>

