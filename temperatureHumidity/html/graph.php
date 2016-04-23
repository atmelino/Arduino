<?php 

require_once ('../lib/jpgraph/jpgraph.php');
require_once ('../lib/jpgraph/jpgraph_line.php');
require_once ('../lib/jpgraph/jpgraph_date.php');
require_once ('../lib/jpgraph/jpgraph_utils.inc.php');
//require_once ('./login.inc.php');
//include ('./login2.inc.php');



global $t;
global $range;
global $debug;
global $table;
$debug=true;
$debug=false;


function getData($hostname,$username,$password,$database)
{
	global $xdata;
	global $datat;
	global $datah;
	global $range;
	global $debug;
	global $starttime;
	global $endtime;
	global $range;
	global $hostname,$username,$password,$database,$table;
	global $table;
	global $IPAddress;
	
	connect($hostname,$username,$password,$database);


	//$link = mysql_connect('localhost', 'root', '1234')
	//or die('Could not connect: ' . mysql_error());

	//mysql_select_db('ardtemphumid') or die('Could not select database');

	$endtime=time();
	//$range=40000;
	$starttime=$endtime-$range;
	//$starttime=$endtime-100000;
	//$starttime=1200000000;
	if($debug)
	{
		echo "getData range start end time";
		var_dump($range);
		var_dump($starttime);
		var_dump($endtime);
	}
	$i=1;

	// extend x-axis to left end of range
	//$xdata[0]=$starttime-1;
	$xdata[0]=0;
	$datat[0]="";
	$datah[0]="";

	//$table="11_0_0_177";
	$table=str_replace(".", "_", $IPAddress);
	
	//$table=$IPAddress;
	
	//get data from database
	$sql="SELECT * from $table WHERE seconds BETWEEN $starttime AND $endtime";
	$result = mysql_query($sql) or die('Query failed: ' . mysql_error());
	if ($result) {
		while ($row = mysql_fetch_assoc($result)) {
			$seconds=$row["seconds"];
			$valuet=$row["temperature"];
			$valueh=$row["humidity"];

			//add to data array
			$xdata[$i]=$seconds;
			//$xdatad[$i]=date('Y-m-d H:i',$seconds);
			$datat[$i]=$valuet;
			$datah[$i]=$valueh;


			if($debug)
			{
				echo $row['seconds'] . " " . $row['date'] . " " . $row['temperature'] . " " . $row['humidity'] . "\n";
				echo $xdata[$i]. " ". $datat[$i].  "\n";
			}

			//echo $row['date'] . " " . $row['temperature'] . " " . $row['humidity'];
			//echo "<br />";
			//echo "\n";
			//echo $i;
			//echo " ";
			//echo $datay1[$i];
			//echo "\n";
			++$i;

		}
	}

	// extend x-axis to left end of range
	$xdata[$i]=$endtime+1;
	$datat[$i]="";
	$datah[$i]="";

}

function connect($hostname,$username,$password,$database)
{
	//connection to the database
	$con = mysql_connect($hostname,$username,$password)
	or die('Could not connect: ' . mysql_error());

	//select the database
	mysql_select_db($database, $con)
	or die('Could not select database: ' . mysql_error());

}

function graphit()
{
	global $xdata;
	global $datat;
	global $datah;
	global $t;
	global $debug;
	global $starttime;
	global $endtime;
	global $range;


	if($debug){
		echo "graphit start end time\n";
		var_dump($starttime);
		var_dump($endtime);
	}


	// Setup the graph
	$graph = new Graph(700,500);
	// Adjust the margin to make room for the X-labels
	//$graph->SetMargin(40,30,40,120);
	$graph->SetMargin(100,30,40,100);
	$graph->SetMarginColor('white');

	//$graph->SetScale('datlin');
	//$graph->SetScale('datint');
	$graph->SetScale('intlin',0,100,$starttime,$endtime);
	//$graph->SetScale('intlin',0,100,$starttime,1461565980);

	//$output = 'Parameter: ' .$range ;
	//$graph->title->Set('Parameter:' . $range);
	//$graph->title->SetFont(FF_ARIAL,FS_NORMAL,14);
	$graph->xaxis->SetFont(FF_ARIAL,FS_NORMAL,8);
	$graph->xaxis->SetLabelAngle(30);
	$graph->xaxis->SetLabelFormatString('m/d/Y H:i:s',true);


	$graph->SetYScale(0,'lin');

	$p1 = new LinePlot($datat,$xdata);
	$p1->SetColor('red');
	$p1->SetLegend('Temperature [F]');
	$graph->Add($p1);
	$graph->yaxis->SetColor('red');

	$p2 = new LinePlot($datah,$xdata);
	$p2->SetColor('teal');
	$p2->SetLegend('Humidity [%]');

	$graph->AddY(0,$p2);
	$graph->ynaxis[0]->SetColor('teal');

	//$graph->legend->SetPos(0.5,0.98,'center','bottom');
	$graph->legend->SetPos(0.5,0.01,'center','top');
	// Output line
	if(!$debug){
		$graph->Stroke();
	}
}

function debugSave($hostname,$username,$password,$database,$value)
{
	global $IPAddress;

	connect($hostname,$username,$password,$database);
	mysql_query("UPDATE arddebug SET value='$value' WHERE id = 1");
	//or die(mysql_error());
	//mysql_query("INSERT INTO arddebug VALUES (1,'IPString','n') ") or reportErrorData();
	//mysql_query("INSERT INTO Persons	VALUES (4,'Nilsen', 'Johan', 'Bakken 2', 'Stavanger')");
	// this worked:
	//mysql_query("UPDATE ardoption
	//	SET debugStr='$IPAddress'
	//WHERE id = 1")
	//	or die(mysql_error());
	

}


if( empty($_GET['r']) )
	$range=3600;
else
	$range= $_GET['r'];

if( empty($_GET['i']) )
	$IPAddress="not got";
else
	$IPAddress= $_GET['i'];




$hostname="localhost";
$username="root";
$password="1234";
$database="ardNetSense";



//debugSave($hostname,$username,$password,$database,'hello');
//debugSave($hostname,$username,$password,$database,$range);
debugSave($hostname,$username,$password,$database,$IPAddress);


getData($hostname,$username,$password,$database);

graphit();


//mysql_close($con);


?>
