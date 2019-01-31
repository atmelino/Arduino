<?php
include("phpgraphlib.php");
$graph=new PHPGraphLib(550,350); 

$link = mysql_connect('localhost', 'root', '1234')
   or die('Could not connect: ' . mysql_error());
     
mysql_select_db('ardtemphumid') or die('Could not select database');
  
$dataArray=array();
  
//get data from database
$sql="SELECT * from arddata";
$result = mysql_query($sql) or die('Query failed: ' . mysql_error());
if ($result) {
  while ($row = mysql_fetch_assoc($result)) {
      $salesgroup=$row["salesgroup"];
      $count=$row["count"];
      //add to data areray
      $dataArray[$salesgroup]=$count;
  }
}
  
//configure graph
$graph->addData($dataArray);
$graph->setTitle("Sales by Group");
$graph->setGradient("lime", "green");
$graph->setBarOutlineColor("black");
$graph->createGraph();
?>
