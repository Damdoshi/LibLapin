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


/**
 * @doc
 * @doc-symbol hardware
 * @doc-kind module
 * @doc-module hardware
 * @doc-order 0
 * @doc-since 0
 * @doc-until latest
 * @doc-level 40
 *
 * @doc-lang en
 * @brief Exposes small hardware helpers for VM110N boards, Raspberry Pi GPIO mapping, bitstreams and MAX7219 matrices.
 * @header lapin/hardware.h
 *
 * @doc-lang fr
 * @brief Expose de petites aides matérielles pour les cartes VM110N, le mapping GPIO Raspberry Pi, les flux de bits et les matrices MAX7219.
 * @header lapin/hardware.h
 */

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


/**
 * @doc
 * @doc-symbol t_bunny_vm110n
 * @doc-kind struct
 * @doc-module hardware
 * @doc-order 100
 * @doc-since 0
 * @doc-until latest
 * @doc-level 40
 *
 * @doc-lang en
 * @brief Stores the state used to communicate with a Velleman VM110N board.
 * @description The input fields are refreshed by bunny_vm110n_read. The output fields are sent to the board by bunny_vm110n_write.
 * @field _private Private backend handle. Do not modify it.
 * @field id Board identifier configured by jumper.
 * @field digital_inputs Digital input states read from the board.
 * @field analog_inputs Analog input voltages read from the board.
 * @field digital_outputs Digital output states to write.
 * @field analog_outputs Analog output voltages to write.
 * @see bunny_new_vm110n, bunny_vm110n_read, bunny_vm110n_write
 *
 * @doc-lang fr
 * @brief Stocke l'état utilisé pour communiquer avec une carte Velleman VM110N.
 * @description Les champs d'entrée sont rafraîchis par bunny_vm110n_read. Les champs de sortie sont envoyés à la carte par bunny_vm110n_write.
 * @field _private Handle backend privé. Ne le modifiez pas.
 * @field id Identifiant de la carte configuré par cavalier.
 * @field digital_inputs États des entrées numériques lus depuis la carte.
 * @field analog_inputs Tensions des entrées analogiques lues depuis la carte.
 * @field digital_outputs États des sorties numériques à écrire.
 * @field analog_outputs Tensions des sorties analogiques à écrire.
 * @see bunny_new_vm110n, bunny_vm110n_read, bunny_vm110n_write
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


/**
 * @doc
 * @doc-symbol t_bunny_rpi
 * @doc-kind type
 * @doc-module hardware
 * @doc-order 200
 * @doc-since 0
 * @doc-until latest
 * @doc-level 60
 *
 * @doc-lang en
 * @brief Represents the memory-mapped Raspberry Pi GPIO area.
 * @description t_bunny_rpi is returned by bunny_new_rpi and must be released with bunny_delete_rpi. It is intentionally low-level and hardware-specific.
 * @see bunny_new_rpi, bunny_delete_rpi
 *
 * @doc-lang fr
 * @brief Représente la zone GPIO Raspberry Pi mappée en mémoire.
 * @description t_bunny_rpi est renvoyé par bunny_new_rpi et doit être libéré avec bunny_delete_rpi. Il est volontairement bas niveau et spécifique au matériel.
 * @see bunny_new_rpi, bunny_delete_rpi
 */
typedef volatile uint32_t	t_bunny_rpi;

t_bunny_rpi			*bunny_new_rpi(void);
void				bunny_delete_rpi(t_bunny_rpi			*rpi);

/*
** Représente une unique sortie série
*/



/**
 * @doc
 * @doc-symbol t_bunny_bitstream
 * @doc-kind struct
 * @doc-module hardware
 * @doc-order 250
 * @doc-since 0
 * @doc-until latest
 * @doc-level 50
 *
 * @doc-lang en
 * @brief Stores a serial bit stream associated with one output pin.
 * @description A bitstream accumulates bit values before a hardware-specific backend emits them.
 * @field pin_number Hardware pin associated with the stream.
 * @field pin_stream_capacity Maximum number of bits that can be stored.
 * @field pin_stream_size Current number of stored bits.
 * @field pin_stream Packed bit storage.
 * @see bunny_new_bitstream, bunny_push_bitstream, bunny_pop_bitstream, bunny_top_bitstream
 *
 * @doc-lang fr
 * @brief Stocke un flux série de bits associé à une broche de sortie.
 * @description Un bitstream accumule des valeurs de bits avant qu'un backend matériel spécifique les émette.
 * @field pin_number Broche matérielle associée au flux.
 * @field pin_stream_capacity Nombre maximal de bits stockables.
 * @field pin_stream_size Nombre courant de bits stockés.
 * @field pin_stream Stockage compact des bits.
 * @see bunny_new_bitstream, bunny_push_bitstream, bunny_pop_bitstream, bunny_top_bitstream
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


/**
 * @doc
 * @doc-symbol bunny_delete_bitstream
 * @doc-kind macro
 * @doc-module hardware
 * @doc-order 275
 * @doc-since 0
 * @doc-until latest
 * @doc-level 50
 *
 * @doc-lang en
 * @brief Destroys a bitstream allocated by bunny_new_bitstream.
 * @param b Bitstream to destroy.
 * @see bunny_new_bitstream
 *
 * @doc-lang fr
 * @brief Détruit un bitstream alloué par bunny_new_bitstream.
 * @param b Bitstream à détruire.
 * @see bunny_new_bitstream
 */
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


