<html>
<head>
<title>Top 25 Stocks</title>
<style>
table tr:nth-child(odd) {
    background-color: #e0dcdc;
}
table{
    margin: 0 auto;
    text-align: center;
    font-size: 20px;
    width: 85%;
    border-collapse: collapse;
}
h1{
    text-align: center;
    padding: 5px; 
    font-size: 28px;
    color: red;
}
h2{
    text-align: center;
    color: red;
}
}
</style>
</head>
<body>
<h1>Top 25 Stocks</h1>

<?php 
$username = "cs288"; 
$password = "cs288"; 
$database = "stock"; 
$mysqli = new mysqli("127.0.0.1", $username, $password, $database); 

// get most recent stock table 
$result = mysqli_query($mysqli, "show tables"); // run the query and assign the result to $result
$rows = mysqli_num_rows($result);  
$cnt = 0; 
while($table = mysqli_fetch_array($result)) { // go through each row that was returned in $result
    $cnt++; 
    if( $cnt == $rows ){
        $tbl = $table[0]; 
    }
}
echo '<h2>Table: '.$tbl.'</h2>'; 

// get data from table 
$x = 0; 
$query = "SELECT * FROM ".$tbl; 
echo '<table border="5" cellspacing="0" cellpadding="0"> 
      <tr> 
          <td> <font color = "red" face="Georgia"> <b> Symbol </b> </font> </td> 
          <td> <font color = "red" face="Georgia"> <b> Name </b> </font> </td> 
          <td> <font color = "red" face="Georgia"> <b> Price (USD) </b> </font> </td> 
          <td> <font color = "red" face="Georgia"> <b> Change (USD) </b> </font> </td> 
          <td> <font color = "red" face="Georgia">% <b> Change</font> </b> </td> 
          <td> <font color = "red" face="Georgia"> <b> Volume (M) </b> </font> </td> 
          <td> <font color = "red" face="Georgia"> <b> Avg Volume (3 Months) </b> </font> </td> 
          <td> <font color = "red" face="Georgia"> <b> Market Cap (B)</b> </font> </td> 
      </tr>';
if ($result = $mysqli->query($query)) {
    while ($row = $result->fetch_assoc()) {
        $symbol = $row["symbol"];
        $name = $row["name"];
        $price = $row["price"];
        $change = $row["chng"];
        $pchange = $row["pchng"]; 
        $vol= $row["volume"]; 
        $avol= $row["avg"]; 
        $mcap= $row["mcap"]; 

        echo '<tr> 
                  <td>'.$symbol.'</td> 
                  <td>'.$name.'</td> 
                  <td>'.$price.'</td> 
                  <td>'.$change.'</td> 
                  <td>'.$pchange.'</td> 
                  <td>'.$vol.'</td> 
                  <td>'.$avol.'</td> 
                  <td>'.$mcap.'</td> 
              </tr>';
    }
    $result->free();
    $x++; 
} 
?>
</body>
</html>