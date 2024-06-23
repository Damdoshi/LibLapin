<?php

function skip_int_label($str)
{
  for ($i = 0, $l = strlen($str); $i < $l; ++$i)
    if ($str[$i] < '0' || $str[$i] > '9')
    {
      while ($i < $l && $str[$i] == '_')
        $i += 1;
      return (substr($str, $i));
    }
  return ($str);
}

