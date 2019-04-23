<?php
// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2019
//
// LibLapin

function json_file($file)
{
  $cnt = file_get_contents($file);
  $cnt = str_replace("\r", "", $cnt);
  $cnt = str_replace(" ", "&nbsp;", $cnt);
  $cnt = str_replace("\t", "&nbsp;&nbsp;&nbsp;&nbsp;", $cnt);

  $cnt = str_replace("<", '&lt;', $cnt);
  $cnt = str_replace(">", '&gt;', $cnt);

  $cnt = preg_replace("/\/\/.+/", '<span style="color: red;">${0}</span>', $cnt);
  $cnt = preg_replace("/\/\*(.+?)\*\//s", '<span style="color: red;">${0}</span>', $cnt);

  $cnt = str_replace("@", "&#64;", $cnt);
  $cnt = str_replace("\n", "<br/>", $cnt);
  return ($cnt);
}
