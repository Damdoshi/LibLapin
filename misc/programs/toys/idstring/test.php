#!/usr/bin/php
<?php
function rstr($len)
{
  $pol = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ1234567890";
  $randstring = '';
  for ($i = 0; $i < $len; $i++)
    $randstring .= $pol[rand(0, strlen($pol) - 1)];
  return $randstring;
}

for ($i = 0; $i < 50000; ++$i)
{
  echo "'".rstr(rand(0, 20))."'";
  echo " ";
}

