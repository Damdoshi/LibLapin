<?php
$functions = [
  30 => [
    "bunny_check_char",
    "bunny_check_text",
    "bunny_check_text_case",
    "bunny_read_char",
    "bunny_read_text",
    "bunny_skip_space",
    "bunny_inline_skip_space",
    "bunny_read_field",
    "bunny_read_double",
    "bunny_read_integer",
    "bunny_read_cstring",
    "bunny_read_rawstring",
    "bunny_write_cstring",
    "bunny_which_line",
  ]
];
foreach ($functions as $f => $l)
{
  foreach ($l as $k)
  {
    $circle_level[$k] = $f;
  }
}
