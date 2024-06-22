/*
** Jason Brillante "Damdoshi"
** Hanged Bunny Studio 2014-2023
**
**
** Bibliotheque Lapin
*/

#ifndef			__LAPIN_PRIVATE_HARDWARE_HPP__
# define		__LAPIN_PRIVATE_HARDWARE_HPP__

bool			_bunny_max7219_start_word(t_bunny_max7219	*m);
bool			_bunny_max7219_end_word(t_bunny_max7219		*m);
bool			_bunny_max7219_write_data(t_bunny_max7219	*m,
						  uint8_t		data);
bool			_bunny_max7219_send_word(t_bunny_max7219	*m,
						 t_bunny_max7219_command cmd,
						 uint8_t		data);

#endif	//		__LAPIN_PRIVATE_HARDWARE_HPP__
