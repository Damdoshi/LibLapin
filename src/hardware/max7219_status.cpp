// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2022
//
// Bibliotheque Lapin

#include		"lapin_private.h"

bool			_bunny_max7219_start_word(t_bunny_max7219	*m)
{
  bunny_push_bitstream(m->clock_pin, 1, 0);
  bunny_push_bitstream(m->load_pin, 1, 0);
  bunny_push_bitstream(m->data_pin, 1, 0);
  m->stream_progression += 1;
  return (true);
}

bool			_bunny_max7219_end_word(t_bunny_max7219		*m)
{
  bunny_push_bitstream(m->clock_pin, 1, 0);
  bunny_push_bitstream(m->load_pin, 1, 1);
  bunny_push_bitstream(m->data_pin, 1, 0);
  m->stream_progression += 1;
  return (true);
}

bool			_bunny_max7219_write_data(t_bunny_max7219	*m,
						  uint8_t		data)
{
  for (int i = 0; i < 8; ++i)
    {
      bunny_push_bitstream(m->clock_pin, 1, 0);
      bunny_push_bitstream(m->data_pin, 1, data & 0x80);
      bunny_push_bitstream(m->load_pin, 1, bunny_top_bitstream(m->load_pin));
      m->stream_progression += 1;

      bunny_push_bitstream(m->clock_pin, 1, 1);
      bunny_push_bitstream(m->data_pin, 1, data & 0x80);
      bunny_push_bitstream(m->load_pin, 1, bunny_top_bitstream(m->load_pin));
      m->stream_progression += 1;
      data <<= 1;
    }
  return (true);
}

bool			_bunny_max7219_send_word(t_bunny_max7219	*m,
						 t_bunny_max7219_command cmd,
						 uint8_t		data)
{
  _bunny_max7219_start_word(m);
  for (size_t i = 0; i < m->width * m->height; ++i)
    {
      _bunny_max7219_write_data(m, cmd);
      _bunny_max7219_write_data(m, data);
    }
  _bunny_max7219_end_word(m);
  return (true);
}

bool			bunny_max7219_status(t_bunny_max7219		*m)
{
  _bunny_max7219_send_word(m, BMC_SET_DECODE_MODE, 0);
  _bunny_max7219_send_word(m, BMC_SET_SCANLIMIT, 7);
  _bunny_max7219_send_word(m, BMC_SHUTDOWN, 1);
  _bunny_max7219_send_word(m, BMC_DISPLAY_TEST, 0);
  return (true);
}

