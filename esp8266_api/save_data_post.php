<?php
$data = json_decode(file_get_contents("php://input"));
# Prepare the data
$date = date("Y-m-d H:i:s");
$value = $data->value;
$another_value = $data->another_value;
$data = sprintf("On %s the data is %s and another_value is %s\n", $date, $value, $another_value);
# Save it
file_put_contents("data_post.txt", $data, FILE_APPEND);

# And we need to answer the client. We just tell the date ;)
echo $date;
