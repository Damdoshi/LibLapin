// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2015
//
// USB Device

#include		"UsbDevice.hpp"

bool			hbs::UsbDevice::GetBit(unsigned char		range,
					       unsigned char		pos) const
{
  return ((range >> pos) & 1);
}

void			hbs::UsbDevice::SetBit(unsigned char		&range,
					       unsigned char		pos,
					       bool			val) const
{
  if (val == false)
    range &= ~(1 << pos);
  else
    range |=  (1 << pos);
}
