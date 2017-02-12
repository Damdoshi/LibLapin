// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2015
//
// IO Board Driver

#include		"PVM110N.hpp"

bool			hbs::PVM110N::TakeOverDevice(usb_dev_handle	*dev,
						     int		interface)
{
  /// If it fails, it still works, it only means that it was already ok
  (void)usb_detach_kernel_driver_np(dev, interface);
  (void)usb_claim_interface(dev, interface);
  (void)usb_set_altinterface(dev, interface);
  (void)usb_set_configuration(dev, 1);
  return (true);
}

