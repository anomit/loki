<html>
  <head>  
    <script type="text/JavaScript" src="jquery.js"></script> 
    <script type="text/javascript">
      $(document).ready(function(){
        $("#submit").click(function(){
          $.post("submit.php",{
                  problemid: $("#problemid").val(),
                  code: $("#solution").val()
                },function(data){
                  $("div").html(data);
                });
        });
      });
    </script>
  </head>
  <body>
      <textarea rows="30" cols="50" id='solution'></textarea>
      <input type="hidden" value=<?php echo $_GET['id']; ?> name='id' id='problemid' />
      <input type="button" name="submit" value="submit" id="submit" />
      <div id="result"></div>
  </body>
</html>
