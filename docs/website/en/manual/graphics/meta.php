<?php
$functions = [
  00 => [
    "t_bunny_clipable",
    "t_bunny_pixelarray",
    "bunny_new_pixelarray",
    "bunny_load_pixelarray",
    "t_bunny_picture",
    "bunny_new_picture",
    "bunny_load_picture",
    "bunny_delete_clipable",
    "bunny_blit",
    "bunny_set_pixel",
    "bunny_set_circle",
    "bunny_set_disk",
    "bunny_set_line",
    "bunny_set_polygon",
    "bunny_fill",
    "bunny_clear",
  ],
  10 => [
    "bunny_save_pixelarray",
    "t_bunny_my_load_pixelarray",
    "t_bunny_my_read_pixelarray",
    "gl_bunny_my_load_pixelarray",
    "gl_bunny_my_read_pixelarray",
    "bunny_read_picture",
    "bunny_read_pixelarray",
    "t_bunny_my_blit",
    "gl_bunny_my_blit",
    "t_bunny_my_set_pixel",
    "t_bunny_my_set_disk",
    "t_bunny_my_set_line",
    "t_bunny_my_set_polygon",
    "gl_bunny_my_set_pixel",
    "gl_bunny_my_set_disk",
    "gl_bunny_my_set_line",
    "gl_bunny_my_set_polygon",
    "t_bunny_my_fill",
    "t_bunny_my_clear",
    "gl_bunny_my_fill",
    "gl_bunny_my_clear",
    "bunny_draw",
  ],
  20 => [
    "bunny_read_picture_id",
    "bunny_read_pixelarray_id",
    "bunny_clipable_copy",
  ],
  30 => [
    "t_bunny_geometry",
    "t_bunny_vertex",
    "t_bunny_vertex_array",
    "bunny_set_geometry",
    "t_bunny_my_geometry",
    "gl_bunny_my_geometry",
  ],
  40 => [
    "bunny_enable_full_blit",
    "bunny_GL_reset_states",
    "bunny_GL_push_states",
    "bunny_GL_pop_states",
  ],
  50 => [
    "bunny_make_clipable_unique",
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
  "t_bunny_clipable" => [0, $latest_version],
  "bunny_clipable_copy" => [13, $latest_version],
  "t_bunny_pixelarray" => [0, $latest_version],
  "bunny_new_pixelarray" => [0, $latest_version],

  "bunny_load_pixelarray" => [5, $latest_version],
  "bunny_read_pixelarray_id" => [12, $latest_version],
  "bunny_read_pixelarray" => [5, $latest_version],
  "t_bunny_my_load_pixelarray" => [5, $latest_version],
  "t_bunny_my_read_pixelarray" => [5, $latest_version],
  "gl_bunny_my_load_pixelarray" => [5, $latest_version],
  "gl_bunny_my_read_pixelarray" => [5, $latest_version],

  "bunny_save_pixelarray" => [5, $latest_version],

  "t_bunny_picture" => [0, $latest_version],
  "bunny_new_picture" => [0, $latest_version],
  "bunny_load_picture" => [5, $latest_version],
  "bunny_read_picture_id" => [12, $latest_version],
  "bunny_read_picture" => [5, $latest_version],
  "bunny_delete_clipable" => [0, $latest_version],

  "bunny_blit" => [0, $latest_version],
  "t_bunny_my_blit" => [1, $latest_version],
  "bunny_draw" => [0, $latest_version],

  "bunny_set_pixel" => [0, $latest_version],
  "t_bunny_my_set_pixel" => [1, $latest_version],
  "gl_bunny_my_set_pixel" => [1, $latest_version],

  "bunny_set_line" => [0, $latest_version],
  "t_bunny_my_set_line" => [1, $latest_version],
  "gl_bunny_my_set_line" => [1, $latest_version],

  "bunny_set_polygon" => [0, $latest_version],
  "t_bunny_my_set_polygon" => [1, $latest_version],
  "gl_bunny_my_set_polygon" => [1, $latest_version],

  "bunny_set_circle" => [8, $latest_version],
  "t_bunny_my_set_circle" => [8, 10],
  "gl_bunny_my_set_circle" => [8, 10],

  "bunny_set_disk" => [11, $latest_version],
  "t_bunny_my_set_disk" => [11, $latest_version],
  "gl_bunny_my_set_disk" => [11, $latest_version],

  "bunny_fill" => [0, $latest_version],
  "t_bunny_my_fill" => [1, $latest_version],
  "gl_bunny_my_fill" => [1, $latest_version],

  "bunny_clear" => [0, $latest_version],
  "t_bunny_my_clear" => [1, $latest_version],
  "gl_bunny_my_clear" => [1, $latest_version],

  "t_bunny_geometry" => [7, $latest_version],
  "t_bunny_vertex" => [7, $latest_version],
  "t_bunny_vertex_array" => [7, $latest_version],
  "bunny_set_geometry" => [7, $latest_version],
  "t_bunny_my_geometry" => [7, $latest_version],
  "gl_bunny_my_geometry" => [7, $latest_version],

  "bunny_enable_full_blit" => [9, $latest_version],
  "bunny_GL_reset_states" => [11, $latest_version],
  "bunny_GL_push_states" => [11, $latest_version],
  "bunny_GL_pop_states" => [11, $latest_version],

  "bunny_make_clipable_unique" => [12, $latest_version],
];
