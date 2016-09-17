// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2016
//
// Bibliotheque Lapin

#include		"PVM110N.hpp"
#include		"lapin.h"

struct			bunny_hardware
{
  hbs::PVM110N		*board;
  int			id;
  bool			digital_inputs[5];
  double		analog_inputs[2];
  bool			digital_outputs[8];
  double		analog_outputs[2];
};

bool			bunny_hardware_read(t_bunny_hardware		*hdr)
{
  struct bunny_hardware	*hard = (struct bunny_hardware*)hdr;
  hbs::PVM110N		*ptr = (hbs::PVM110N*)hdr->_private;

  if (ptr->ReadInputs() == false)
    return (false);
  hard->analog_inputs[0] = ptr->GetAnalog(hbs::PVM110N::ANAL_INPUT_0);
  hard->analog_inputs[1] = ptr->GetAnalog(hbs::PVM110N::ANAL_INPUT_1);
  hard->digital_inputs[0] = ptr->GetDigital(hbs::PVM110N::DIGI_INPUT_0);
  hard->digital_inputs[1] = ptr->GetDigital(hbs::PVM110N::DIGI_INPUT_1);
  hard->digital_inputs[2] = ptr->GetDigital(hbs::PVM110N::DIGI_INPUT_2);
  hard->digital_inputs[3] = ptr->GetDigital(hbs::PVM110N::DIGI_INPUT_3);
  hard->digital_inputs[4] = ptr->GetDigital(hbs::PVM110N::DIGI_INPUT_4);
  return (true);
}

