// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2015
//
// IO Board Driver

#include		"PVM110N.hpp"

void			hbs::PVM110N::Close(void)
{
  if (device_handle == NULL)
    return ;
  usb_close(device_handle);
  device_handle = NULL;
  dev_no = 0;
}
