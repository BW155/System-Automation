<?php
include 'Functions.php';
//print_r('<pre>');
$input1 = $_POST['input-1'];
$input2 = $_POST['input-2'];
$msg = '';
# Call functions to process data
$function = new Functions();
$result1 = $input1 ? $function->setData("deur", $input1) : '';
$result2 = $input2 ? $function->setData("deur", $input2) : '';

if ($result1 || $result2) {
  $value = $result1 ?: $result2;
  $msg = 'the door will now  ' .$value;
}
?>

<!DOCTYPE html>
<html>
<head>
  <title>Request Handle</title>
</head>
<body>
<div>
  <?php if (isset($msg)) {
    echo '<h2>' . $msg . '</h2>';
  } ?>
</div>
</body>
</html>



