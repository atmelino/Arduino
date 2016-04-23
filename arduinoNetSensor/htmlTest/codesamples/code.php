
<!DOCTYPE html 
     PUBLIC "-//W3C//DTD XHTML 1.0 Strict//EN"
     "http://www.w3.org/TR/xhtml1/DTD/xhtml1-strict.dtd">
<html>
	<head>
		<title>PHP Test</title>
	</head>
	<body>
		<?php
		 	if(!isset($_POST['submit'])){
		?>
 
		<form action="<?php echo $_SERVER['PHP_SELF']; ?>" method="post">
		Enter your age: <input name="age" size="2">
		<input type="submit" name="submit" value="Go">
 
		<?php 
			} else {
				//Grab the text we input
				$input = $_POST['age'];
 
				if($input < 27){
					echo "You are young";
				} elseif($input == 27){
					echo "The perfect age";
				} elseif($input > 27){
					echo "You are old!";
				}
			}
		?>
	</body>
</html>








