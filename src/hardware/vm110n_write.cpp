// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2018
//
// Bibliotheque Lapin

#include		"PVM110N.hpp"
/*
** For MinGW
*/
#undef			TRANSPARENT
#include		"lapin_private.h"

#define			PATTERN		"%p -> %s"


/**
 * @doc
 * @doc-symbol bunny_vm110n_write
 * @doc-kind function
 * @doc-module hardware
 * @doc-order 180
 * @doc-since 0
 * @doc-until latest
 * @doc-level 40
 *
 * @doc-lang en
 * @brief Writes the output state of a VM110N board.
 * @param hdr Handler containing output values to write.
 * @return-success Returns true when outputs were written.
 * @return-failure Returns false on invalid values or hardware error.
 * @log "vm110n"
 * @see t_bunny_vm110n
 *
 * @doc-lang fr
 * @brief Écrit l’état des sorties d’une carte VM110N.
 * @param hdr Gestionnaire contenant les valeurs de sortie à écrire.
 * @return-success Renvoie true lorsque les sorties ont été écrites.
 * @return-failure Renvoie false en cas de valeurs invalides ou d’erreur matérielle.
 * @log "vm110n"
 * @see t_bunny_vm110n
 */
bool			bunny_vm110n_write(const t_bunny_vm110n	*hdr)
{
  hbs::PVM110N		*hard = (hbs::PVM110N*)hdr->_private;

  if (hdr->analog_outputs[0] < 0 || hdr->analog_outputs[0] > 1)
    scream_error_if(return (false), EINVAL,
		    PATTERN " (Invalid analog_outputs[0] value)",
		    "vm110n",
		    hdr, "false");
  if (hdr->analog_outputs[1] < 0 || hdr->analog_outputs[1] > 1)
    scream_error_if(return (false), EINVAL,
		    PATTERN " (Invalid analog_outputs[1] value)",
		    "vm110n",
		    hdr, "false");
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
  if (hard->WriteOutputs() == false)
    scream_error_if(return (false), EWOULDBLOCK, PATTERN, "vm110n", hdr, "false");
  scream_log_if(PATTERN, "vm110n", hdr, "true");
  return (true);
}

