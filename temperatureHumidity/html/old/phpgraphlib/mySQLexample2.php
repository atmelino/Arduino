<?php
include("phpgraphlib.php");
$graph=new PHPGraphLib(800,500); 

$link = mysql_connect('localhost', 'root', '1234')
   or die('Could not connect: ' . mysql_error());
     
mysql_select_db('ardtemphumid') or die('Could not select database');
  
$dataArray=array();
  
//get data from database
$sql="SELECT * from arddata";
$result = mysql_query($sql) or die('Query failed: ' . mysql_error());
if ($result) {
  while ($row = mysql_fetch_assoc($result)) {
      $date=$row["date"];
      $valuet=$row["temperature"];
      $valueh=$row["humidity"];
      //add to data areray
      $dataArray[$date]=$valuet;
      $dataArrayh[$date]=$valueh;
  }
}
  


$graph->addData($dataArray);
$graph->addData($dataArrayh);
$graph->setTitle('Temperature/Humidity');
$graph->setBars(false);
$graph->setLine(true);
$graph->setDataPoints(true);
$graph->setDataPointColor('maroon');
$graph->setDataValues(true);
$graph->setDataValueColor('maroon');
$graph->setGoalLine(.0025);
$graph->setGoalLineColor('red');
$graph->createGraph();


//configure graph
//$graph->addData($dataArray);
//$graph->setTitle("Temperature");
//$graph->setGradient("lime", "green");
//$graph->setBarOutlineColor("black");
//$graph->createGraph();
?>
