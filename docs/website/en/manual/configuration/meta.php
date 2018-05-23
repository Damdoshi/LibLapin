<?php
$functions = [
  10 => [
    "t_bunny_configuration_type",
    "t_bunny_configuration",
    "bunny_open_configuration",
    "bunny_delete_configuration",
    "bunny_configuration_get_name",
    "bunny_configuration_access",
    "bunny_configuration_get",
    "bunny_configuration_set",
    "bunny_configuration_go_get_node",
    "bunny_configuration_go_get",
    "bunny_configuration_go_set",
    "bunny_configuration_first",
    "bunny_configuration_next",
    "bunny_configuration_end",
    "bunny_configuration_is_last",
  ],
  20 => [
    "bunny_which_format",
    "bunny_new_configuration",
    "bunny_load_configuration",
    "bunny_save_configuration",
    "bunny_read_configuration",
    "bunny_write_configuration",
    "bunny_delete_node",
    "bunny_configuration_create_mode",
    "bunny_configuration_get_child",
    "bunny_configuration_get_nbr_child",
    "bunny_configuration_get_case",
    "bunny_configuration_get_nbr_case",
  ],
  30 => [
    "bunny_configuration_get_parent",
    "bunny_configuration_get_root",
    "bunny_configuration_get_address",
    "bunny_configuration_get_string",
    "bunny_configuration_get_double",
    "bunny_configuration_get_int",
    "bunny_configuration_set_string",
    "bunny_configuration_set_double",
    "bunny_configuration_set_int",
    "bunny_configuration_go_get_string",
    "bunny_configuration_go_get_double",
    "bunny_configuration_go_get_int",
    "bunny_configuration_go_set_string",
    "bunny_configuration_go_set_double",
    "bunny_configuration_go_set_int",
    "bunny_configuration_execute",
  ],
  40 => [
    "t_bunny_my_read_configuration",
    "gl_bunny_my_read_configuration",
    "t_bunny_my_write_configuration",
    "gl_bunny_my_write_configuration",
    "bunny_configuration_go_get_node_va",
    "bunny_configuration_go_get_va",
    "bunny_configuration_go_get_string_va",
    "bunny_configuration_go_get_double_va",
    "bunny_configuration_go_get_int_va",
    "bunny_configuration_go_set_va",
    "bunny_configuration_go_set_string_va",
    "bunny_configuration_go_set_double_va",
    "bunny_configuration_go_set_int_va",
    "bunny_configuration_push_path",
    "bunny_configuration_pop_path",
  ],
];
foreach ($functions as $f => $l)
{
  foreach ($l as $k)
  {
    $circle_level[$k] = $f;
  }
}

