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
