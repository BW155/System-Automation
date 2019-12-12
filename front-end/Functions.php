<?php

class Functions
{  
  public function setData($object, $action)
  {

    # Make db connection
    $redis = new Redis();
    $redis->connect("127.0.0.1",6379);
    $redis->auth("redbanaan");

    # process data
     $redis->set($object, $action);
     $getBack = $redis->get($object);     

    # verify the set
    return $getBack;
  }     

}

