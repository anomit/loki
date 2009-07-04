<?php
  require_once('config.php');
  //test stuff, replace with authentication module
  $_SESSION['userid'] = 1;

  $problemrec = mysql_query('SELECT problemid, title FROM problem');
  $problemArr = array();
  
  while( ( $row = mysql_fetch_assoc($problemrec) ) )
    $problemArr[] = $row;
    
  $smarty->assign('problems',$problemArr);
  $smarty->display('index.tpl');

?>
