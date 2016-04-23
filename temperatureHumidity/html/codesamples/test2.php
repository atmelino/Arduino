<HTML>

<head>

    <script language="JavaScript" type="text/javascript">

    function onload_function() {


	    refreshIt(); // refresh every x secs
}


    function refreshIt() {


   //javaFunction();

        setTimeout('refreshIt()',1000); // refresh every x secs

}



</script>
</head>

 <BODY onload=" onload_function()">





  <?php 
   if (isset($_GET[action])){
	// Retrieve the GET parameters and executes the function
	  $funcName	 = $_GET[action];
	  $vars	  = $_GET[vars];
	  $funcName($vars); 
	 } else if (isset($_POST[action])){
	  // Retrieve the POST parameters and executes the function
	  $funcName	 = $_POST[action];
	$vars	  = $_POST[vars];
	$funcName($vars); 
	  
	 } else {
	  // If there is no action in the URL, then do this
	echo "<INPUT NAME='btnSubmitAdmin' TYPE='button' ONCLICK='javascript:javaFunction()' VALUE='Call Javafunction() which redirects to a PHP function'>";
   }
	 
   function phpFunction($v1){
	// makes an array from the passed variable 
	// (note: $vars = 1 string while it used to be a javascript Array)
	// with explode you can make an array from 1 string. The seperator is a , 
	$varArray = explode(",", $v1);
	
	echo "<BR>function phpFunction<BR><BR>"; 
	echo "v1: $varArray[0] <BR>";
	echo "v2: $varArray[1]<BR>";
	

   }









  ?>
 
 
  <SCRIPT language="javascript">
   function javaFunction(){
	// In the varArray are all the variables you want to give with the function
	var varArray = new Array();
	varArray[0] = "var1";
	varArray[1] = "var2";
   
	// the url which you have to reload is this page, but you add an action to the GET- or POST-variable
	var url="<?php echo $_SERVER[PHP_SELF];?>?action=phpFunction&vars="+varArray;
	
	// Opens the url in the same window
	   window.open(url, "_self");
	  }
  </SCRIPT>




 </BODY>
</HTML>




