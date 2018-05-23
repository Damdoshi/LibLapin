<?php
$functions = [
  20 => [
    "t_bunny_ciphering",
    "gl_bunny_ciphering_table",
    "t_bunny_cipher_key",
    "bunny_get_ciphering",
    "bunny_new_key",
    "bunny_delete_key",
    "bunny_cipher_file",
    "bunny_uncipher_file",
    "bunny_cipher_data",
    "bunny_uncipher_data",
  ],
  40 => [
    "bunny_default_key",
    "bunny_fill_default_key",
    "t_bunny_key_twist",
    "gl_bunny_my_key_twist",
    "t_bunny_my_cipher",
    "gl_bunny_my_cipher",
    "t_bunny_my_uncipher",
    "gl_bunny_my_uncipher",
    "t_bunny_ressource_cipher",
    "gl_bunny_ressource_ciphering",
    "gl_bunny_ressource_data",
  ]
];
foreach ($functions as $f => $l)
{
  foreach ($l as $k)
  {
    $circle_level[$k] = $f;
  }
}
