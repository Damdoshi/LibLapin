<?php
// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2018
//
// LibLapin

function manual_symbol_display_map($dir)
{
  // Generated meta files may refer to $latest_version for version ranges.  The
  // display map does not need the actual value, but defining it avoids noisy
  // warnings when this helper is called in isolation.
  $latest_version = -1;
  $doc_symbol_display = [];
  foreach (["meta.php", "meta.generated.php"] as $meta_file)
  {
    $path = "$dir/$meta_file";
    if (file_exists($path))
      require($path);
  }
  if (!isset($doc_symbol_display) || !is_array($doc_symbol_display))
    return ([]);
  return ($doc_symbol_display);
}

function sort_symbols_longest_first(&$sym)
{
  usort($sym, function($a, $b) {
    $as = isset($a["sym"]) ? $a["sym"] : "";
    $bs = isset($b["sym"]) ? $b["sym"] : "";
    $cmp = strlen($bs) <=> strlen($as);
    if ($cmp != 0)
      return ($cmp);
    return (strcmp($bs, $as));
  });
}

function get_all_symbols($root, $type, $base = null)
{
  if ($base)
    $sym = $base;
  else
    $sym = [];
  $i = count($sym);
  if (!is_dir($root))
    return ($sym);
  foreach (scandir("$root/") as $mod)
  {
    if ($mod[0] != "."
        && strstr($mod, ".php") == false
        && $mod[strlen($mod) - 1] != "~"
        && is_dir("$root/$mod")
    )
    {
      $display = manual_symbol_display_map("$root/$mod");
      foreach (scandir("$root/$mod") as $s)
      {
        if ($s[0] != "."
            && $s != "main.php"
            && $s != "meta.php"
            && $s != "meta.generated.php"
            && $s[strlen($s) - 1] != "~"
            && strstr($s, ".php") != false
        )
        {
          $label = skip_int_label(str_replace(".php", "", $s));
          $displayed = isset($display[$label]) ? $display[$label] : $label;

          // A generated C++ method must be linked by its fully qualified name.
          // Old/leftover short labels such as "T" or "Now" are too broad and
          // cause accidental links everywhere in prose and prototypes.
          if (strlen($displayed) <= 1)
            continue;

          $sym[$i]["typ"] = $type;
          $sym[$i]["mod"] = $mod;
          $sym[$i]["sym"] = $displayed;
          $sym[$i]["anchor"] = $label;
          $i += 1;
        }
      }
    }
  }
  sort_symbols_longest_first($sym);
  return ($sym);
}
