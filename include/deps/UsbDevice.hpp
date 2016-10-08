// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2015
//
// HBSL - Misc - Usb Device

#ifndef				__HBS_MISC_USBDEVICE_HPP__
# define			__HBS_MISC_USBDEVICE_HPP__
# include			<usb.h>

namespace			hbs
{
  //! Open USB busses and provide some bit manipulation functions
  class				UsbDevice
  {
  protected:
    static struct usb_bus	*usb_busses;

    //! Return the state of the bit pos in range.
    /*!
    ** Return the state of the bit pos in range.
    ** \param range The original value.
    ** \param pos The bit you wish to get
    ** \return (range >> pos) & 1
    */
    bool			GetBit(unsigned char			range,
				       unsigned char			pos) const;
    //! Set the bit pos in range to the value val
    /*!
    ** Set the value val to the bit pos in range.
    ** \param range The bit collection to edit
    ** \param pos The bit you wish to set
    ** \param val The value you wish to assign to the bit
    */
    void			SetBit(unsigned char			&range,
				       unsigned char			pos,
				       bool				val) const;

    //! Build the UsbDevice. Open USB busses is not opened yet.
    UsbDevice(void);
    //! Destroy the UsbDevice. Does not close USB busses.
    ~UsbDevice(void);
  };
}

#endif	//			__HBS_MISC_USBDEVICE_HPP__
