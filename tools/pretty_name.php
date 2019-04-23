<?php
// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2019
//
// LibLapin

function pretty_name($name)
{
  $cap = true;
  for ($i = 0, $l = strlen($name); $i < $l; ++$i)
    if ($name[$i] == '_')
      $cap = true;
    else if ($cap)
    {
      $name[$i] = strtoupper($name[$i]);
      $cap = false;
    }
  return (str_replace("_", "", $name));
}

