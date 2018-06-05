<html>
	<head>
		<title>Garbage monitoring </title>
		<style>
		html, body{
			background-color: #F2F2F2;
			font-family: Arial;
			font-size: 1em;
		}
		table{
			border-spacing: 0;
			border-collapse: collapse;
			margin: 0 auto;
			width: 90%;
		}
		th{
			padding: 8px;
			background-color: #FF837A;
			border: 1px solid #FF837A;
		}
		td{
			padding: 10px;
			background-color: #FFF;
			border: 1px solid #CCC;
		}
		
		p{
			margin: 0 0 1em 0;
		}
		
		div.contentcontainer{
			margin: 10px auto;
			width: 90%;
			background-color: #FFF;
			padding: 10px;
		}
		div.title{
			font-weight: bold;
			font-size: 1.5em;
			text-decoration: underline;
		}
		div.subtitle{
			font-weight: bold;
			font-size: 1.2em;
		}
		div.content{
			font-size: 1em;
		}
		</style>
	</head>
	<body>
	<meta http-equiv="refresh" content="5" >
		<?php	
			
			$servername = "localhost";
			$username = "root";
			$dbname = "iotdb";
			$password = "";

			
			$conn = mysqli_connect($servername, $username, $password, $dbname);
			if (!$conn) {
				die("Connection failed: " . mysqli_connect_error());
			}
			
			if ($result = mysqli_query($conn, "SELECT Date FROM sens_data")) {

				$row_cnt = mysqli_num_rows($result);

			printf("The database has %d entries.", $row_cnt);
			}
		
			$result = mysqli_query($conn, "SELECT Date, Time, sensor FROM sens_data ORDER BY date DESC, time DESC  LIMIT 25");
			echo "<table><tr><th>Date</th><th>Time</th><th>Sensor</th></tr>";
			while($row = mysqli_fetch_assoc($result)) {
				echo "<tr><td>";
				echo $row["Date"];
				echo "</td><td>";   
				echo $row["Time"];
				echo "</td><td>";
				echo $row["sensor"];
				echo "</td></tr>";
			}
			echo "</tr></table>";

			
			mysqli_close($conn);
		?>
		
	</body>
</html>