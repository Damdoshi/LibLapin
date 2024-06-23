<?php
$functions = [
  20 => [
    "t_bunny_shader",
    "bunny_is_shader_available",
    "bunny_blit_shader",
    "t_bunny_color_blind_tweak",
    "bunny_noise_color",
    "t_bunny_noise_type",
    "t_bunny_screen_tweak",
    "bunny_screen_tweak_shader",
    "bunny_default_screen_tweak",
  ],
  30 => [
    "t_bunny_normal_light",
    "t_bunny_normal_map",
    "bunny_normal_map_shader",
    "t_bunny_spreading",
    "bunny_spreading_shader",
    "bunny_blit_spreading",
    "bunny_fill_spreading",
    "bunny_flip_spreading",
    "bunny_draw_spreading_source",
    "bunny_clear_spreading",
    "bunny_delete_spreading",
  ],
  40 => [
    "t_bunny_variable_type",
    "t_bunny_transform",
    "bunny_new_shader",
    "bunny_load_shader",
    "bunny_read_shader",
    "bunny_shader_set_variable",
    "bunny_delete_shader",
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
  "t_bunny_shader" => [6, $latest_version],
  "bunny_is_shader_available" => [6, $latest_version],
  "bunny_blit_shader" => [6, $latest_version],

  "t_bunny_color_blind_tweak" => [12, $latest_version],
  "bunny_noise_color" => [12, $latest_version],
  "t_bunny_noise_type" => [12, $latest_version],
  "t_bunny_screen_tweak" => [12, $latest_version],
  "bunny_screen_tweak_shader" => [12, $latest_version],
  "bunny_default_screen_tweak" => [12, $latest_version],

  "t_bunny_normal_light" => [12, $latest_version],
  "t_bunny_normal_map" => [12, $latest_version],
  "bunny_normal_map_shader" => [12, $latest_version],
  "t_bunny_spreading" => [12, $latest_version],
  "bunny_spreading_shader" => [12, $latest_version],
  "bunny_blit_spreading" => [12, $latest_version],
  "bunny_fill_spreading" => [12, $latest_version],
  "bunny_flip_spreading" => [12, $latest_version],
  "bunny_draw_spreading_source" => [12, $latest_version],
  "bunny_clear_spreading" => [12, $latest_version],
  "bunny_delete_spreading" => [12, $latest_version],

  "t_bunny_variable_type" => [6, $latest_version],
  "t_bunny_transform" => [6, $latest_version],
  "bunny_new_shader" => [6, $latest_version],
  "bunny_load_shader" => [6, $latest_version],
  "bunny_read_shader" => [6, $latest_version],
  "bunny_shader_set_variable" => [6, $latest_version],
  "bunny_delete_shader" => [6, $latest_version],
];
