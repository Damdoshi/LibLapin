// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2015
//
// IO Board Driver


#include		"PVM110N.hpp"

bool			hbs::PVM110N::SendCommand(void) const
{
  int			total;
  int			wten;
  int			i;

  /// 3 try
  total = 0;
  for (i = 0; i < 3; ++i)
    {
      if ((wten = usb_interrupt_write
	   (device_handle, USB_OUT_EP, &data_out[total], sizeof(data_out) - total, 20)) < 0)
	return (false);
      if ((total += wten) == sizeof(data_out))
	return (true);
    }
  return (false);
}
