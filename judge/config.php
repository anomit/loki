<?php
session_start();

require('/usr/local/lib/php/Smarty/Smarty.class.php');
$smarty_dir = "/home/anomit/code/smarty/";

$smarty = new Smarty(); 

$smarty->template_dir = $smarty_dir.'templates';
$smarty->compile_dir = $smarty_dir.'templates_c';
$smarty->cache_dir = $smarty_dir.'cache';
$smarty->config_dir = $smarty_dir.'configs';

$db  = mysql_connect('localhost','root','mysql');
mysql_select_db('judge', $db);
?>
