<!--
Gabriel Do
COEN 10L
Monday 2:15pm
-->

<html>
<body>

<?php
$n1=$_POST["number1"];
$n2=$_POST["number2"];
$n3=$_POST["number3"];
$n4=$_POST["number4"];
$n5=$_POST["number5"];
$userInputArr=array ($n1,$n2,$n3,$n4,$n5);
$randArr=array (0,0,0,0,0);

$counter=0;
$size1=count($userInputArr);
$size2=count($randArr);
for ($i=0;$i<$size1;$i++) //iterate through all elements in randArr
{
        $randArr[$i]=rand(1,20);
        for ($k=0;$k<$i;$k++) //iterate through all elements before this element in randArr
        {
                if ($randArr[$i]==$randArr[$k]) //current element is the same as an element from before
                {
                        $randArr[$i]=rand(1,20); //set new rand number
                        $k=0; //restart loop
                }
        }
        for($j=0; $j<$size2;$j++) // iterate through all elements in userInputArr
        {
                if ($userInputArr[$j]==$randArr[$i])
                {
                        $counter++;
                        break;
                }
        }
$inputStr1=$inputStr1.$randArr[$i]." "; //add current element to string to be outputed
$inputStr2=$inputStr2.$userInputArr[$i]. " ";
}
echo "The lottery numbers are: ".$inputStr1."<br>";
echo "You guessed: " .$inputStr2."<br>";
echo "You have " .$counter. " match(es)."."<br>";
?>
<form method= "POST" action= "lab4.html">
<input type="submit" value="Try again?"/>
<body>
<html>      
