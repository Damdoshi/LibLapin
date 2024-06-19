/*
** Jason Brillante "Damdoshi"
** Hanged Bunny Studio 2014-2016
**
** Bibliotheque Lapin
*/

/*!
** \file hardware.h
** A little driver for a specific electronic board and later, some controlers builts on it.
** The electronic board is the Velleman VM110N.
*/

#ifndef				__LAPIN_HARDWARE_H__
# define			__LAPIN_HARDWARE_H__
# if				!defined(__LAPIN_H__)
#  error			You cannot include this file directly.
# endif

/*!
** The t_bunny_vm110n structure contains informations and
** buffers useful to handle the board.
**
** It starts with a private field.
**
** The id match the id of the board, that can be configured thanks to a jumper.
**
** The digital_inputs and analog_inputs are set by the bunny_vm110n_read function
** and match the electronic state of the board. Digital inputs are boolean
** while analog_inputs are double. The value of these double can vary between 0 and 5,
** matching the electronic states that can vary between 0 and 5 volts.
**
** The digital_outputs and analog_outputs are written on the board thanks to
**
*/
typedef struct			s_bunny_vm110n
{
  const void * const		_private;
  const int			id;
  const bool			digital_inputs[5];
  const double			analog_inputs[2];
  bool				digital_outputs[8];
  double			analog_outputs[2];
}				t_bunny_vm110n;

/*!
** Create a t_bunny_vm110n associated with the board of the given id.
** \param id The id of the board we want to control
** \return A t_bunny_vm110n or NULL on error.
*/
t_bunny_vm110n			*bunny_new_vm110n(size_t			id);

/*!
** Destroy the vm110n handler.
** \param hdr The vm110n handler to destroy.
*/
void				bunny_delete_vm110n(t_bunny_vm110n		*hrd);

/*!
** Read states on the electronic board. Registered them inside digital_inputs and
** analog_inputs attributes of t_bunny_vm110n.
** \param hrd The board to read
** \return True if the reading was done. False on error.
*/
bool				bunny_vm110n_read(t_bunny_vm110n		*hrd);

/*!
** Write states on the electronic board. Written states are stored inside digital_outputs
** and analog_outputs attributes of t_bunny_vm110n.
** \param hdr The board where to write
** \return True if the writing was done. False on error.
*/
bool				bunny_vm110n_write(const t_bunny_vm110n		*hdr);

/*
** Le type permettant de manipuler la broche du RPI.
** Pour l'instant, rien n'est fait...
*/
typedef volatile uint32_t	t_bunny_rpi;

t_bunny_rpi			*bunny_new_rpi(void);
void				bunny_delete_rpi(t_bunny_rpi			*rpi);

/*
** Représente une unique sortie série
*/

typedef struct			s_bunny_bitstream
{
  int				pin_number;
  size_t			pin_stream_capacity; // In bit
  size_t			pin_stream_size; // In bit
  int				pin_stream[__ZERO_LENGTH__];
}				t_bunny_bitstream;

t_bunny_bitstream		*bunny_new_bitstream(int			pin_num,
						     int			pin_stream_capacity);
# define			bunny_delete_bitstream(b)			bunny_free(b)

int				bunny_push_bitstream(t_bunny_bitstream		*bs,
						     size_t			nbr_bit,
						     int			val);
int				bunny_pop_bitstream(t_bunny_bitstream		*bs);
int				bunny_top_bitstream(t_bunny_bitstream		*bs);

/*
** Le type permettant de manipuler un Arduino UNO
** associé à une matrice
** Néccessite arduino-core
*/
typedef enum			e_bunny_max7219_command
  {
    BMC_NO_OPERATION,
    BMC_SET_DIGIT0,
    BMC_SET_DIGIT1,
    BMC_SET_DIGIT2,
    BMC_SET_DIGIT3,
    BMC_SET_DIGIT4,
    BMC_SET_DIGIT5,
    BMC_SET_DIGIT6,
    BMC_SET_DIGIT7,
    BMC_SET_DECODE_MODE,
    BMC_SET_INTENSITY,
    BMC_SET_SCANLIMIT,
    BMC_SHUTDOWN,
    //
    //
    //
    BMC_DISPLAY_TEST		= 15
  }				t_bunny_max7219_command;

typedef struct			s_bunny_max7219
{
  bool * const			pixels;
  char * const			luminosity;
  size_t			width; // In matrix
  size_t			height; // In matrix
  t_bunny_bitstream		*clock_pin;
  t_bunny_bitstream		*load_pin;
  t_bunny_bitstream		*data_pin;
  int				stream_progression;
}				t_bunny_max7219;

t_bunny_max7219			*bunny_new_max7219(size_t			w,
						   size_t			h,
						   int				clockpin,
						   int				loadpin,
						   int				datapin);
bool				bunny_max7219_status(t_bunny_max7219		*m);
bool				bunny_max7219_luminosity(t_bunny_max7219	*m);
bool				bunny_max7219_pixels(t_bunny_max7219		*m);
void				bunny_delete_max7219(t_bunny_max7219		*m);


// N'existe pas, c'est a un systeme de carte d'intégrer cette ecriture, comme le vm110n ou l'arduino
bool				bunny_max7219_write(t_bunny_max7219		*m);


#endif	/*			__LAPIN_VM110N_H__				*/
