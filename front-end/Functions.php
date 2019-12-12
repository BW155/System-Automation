<?php

class Functions
{
$db = null;

  public function saveData($data)
  {

    # Make db connection
  	$redis = new Redis();
    $redis->connect("127.0.0.1",6379);
    $redis->auth("redbanaan");
    # process data
    $db = $this->db;

    # check if results
    return true;
  }


}