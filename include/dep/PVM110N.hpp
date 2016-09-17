// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2015
//
// HBSL - Misc - PVCM110N Driver

#ifndef				__HBS_MISC_PVM110N_DRIVER_HPP__
# define			__HBS_MISC_PVM110N_DRIVER_HPP__
# include			"UsbDevice.hpp"

namespace			hbs
{
  class				PVM110N : protected hbs::UsbDevice
  {
  public:
    //! ID of the Velleman card. (Jumper on the board)
    enum			CardId
      {
	ID_0,
	ID_1,
	ID_2,
	ID_3
      };
    //! ID of analog inputs.
    enum			AnalogInput
      {
	ANAL_INPUT_0,
	ANAL_INPUT_1
      };
    //! ID of digital inputs.
    enum			DigitalInput
      {
	DIGI_INPUT_0,
	DIGI_INPUT_1,
	DIGI_INPUT_2,
	DIGI_INPUT_3,
	DIGI_INPUT_4
      };
    //! ID of the analog outputs.
    enum			AnalogOutput
      {
	ANAL_OUTPUT_0,
	ANAL_OUTPUT_1
      };
    //! ID of the digital outputs.
    enum			DigitalOutput
      {
	DIGI_OUTPUT_0,
	DIGI_OUTPUT_1,
	DIGI_OUTPUT_2,
	DIGI_OUTPUT_3,
	DIGI_OUTPUT_4,
	DIGI_OUTPUT_5,
	DIGI_OUTPUT_6,
	DIGI_OUTPUT_7
      };

  private:
    static const int		VM110N_IPID;
    static const int		VELLEMAN_VENDOR_ID;
    enum			Command
      {
	CMD_RESET		= 0x00,				// No parameters
	CMD_SET_DEBOUNCE_1	= 0x01,				// With DEBOUNCE_1 as parameter
	CMD_SET_DEBOUNCE_2	= 0x02,				// With DEBOUNCE_2 as parameter
	CMD_RESET_COUNTER_1	= 0x03,				// With RESET_COUNTER_1=0 as parameter
	CMD_RESET_COUNTER_2	= 0x04,				// With RESET_COUNTER_2=0 as parameter
	CMD_SET_ANALOG_DIGITAL	= 0x05				// With DIGI and ANAL as parameter
      };
    enum			UsbCommand
      {
	USB_OUT_EP		= 0x01,
	USB_INP_EP		= 0x81
      };
    enum			InputByte
      {
	DIGI_INPUT		= 0x00,
	BOARD_NUMBER		= 0x01,
	ANAL_1_INPUT		= 0x02,
	ANAL_2_INPUT		= 0x03,
	COUNTER_1		= 0x04,				// 16 bits
	COUNTER_2		= 0x06,				// 16 bits
      };
    enum			OutputByte
      {
	COMMAND			= 0x00,
	DIGI_OUTPUT_OFFSET	= 0x01,
	ANAL_OUTPUT_1_OFFSET	= 0x02,
	ANAL_OUTPUT_2_OFFSET	= 0x03,
	RESET_COUNTER_1		= 0x04,
	RESET_COUNTER_2		= 0x05,
	DEBOUNCE_1		= 0x06,
	DEBOUNCE_2		= 0x07
      };

    char			data_in[8];
    mutable char		data_out[8];
    struct usb_dev_handle	*device_handle;
    int				dev_no;

    /// Subfunctions
    bool			TakeOverDevice(usb_dev_handle	*dev,
					       int		interface /* ? */);
    bool			SendCommand(void) const;
    bool			ReceiveCommand(void);
    bool			SendReset(void) const;

    void			InBitEdit_FromSystemToUser(void);

  public:
    //! Open the velleman board that match the given ID
    /*!
    ** Open the velleman board that match the given ID.
    ** \param id The ID of the board you wish to connect with.
    ** \return True if everything went well.
    */
    bool			Open(CardId			id = ID_0);
    //! Close the velleman board that was opened.
    void			Close(void);

    //! Retrieve information from the board to the PVM110N class.
    /*!
    ** Retrieve informations from the board to the PVM110N class.
    ** You have to call ReadInputs before any Get* function.
    ** Every call to ReadInputs updates the recorded status.
    ** \return True if everything went well.
    */
    bool			ReadInputs(void);

    //! Get the value of an analog input retrieved inside the class.
    /*!
    ** Get the value of an analog input retrieved inside the class.
    ** \param id The id of the input you wish to get.
    ** \return The analog value, from 0 to 255. (0V-5V)
    */
    unsigned char		GetAnalog(AnalogInput		id) const;
    //! Get the value of a digital input retrieved inside the class.
    /*!
    ** Get the value of a digital input retrieved inside the class.
    ** \param id The id of the input you wish to get.
    ** \return The digital value.
    */
    bool			GetDigital(DigitalInput		id) const;
    //! Get values of every digital input retrieved inside the class.
    /*!
    ** Get values of every digital input retrieved inside the class.
    ** \return All digital values, one per bit.
    */
    unsigned char		GetDigital(void) const;

    //! Send to the board values set in the class.
    /*!
    ** Send to the board values set in the class. You have to set values
    ** before thanks to Set* functions.
    ** \return True if everything went well.
    */
    bool			WriteOutputs(void) const;

    //! Set an analog output.
    /*!
    ** Set an analog output.
    ** \param id The id of the analog output to set.
    ** \param value The value to set
    */
    void			SetAnalog(AnalogOutput		id,
					  unsigned char		value);
    //! Set a digital output.
    /*!
    ** Set a digital output.
    ** \param id The id of the digital output to set.
    ** \param value The value to set.
    */
    void			SetDigital(DigitalOutput	id,
					   bool			value);
    //! Set every digital output at once.
    /*!
    ** Set every digital output at once.
    ** \param value All digital values, one per bit.
    */
    void			SetDigital(unsigned char	value);

    //! Build the PVM110N communicator.
    PVM110N(void);
    //! Destroy the PVM110N communicator. Close its usb device if it was still opened.
    ~PVM110N(void);
  };
}

#endif	//		__HBS_MISC_PVM110N_DRIVER_HPP__