/**
 * @doc
 * @doc-symbol t_bunny_max7219_command
 * @doc-kind enum
 * @doc-module hardware
 * @doc-order 400
 * @doc-since 0
 * @doc-until latest
 * @doc-level 60
 *
 * @doc-lang en
 * @brief Lists MAX7219 command bytes.
 * @description These values are used internally by the MAX7219 helpers and may also be useful when writing a custom backend.
 * @enum BMC_NO_OPERATION No-operation command.
 * @enum BMC_SET_DIGIT0 Select digit 0.
 * @enum BMC_SET_DIGIT1 Select digit 1.
 * @enum BMC_SET_DIGIT2 Select digit 2.
 * @enum BMC_SET_DIGIT3 Select digit 3.
 * @enum BMC_SET_DIGIT4 Select digit 4.
 * @enum BMC_SET_DIGIT5 Select digit 5.
 * @enum BMC_SET_DIGIT6 Select digit 6.
 * @enum BMC_SET_DIGIT7 Select digit 7.
 * @enum BMC_SET_DECODE_MODE Configure decode mode.
 * @enum BMC_SET_INTENSITY Configure luminosity.
 * @enum BMC_SET_SCANLIMIT Configure scan limit.
 * @enum BMC_SHUTDOWN Enable or disable shutdown mode.
 * @enum BMC_DISPLAY_TEST Enable or disable display test.
 * @see t_bunny_max7219
 *
 * @doc-lang fr
 * @brief Liste les octets de commande MAX7219.
 * @description Ces valeurs sont utilisées en interne par les aides MAX7219 et peuvent aussi servir à écrire un backend personnalisé.
 * @enum BMC_NO_OPERATION Commande sans opération.
 * @enum BMC_SET_DIGIT0 Sélection du digit 0.
 * @enum BMC_SET_DIGIT1 Sélection du digit 1.
 * @enum BMC_SET_DIGIT2 Sélection du digit 2.
 * @enum BMC_SET_DIGIT3 Sélection du digit 3.
 * @enum BMC_SET_DIGIT4 Sélection du digit 4.
 * @enum BMC_SET_DIGIT5 Sélection du digit 5.
 * @enum BMC_SET_DIGIT6 Sélection du digit 6.
 * @enum BMC_SET_DIGIT7 Sélection du digit 7.
 * @enum BMC_SET_DECODE_MODE Configure le mode de décodage.
 * @enum BMC_SET_INTENSITY Configure la luminosité.
 * @enum BMC_SET_SCANLIMIT Configure la limite de scan.
 * @enum BMC_SHUTDOWN Active ou désactive le mode shutdown.
 * @enum BMC_DISPLAY_TEST Active ou désactive le test d'affichage.
 * @see t_bunny_max7219
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



/**
 * @doc
 * @doc-symbol t_bunny_max7219
 * @doc-kind struct
 * @doc-module hardware
 * @doc-order 420
 * @doc-since 0
 * @doc-until latest
 * @doc-level 60
 *
 * @doc-lang en
 * @brief Stores the state of a MAX7219 LED matrix chain.
 * @field pixels Pixel states, arranged by matrix.
 * @field luminosity Per-matrix luminosity values.
 * @field width Width in 8x8 matrices.
 * @field height Height in 8x8 matrices.
 * @field clock_pin Bitstream used for the clock signal.
 * @field load_pin Bitstream used for the load signal.
 * @field data_pin Bitstream used for the data signal.
 * @field stream_progression Current generated stream progression.
 * @see bunny_new_max7219, bunny_max7219_pixels, bunny_delete_max7219
 *
 * @doc-lang fr
 * @brief Stocke l'état d'une chaîne de matrices LED MAX7219.
 * @field pixels États des pixels, organisés par matrice.
 * @field luminosity Valeurs de luminosité par matrice.
 * @field width Largeur en matrices 8x8.
 * @field height Hauteur en matrices 8x8.
 * @field clock_pin Bitstream utilisé pour le signal clock.
 * @field load_pin Bitstream utilisé pour le signal load.
 * @field data_pin Bitstream utilisé pour le signal data.
 * @field stream_progression Progression courante du flux généré.
 * @see bunny_new_max7219, bunny_max7219_pixels, bunny_delete_max7219
 */
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
