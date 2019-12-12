<?php
include 'Functions.php';
//print_r('<pre>');

$input = $_POST['input-1'];
$msg = '';
# Call functions to process data
$function = new Functions();
$result = $function->saveData($input);
if ($result) {
  $msg = 'your Data has been saved!!';
}
?>

<!DOCTYPE html>
<html>
<head>
  <title>Page Title</title>
</head>
<body>
<h1><?php echo $input ?></h1>
<div>
  <?php if (isset($msg)) {
    echo '<h2>' . $msg . '</h2>';
  } ?>
</div>
</body>
</html>
