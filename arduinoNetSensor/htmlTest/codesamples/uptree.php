<?php

//Function defined here
//The variables will come from the ajax data statement
function updatetree($node, $option) {

  if($node == '' || $option == '') {
    return 'Select an item in the tree.';
  }

  $dbco = mysql_connect('localhost', 'root', 'mmowebdb');
  if (!$dbco)
    {
    die('Could not connect: ' . mysql_error());
    }

  mysql_select_db("pagelinks", $dbco);

  $sql = '';
  switch($option) {
     case 'delete':
        $sql = "DELETE FROM dtree_table WHERE nid='$node'";
        break;
     case 'add':
        list($pagename, $address) = explode(",", $page);
        $pagename = trim($pagename);
        $address = trim($address);
        $sql = "INSERT INTO dtree_table (nid, pid, name, url) values (NULL, ".$node.", '".$pagename."', '".$address."')";
        break;
     case 'update':
        break;
  }

  if (!empty($sql)) return $sql;
}

//echo statement to run function, variables sent by ajax are retrieved with $_REQUEST
//they could have also been retrieved with $_GET or $_POST
echo updatetree(trim($_REQUEST['node']),trim($_REQUEST['option']),trim($_REQUEST['page']));

?>