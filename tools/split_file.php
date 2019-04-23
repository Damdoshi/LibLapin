<?php
// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2019
//
// LibLapin

require_once ("bassert.php");

function whichline($content, $idx)
{
  $cnt = 1;
  while ($idx >= 0)
  {
    if ($content[$idx] == '\n')
      $cnt += 1;
    $idx -= 1;
  }
  return ($cnt);
}

function split_file($file)
{
  BAssert(($content = file_get_contents($file)), "cannot read $file.");
  $last_pos = 0;
  $doclist = [];
  while (($last_pos = strpos($content, "/*?", $last_pos)) !== false)
  {
    $start = $last_pos;
    while ($content[$start] != '{')
      $start += 1;
    $get_code_line = ($end_pos = strpos($content, "*/", $start)) + 2;
    while ($content[$end_pos] != '}')
      $end_pos -= 1;
    $json_str = substr($content, $start, $end_pos - $start + 1);
    BAssert($json = json_decode($json_str, true), "Invalid json retrieved from $file:".whichline($content, $start).":\n$json_str\n");
    BAssert($json["name"], "a name field was required near $file:".whichline($content, $start));
    BAssert($json["order"], "an order field was required near $file:".whichline($content, $start));
    BAssert(!isset($doclist[$json["order"]]),
            "order ".$json["order"]." requested by ".$json["name"]." is already taken by ".
            (isset($doclist[$json["order"]]["name"]) ? $doclist[$json["order"]]["name"] : "").
            " in $file:".whichline($content, $start));

    while (ctype_space($content[$get_code_line]))
      $get_code_line += 1;
    $end_of_dec = $get_code_line;
    // Type
    if (strncmp(substr($content, $get_code_line), "typedef", 7) == 0)
    {
      for ($inspector = $get_code_line + 7; ctype_space($content[$inspector]); ++$inspector);
      if (strncmp(substr($content, $inspector), "struct", 6) == 0)
        $json["type"] = "struct";
      else if (strncmp(substr($content, $inspector), "enum", 4) == 0)
        $json["type"] = "enum";
      else if (strncmp(substr($content, $inspector), "union", 5) == 0)
        $json["type"] = "union";
      else
        $json["type"] = "alias";
      $cnt = 0;
      for (;$content[$inspector] != ';' && $cnt != 0; ++$inspector)
        if ($content[$inspector] == '{')
          $cnt += 1;
        else if ($content[$inspector] == '}')
          $cnt -= 1;
      $end_of_dec = $inspector;
    }
    // Macro
    else if (strncmp(substr($content, $get_code_line), "#define", 7) == 0)
    {
      $get_code_line += 7;
      for ($inspector = $get_code_line; ctype_space($content[$inspector]); ++$inspector);
      for ($end_of_dec = $inspector; $content[$end_of_dec] != '(' && !ctype_space($content[$end_of_dec]); ++$end_of_dec);
      if ($content[$end_of_dec] == '(')
      {
        $json["type"] = "macro";
        for (; $content[$end_of_dec] != ')'; ++$end_of_dec);
        ++$end_of_dec;
      }
      else
        $json["type"] = "macro_constant";
    }
    else
    {
      for ($inspector = $get_code_line; $content[$inspector] != '(' && $content[$inspector] != '=' && $content[$inspector] != ';'; ++$inspector);
      // Fonction
      if ($content[$inspector] == '(')
      {
        $json["type"] = "function";
        for (; $content[$inspector] != ';' && $content[$inspector] != '{'; ++$inspector);
        $end_of_dec = $inspector;
      }
      // Globale
      else
      {
        $end_of_dec = $inspector;
        $json["type"] = "global";
        for (; $content[$inspector] != ';' && $content[$inspector] != '{'; ++$inspector);
        if ($content[$inspector] == ';')
          $end_of_dec = $inspector;
      }
    }

    $json["declaration"] = substr($content, $get_code_line, $end_of_dec - $get_code_line);
    $doclist[$json["order"]] = $json;
    $last_pos = $end_of_dec;
  }
  return ($doclist);
}

