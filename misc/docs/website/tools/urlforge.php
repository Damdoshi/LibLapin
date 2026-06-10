<?php

function urlforge($page, $doc, $mod, $anchor, $text = null)
{
  if ($text === null)
    $text = $anchor;
  $chars = preg_split('//u', $text, -1, PREG_SPLIT_NO_EMPTY);
  if ($chars === false)
    $chars = str_split($text);
  $chars = array_map(function($ch) {
    return htmlspecialchars($ch, ENT_NOQUOTES | ENT_SUBSTITUTE, 'UTF-8');
  }, $chars);
  $label = implode("&zwnj;", $chars);
  // Base64 to prevent the color_template str_replace to match...
  return (
    "<a class=\"doclink\"".
    "href=\"index.php?pag=$page&amp;doc=$doc&amp;mod=$mod#".
    base64_encode($anchor)."\">".
    $label.
    "</a>"
  );
}
