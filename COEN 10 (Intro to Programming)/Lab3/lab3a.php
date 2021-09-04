<html>
<body>

<?php
$n=$_POST["number"];
$checkNum=-1;
$x=array (0,0,0,0,0);

$size=count($x);
	for($i=0;$i<$size;$i++)
{
	$x[$i] = rand(1,20);
	echo $x[$i]." ";
		if ($n==$x[$i]) $checkNum=$n;
}
if($checkNum!=-1) echo "You got it!";
else echo "Wrong!";
?>

<form method = "POST" action="lab3.html">
<input type="submit" value="Try again"/>
</form>
</body>
</html>

