<?php
  header("Cache-Control: no-cache"); 
  header("Content-Type: text/html");

  include_once("config.php");
  //print_r($_POST);
  //echo "<span style=\"color:red\">".$_POST['problemid']."<br /></span>";
  $problemid = mysql_real_escape_string($_POST['problemid']);
  $code = html_entity_decode(htmlentities($_POST['code']));
  $userid = $_SESSION['userid'];
  $ts = time(); //approx timestamp of submission

  $filename = "files/source".$userid.$ts.".c";

  $fd = fopen($filename, 'w');
  if ( fwrite($fd, $code) ){
    fclose($fd);
    if(mysql_query("INSERT INTO compile_table VALUES ($problemid, $userid, '$filename', $ts, 0)", $db))
        echo "Your solution has been sumbitted. Check your score table";
    else
        echo mysql_error();
  }
  else
    echo "The server faced some difficulties. Please retry";

?>
