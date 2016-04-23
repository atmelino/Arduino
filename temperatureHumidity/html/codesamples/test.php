<!DOCTYPE HTML PUBLIC "-//W3C//DTD HTML 4.01 Transitional//EN">
<html>
  <head>

    <meta http-equiv="content-type" content="text/html; charset=ISO-8859-1">
  </head>
  <body>
<?php

 print("Hello World");

myFunction2();


 function myFunction2()
 {

   print("function called");
 }




?>
    <br>
    <br>
<FORM METHOD="LINK" ACTION="insert.php">
<INPUT TYPE="submit" VALUE="Add data">
</FORM>   
 <br>


    <br>
<FORM METHOD="LINK" ACTION="test.php">
<INPUT TYPE="submit" VALUE="lets see what happens">
</FORM>   
 <br>
  

<br>
<button onclick="myFunction2()">Click me</button>


<br>
<button onclick="myFunction()">Click me</button>
 <textarea rows="1" cols="12" id="IP">
</textarea><br />
      <script type="text/javascript">
 function myFunction()
 {
        document.getElementById('IP').innerHTML="clicked";     
 }


</script>
</body>
</html>











<body>

  Start Simulation
    <form action="control.php" method="post">
     <br>
      <input type="submit">
    </form>
 </body>





<?php

 print("Hello World");


$var = '';

// This will evaluate to TRUE so the text will be printed.
if (isset($var)) {
    echo "This var is set so I will print.";
}


  //myFunction2();


 function myFunction2()
 {

   print("function called");
 }




?>

