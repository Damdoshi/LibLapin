#!/usr/bin/php
<?php
// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2019
//
// LibLapin

$stack = "";

function stack($buf)
{
  global $stack;

  $stack .= $buf;
  return $buf;
}

function minify($code)
{
  //
  return ($code);
}

ob_start();
require_once ("./tools/index.php");
ob_end_clean();

echo minify($stack);

