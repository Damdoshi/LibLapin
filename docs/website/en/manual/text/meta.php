<?php
$functions = [
  20 => [
    "t_bunny_align",
    "t_bunny_font",
    "bunny_load_text",
    "bunny_load_font",
  ],
  30 => [
    "t_bunny_vector_font_line_coord",
    "t_bunny_letter",
    "t_bunny_letter_tab",
    "gl_vector_font"
  ],
];
foreach ($functions as $f => $l)
{
  foreach ($l as $k)
  {
    $circle_level[$k] = $f;
  }
}
