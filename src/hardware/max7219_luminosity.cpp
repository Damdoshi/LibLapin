// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2022
//
// Bibliotheque Lapin

#include		"lapin_private.h"


/**
 * @doc
 * @doc-symbol bunny_max7219_luminosity
 * @doc-kind function
 * @doc-module hardware
 * @doc-order 480
 * @doc-since 0
 * @doc-until latest
 * @doc-level 50
 *
 * @doc-lang en
 * @brief Generates the MAX7219 luminosity bitstream.
 * @param m MAX7219 descriptor.
 * @return-success Returns true when the stream was generated.
 * @see t_bunny_max7219
 *
 * @doc-lang fr
 * @brief Génère le bitstream de luminosité MAX7219.
 * @param m Descripteur MAX7219.
 * @return-success Renvoie true lorsque le flux a été généré.
 * @see t_bunny_max7219
 */
bool			bunny_max7219_luminosity(t_bunny_max7219		*m)
{
  _bunny_max7219_start_word(m);
  for (size_t i = 0; i < m->width * m->height; ++i)
    {
      _bunny_max7219_write_data(m, BMC_SET_INTENSITY);
      _bunny_max7219_write_data(m, m->luminosity[i]);
    }
  _bunny_max7219_end_word(m);
  return (true);
}
