// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2016
//
// Lapin library

#include			"lapin_private.h"

t_bunny_my_cipher		gl_bunny_my_cipher = NULL;
t_bunny_my_cipher		gl_bunny_my_uncipher = NULL;
t_bunny_key_twist		gl_bunny_my_key_twist = NULL;

const char * const		gl_bunny_ciphering_table[BS_CUSTOM] =
  {
    "xor",
    "caesar",
    "shaker"
  };

