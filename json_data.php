<!DOCTYPE html>  
 <html>  
      <head>  
           <title>garbage-IOT</title>  
      </head>  
      <body>  
           <?php   
           $connect = mysqli_connect("localhost", "root", "", "garbage");  // i forget the database name and id so please add by yourself
           $sql = "SELECT * FROM sens_data";  // added as per our project
           $result = mysqli_query($connect, $sql);  
           $json_array = array();  
           while($row = mysqli_fetch_assoc($result))  
           {  
                $json_array[] = $row;  
           }  
           echo '<pre>';  
           print_r(json_encode($json_array));  
           echo '</pre>';  
           echo json_encode($json_array);  
           ?>  
      </body>  
 </html> 