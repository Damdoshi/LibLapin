// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2018
//
// Bibliotheque Lapin

#include		"PVM110N.hpp"
#include		"lapin_private.h"

struct			bunny_vm110n
{
  hbs::PVM110N		*board;
  int			id;
  bool			digital_inputs[5];
  double		analog_inputs[2];
  bool			digital_outputs[8];
  double		analog_outputs[2];
};

#define			PATTERN		"%p -> %s"

bool			bunny_vm110n_read(t_bunny_vm110n		*hdr)
{
  struct bunny_vm110n	*hard = (struct bunny_vm110n*)hdr;
  hbs::PVM110N		*ptr = (hbs::PVM110N*)hdr->_private;

  if (ptr->ReadInputs() == false)
    scream_error_if(return (false), EAGAIN, PATTERN, "vm110n", hdr, "false");
  hard->analog_inputs[0] = ptr->GetAnalog(hbs::PVM110N::ANAL_INPUT_0) / 255.0;
  hard->analog_inputs[1] = ptr->GetAnalog(hbs::PVM110N::ANAL_INPUT_1) / 255.0;
  hard->digital_inputs[0] = ptr->GetDigital(hbs::PVM110N::DIGI_INPUT_0);
  hard->digital_inputs[1] = ptr->GetDigital(hbs::PVM110N::DIGI_INPUT_1);
  hard->digital_inputs[2] = ptr->GetDigital(hbs::PVM110N::DIGI_INPUT_2);
  hard->digital_inputs[3] = ptr->GetDigital(hbs::PVM110N::DIGI_INPUT_3);
  hard->digital_inputs[4] = ptr->GetDigital(hbs::PVM110N::DIGI_INPUT_4);
  scream_log_if(PATTERN, "vm110n", hdr, "true");
  return (true);
}

