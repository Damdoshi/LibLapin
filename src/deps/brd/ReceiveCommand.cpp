// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2015
//
// IO Board Driver

#include		"PVM110N.hpp"

bool			hbs::PVM110N::ReceiveCommand(void)
{
  int			total;
  int			rten;
  int			i;

  /// 3 try
  total = 0;
  for (i = 0; i < 3; ++i)
    {
      if ((rten = usb_interrupt_read
	   (device_handle, USB_INP_EP, &data_in[total], sizeof(data_in) - total, 20)) < 0)
	return (false);
      if ((total += rten) == sizeof(data_in))
	return (data_in[BOARD_NUMBER] == dev_no || data_in[BOARD_NUMBER] == (dev_no + 10));
    }
  return (false);
}

