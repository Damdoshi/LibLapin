<?php
// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2019
//
// LibLapin

function urlforge($page, $doc, $mod, $anchor)
{
  $label = str_split($anchor);
  $label = implode("&zwnj;", $label);
  // Base64 to prevent the color_template str_replace to match...
  return (
    "<a class=\"doclink\"".
    "href=\"index.php?pag=$page&amp;doc=$doc&amp;mod=$mod#".
    base64_encode($anchor)."\">".
    $label.
    "</a>"
  );
}

