// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2016
//
// Bibliotheque Lapin

#include		"PVM110N.hpp"
#include		"lapin.h"

bool			bunny_hardware_write(const t_bunny_hardware	*hdr)
{
  hbs::PVM110N		*hard = (hbs::PVM110N*)hdr->_private;

  if (hdr->analog_outputs[0] < 0 || hdr->analog_outputs[0] > 1)
    return (false);
  if (hdr->analog_outputs[1] < 0 || hdr->analog_outputs[1] > 1)
    return (false);
  hard->SetAnalog(hbs::PVM110N::ANAL_OUTPUT_0, hdr->analog_outputs[0] * 255.0);
  hard->SetAnalog(hbs::PVM110N::ANAL_OUTPUT_1, hdr->analog_outputs[1] * 255.0);
  hard->SetDigital(hbs::PVM110N::DIGI_OUTPUT_0, hdr->digital_outputs[0]);
  hard->SetDigital(hbs::PVM110N::DIGI_OUTPUT_1, hdr->digital_outputs[1]);
  hard->SetDigital(hbs::PVM110N::DIGI_OUTPUT_2, hdr->digital_outputs[2]);
  hard->SetDigital(hbs::PVM110N::DIGI_OUTPUT_3, hdr->digital_outputs[3]);
  hard->SetDigital(hbs::PVM110N::DIGI_OUTPUT_4, hdr->digital_outputs[4]);
  hard->SetDigital(hbs::PVM110N::DIGI_OUTPUT_5, hdr->digital_outputs[5]);
  hard->SetDigital(hbs::PVM110N::DIGI_OUTPUT_6, hdr->digital_outputs[6]);
  hard->SetDigital(hbs::PVM110N::DIGI_OUTPUT_7, hdr->digital_outputs[7]);
  return (hard->WriteOutputs());
}

