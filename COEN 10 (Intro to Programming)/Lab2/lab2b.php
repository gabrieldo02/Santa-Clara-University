<html>
<body>
<?php
$number1=$_POST["number1"];
$number2=$_POST["number2"];
$number3=$_POST["number3"];
	if ($number1*$number2==$number3) echo "Good Job";
	else echo "You need practice, Correct Answer:".$number1*$number2;
?> 

<form method="POST" action="lab2a.php">
<input type="submit" value="Try again" />

</form>
</body>
</html>
