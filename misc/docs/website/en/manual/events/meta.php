<?php
$functions = [
  00 => [
    "t_bunny_response",
    "t_bunny_event_state",
    "t_bunny_keysym",
    "t_bunny_key",
    "bunny_set_key_response",
    "t_bunny_mouse_button",
    "t_bunny_click",
    "bunny_set_click_response",
    "t_bunny_move",
    "bunny_set_move_response",
    "t_bunny_display",
    "bunny_set_display_function",
    "t_bunny_loop",
    "bunny_set_loop_main_function",
    "bunny_loop",
    "bunny_get_frequency",
  ],
  10 => [
    "bunny_get_keyboard",
    "bunny_get_mouse_button",
    "bunny_get_mouse_position",
  ],
  20 => [
    "t_bunny_type",
    "bunny_set_text_response",
    "t_bunny_wheel",
    "bunny_set_wheel_response",
    "t_bunny_joystick",
    "t_bunny_joy_connect",
    "bunny_set_joy_connect_response",
    "bunny_get_joy_info",
    "t_bunny_axis",
    "t_bunny_joy_axis",
    "bunny_set_joy_axis_response",
    "bunny_set_joy_axis_minimum_offset",
    "bunny_get_joy_axis",
    "t_bunny_joy_button",
    "bunny_set_joy_button_response",
    "bunny_get_joy_button",
    "t_bunny_get_focus",
    "bunny_set_get_focus_response",
    "t_bunny_lost_focus",
    "bunny_set_lost_focus_response",
    "t_bunny_resize",
    "bunny_set_resize_response",
    "t_bunny_close",
    "bunny_set_close_response",
    "bunny_get_window",
    "bunny_loop_mw",
  ],
  30 => [
    "bunny_set_entering_context_response",
    "t_bunny_leaving_context",
    "bunny_set_leaving_context_response",
    "t_bunny_context",
    "t_bunny_anonymous_context",
    "bunny_set_context",
    "bunny_get_context",
  ],
  40 => [
    "bunny_set_client_to_scheduler",
    "bunny_set_server_to_scheduler",
    "bunny_remove_network_from_scheduler",
    "t_bunny_message_response",
    "bunny_set_message_response",
    "t_bunny_connect_response",
    "bunny_set_connect_response",
  ],
  50 => [
    "t_bunny_async_computation_response",
    "bunny_set_async_computation_response",
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

  "t_bunny_response" => [0, $latest_version],
  "t_bunny_event_state" => [0, $latest_version],

  "t_bunny_keysym" => [2, $latest_version],
  "t_bunny_key" => [0, $latest_version],
  "bunny_set_key_response" => [0, $latest_version],
  "bunny_get_keyboard" => [2, $latest_version],

  "t_bunny_type" => [5, $latest_version],
  "bunny_set_text_response" => [5, $latest_version],

  "t_bunny_mouse_button" => [2, $latest_version],
  "t_bunny_click" => [0, $latest_version],
  "bunny_set_click_response" => [0, $latest_version],
  "bunny_get_mouse_button" => [2, $latest_version],

  "t_bunny_move" => [0, $latest_version],
  "bunny_set_move_response" => [0, $latest_version],
  "bunny_get_mouse_position" => [2, $latest_version],

  "t_bunny_wheel" => [5, $latest_version],
  "bunny_set_wheel_response" => [5, $latest_version],

  "t_bunny_joystick" => [5, $latest_version],
  "t_bunny_joy_connect" => [5, $latest_version],
  "bunny_set_joy_connect_response" => [5, $latest_version],
  "bunny_get_joy_info" => [5, $latest_version],
  "t_bunny_axis" => [5, $latest_version],
  "t_bunny_joy_axis" => [5, $latest_version],
  "bunny_set_joy_axis_response" => [5, $latest_version],
  "bunny_set_joy_axis_minimum_offset" => [12, $latest_version],
  "bunny_get_joy_axis" => [5, $latest_version],

  "t_bunny_joy_button" => [5, $latest_version],
  "bunny_set_joy_button_response" => [5, $latest_version],
  "bunny_get_joy_button" => [5, $latest_version],

  "t_bunny_get_focus" => [7, $latest_version],
  "bunny_set_get_focus_response" => [7, $latest_version],
  "t_bunny_lost_focus" => [7, $latest_version],
  "bunny_set_lost_focus_response" => [7, $latest_version],

  "t_bunny_resize" => [7, $latest_version],
  "bunny_set_resize_response" => [7, $latest_version],

  "t_bunny_close" => [7, $latest_version],
  "bunny_set_close_response" => [7, $latest_version],

  "bunny_get_window" => [6, $latest_version],

  "t_bunny_display" => [7, $latest_version],
  "bunny_set_display_function" => [7, $latest_version],

  "t_bunny_loop" => [0, $latest_version],
  "bunny_set_loop_main_function" => [0, $latest_version],
  "bunny_loop" => [0, $latest_version],
  "bunny_loop_mw" => [6, $latest_version],

  "bunny_set_client_to_scheduler" => [11, $latest_version],
  "bunny_set_server_to_scheduler" => [11, $latest_version],
  "bunny_remove_network_from_scheduler" => [11, $latest_version],
  "t_bunny_message_response" => [11, $latest_version],
  "bunny_set_message_response" => [11, $latest_version],
  "t_bunny_connect_response" => [11, $latest_version],
  "bunny_set_connect_response" => [11, $latest_version],
  "t_bunny_message_response" => [11, $latest_version],

  "bunny_set_entering_context_response" => [12, $latest_version],
  "t_bunny_leaving_context" => [12, $latest_version],
  "bunny_set_leaving_context_response" => [12, $latest_version],

  "t_bunny_async_computation_response" => [12, $latest_version],
  "bunny_set_async_computation_response" => [12, $latest_version],

  "t_bunny_context" => [5, $latest_version],
  "t_bunny_anonymous_context" => [5, $latest_version],
  "bunny_set_context" => [5, $latest_version],
  "bunny_get_context" => [5, $latest_version],

];

