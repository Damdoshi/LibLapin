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

$version_that_support = [
  // 0
  "t_bunny_rgb" => [0, $latest_version],
  "t_bunny_color" => [0, $latest_version],
  "TRANSPARENT" => [0, $latest_version],
  "BLACK" => [0, $latest_version],
  "RED" => [0, $latest_version],
  "GREEN" => [0, $latest_version],
  "BLUE" => [0, $latest_version],
  "PURPLE" => [0, $latest_version],
  "TEAL" => [0, $latest_version],
  "YELLOW" => [0, $latest_version],
  "WHITE" => [0, $latest_version],
  "PINK" => [0, $latest_version],
  "PINK2" => [6, $latest_version],
  "TO_ALPHA" => [0, $latest_version],
  "TO_RED" => [0, $latest_version],
  "TO_GREEN" => [0, $latest_version],
  "TO_BLUE" => [0, $latest_version],
  "GET_COLOR" => [0, $latest_version],
  "ALPHA" => [0, $latest_version],
  "COLOR" => [0, $latest_version],

  "ALPHA_GRAY" => [12, $latest_version],
  "GRAY" => [12, $latest_version],

  "ALPHA_GREY" => [2, 11],
  "GREY" => [2, 11],
];
