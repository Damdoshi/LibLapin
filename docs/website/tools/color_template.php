<?php

// symbols must start with wider symbols and end with shorter one.
function color_template($page, $doc, $symbols, $cnt)
{
  $cnt = str_replace('$S', '<span class="doc_symbol">', $cnt);
  $cnt = str_replace('$K', '<span class="doc_keyword">', $cnt);
  $cnt = str_replace('$T', '<span class="doc_type">', $cnt);
  $cnt = str_replace('$C', '<span class="doc_constant">', $cnt);
  $cnt = str_replace('$B', '<span class="doc_strong">', $cnt);
  $cnt = str_replace('$L', '<span class="doc_litteral">', $cnt);
  $cnt = str_replace('$A', '&nbsp;&nbsp;&nbsp&nbsp;', $cnt);
  $cnt = str_replace('@', '</span>', $cnt);
  foreach ($symbols as $cpl)
  {
    $cnt = str_replace(
      $cpl["sym"],
      urlforge($page, $doc, $cpl["mod"], $cpl["sym"]),
      $cnt
    );
  }
  return ($cnt);
}

