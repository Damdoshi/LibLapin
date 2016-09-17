// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2015
//
// IO Board Driver

#include		"PVM110N.hpp"

const int		hbs::PVM110N::VM110N_IPID = 0x5500;
const int		hbs::PVM110N::VELLEMAN_VENDOR_ID = 0x10CF;

hbs::PVM110N::PVM110N(void)
  : UsbDevice(),
    device_handle(NULL),
    dev_no(0)
{}

hbs::PVM110N::~PVM110N(void)
{
  Close();
}
