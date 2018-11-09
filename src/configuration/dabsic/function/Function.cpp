// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2018
//
// Lapin library

#include		"lapin_private.h"

Function::~Function()
{
  if (prototype)
    bunny_free((void*)prototype);
}

