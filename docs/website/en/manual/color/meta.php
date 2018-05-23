<?php
$functions = [
  00 => [
    "TRANSPARENT",
    "BLACK",
    "RED",
    "GREEN",
    "BLUE",
    "PURPLE",
    "TEAL",
    "YELLOW",
    "WHITE",
    "PINK",
    "PINK2"
  ],
  10 => [
    "TO_ALPHA",
    "TO_RED",
    "TO_GREEN",
    "TO_BLUE",
    "GET_COLOR",
    "ALPHA",
    "COLOR",
    "ALPHA_GRAY",
    "GRAY",
  ],
  20 => [
    "t_bunny_rgb",
    "t_bunny_color",
  ]
];
foreach ($functions as $f => $l)
{
  foreach ($l as $k)
  {
    $circle_level[$k] = $f;
  }
}
