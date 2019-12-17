<!DOCTYPE html>
<html>
<head>
  <title>Page Title</title>
</head>
<body>
<h1>Deur</h1>
<!-- First call -->
<form method="post" action="HandleRequests.php">
  <div class="form-group">
    <input type="hidden" value="open" name="input-1" id="input-1">
    <input type="submit" value="Open">
  </div>
</form>

<!-- Second call -->
<form method="post" action="HandleRequests.php">
  <div class="form-group">
    <input type="hidden" value="close" name="input-2" id="input-2">
    <input type="submit" value="Close">
  </div>
</form>
</body>
</html>



