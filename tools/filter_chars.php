<?php
// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2019
//
// LibLapin

function filter_chars($str, $authorized)
{
  $authorized = str_split($authorized);
  for ($i = 0, $l = strlen($str); $i < $l; ++$i)
    if (in_array($str[$i], $authorized, true) == false)
      return (false);
  return (true);
}

