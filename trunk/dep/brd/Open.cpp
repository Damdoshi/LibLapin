// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2015
//
// IO Board Driver

#include		"PVM110N.hpp"

bool			hbs::PVM110N::Open(CardId	id)
{
  struct usb_device	*dev;
  struct usb_bus	*bus;
  int			board_addr;

  board_addr = id + VM110N_IPID;
  for (bus = usb_busses; bus != NULL; bus = bus->next)
    for (dev = bus->devices; dev != NULL; dev = dev->next)
      if (dev->descriptor.idVendor == VELLEMAN_VENDOR_ID
	  && dev->descriptor.idProduct == board_addr)
	{
	  if ((device_handle = usb_open(dev)) == NULL)
	    return (false);
	  dev_no = id + 1;

	  if (TakeOverDevice(device_handle, 0) == false
	      || SendReset() == false
	      || ReceiveCommand() == false)
	    {
	      usb_close(device_handle);
	      device_handle = NULL;
	      return (false);
	    }
	  return (true);
	}
  return (false);
}
