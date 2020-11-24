<?php
$value = $_GET["value"];
$another_value = $_GET["another_value"];

# Prepare the data
$date = date("Y-m-d H:i:s");
$data = sprintf("On %s the value is %s and another_value is %s\n", $date, $value, $another_value);
# Save it
file_put_contents("data.txt", $data, FILE_APPEND);

# And we need to answer the client. We just tell the date ;)
echo $date;
