<?php
// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2019
//
// LibLapin

$ErrorHappened = false;
function BAssert($test, $msg = "")
{
  global $ErrorHappened;

  if (!$test)
  {
    echo $msg."\n";
    $ErrorHappened = true;
  }
}

