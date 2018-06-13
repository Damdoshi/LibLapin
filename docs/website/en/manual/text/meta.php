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

$version_that_support = [
  "t_bunny_align" => [11, $latest_version],
  "t_bunny_font" => [11, $latest_version],
  "bunny_load_text" => [12, $latest_version],
  "bunny_load_font" => [11, $latest_version],

  "t_bunny_vector_font_line_coord" => [5, $latest_version],
  "t_bunny_letter" => [5, $latest_version],
  "t_bunny_letter_tab" => [5, $latest_version],
  "gl_vector_font" => [5, $latest_version],
];

