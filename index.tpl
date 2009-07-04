<html>
	<head>
	</head>
	
	<body>
	  <table border="1">
        {foreach from=$problems key=k item=v}            
          <tr>
            <td><a href="problem.php?id={$v.problemid}">{$v.title}</a></td>
            <td>50</td>
          <tr>
        {/foreach}
	  </table>
	</body>
</html>
