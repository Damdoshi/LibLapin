<?php
// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2019
//
// LibLapin

function get_all_symbols($root, $type, $base = null)
{
  if ($base)
    $sym = $base;
  else
    $sym = [];
  $i = count($sym);
  foreach (scandir("$root/") as $mod)
  {
    if ($mod[0] != "."
        && strstr($mod, ".php") == false
        && $mod[strlen($mod) - 1] != "~"
    )
    {
      foreach (scandir("$root/$mod") as $s)
      {
        if ($s[0] != "."
            && $s != "main.php"
            && $s[strlen($s) - 1] != "~"
        )
        {
          $s = skip_int_label(str_replace(".php", "", $s));
          $sym[$i]["typ"] = $type;
          $sym[$i]["mod"] = $mod;
          $sym[$i]["sym"] = $s;
          $i += 1;
        }
      }
    }
  }
  do
  {
    $sorted = true;
    for ($i = 0; isset($sym[$i + 1]); ++$i)
    {
      if (strlen($sym[$i]["sym"]) < strlen($sym[$i + 1]["sym"]))
      {
        $str = $sym[$i];
        $sym[$i] = $sym[$i + 1];
        $sym[$i + 1] = $str;
        $sorted = false;
      }
    }
  }
  while ($sorted == false);
  return ($sym);
}

