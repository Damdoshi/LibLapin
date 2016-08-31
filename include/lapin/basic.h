/*
** Jason Brillante "Damdoshi"
** Hanged Bunny Studio 2014-2016
**
**
** Bibliotheque Lapin
*/

#ifndef				__LAPIN_BASIC_H__
# define			__LAPIN_BASIC_H__
# include			<stdbool.h>
# include			<stdint.h>
# include			<stdlib.h>
# ifdef				__WIN32
#  pragma			packed
#  define			PACKED
# else
#  define			PACKED			__attribute__((packed))
# endif
# ifdef				__cplusplus
#  include			"lapin/cpp_guard.hpp"
# endif
# include			"lapin/enum.h"
# include			"lapin/self_test.h"
# ifndef			M_PI
#  define			M_PI			3.14159265358979323846
# endif
# define			LAPIN_MAJOR_VERSION	1
# define			LAPIN_MINOR_VERSION	9

/*
** *****
** ****
** ***  A:\> SYSTEM
** ** ____________________________________________________________________
** * /	        						   \ _[]x \
** || Use LAPIN_ALLOCATOR_OVERLOAD and LAPIN_ALLOCATOR_DEACTIVATED  ``````|
** || in your Makefile with the -D option. Do not set them inside your    |
** || source code, it may be inefficient.                                 |
** ||                                                                     |
** || bunny_malloc, bunny_calloc, bunny_realloc and bunny_free work like  |
** || malloc, calloc, realloc and free.                                   |
** ||                                                                     |
** || liblapin allocator may shadow memory error under valgrind.          |
** || You should disable it before using it.                              |
** ||                                                                     |
** || bunny_malloc is here for two reasons: it allows the assistant to    |
** || limit the amount of memory during an evaluation but also to provoke |
** || segmentation fault when you create buffers overflow.                |
** ||                                                                     |
** || Of course, your program, if you create this kind of error, may work |
** || with the system malloc because of its solidity. It does not mean    |
** || that it is not your fault.                                          |
** |\                                                                     |
** |\\____________________________________________________________________/
** |//-------------------------------------------------------------------\\
** |/                                                                    ||
** || bunny_set_memory_check enable or disable memory check. The program ||
** || may slow down with the check enabled. Use it only while debugging  ||
** ||                                                                    \|
** || bunny_set_maximum ram takes the number of ram in bytes that bunny   '
** || malloc, calloc and realloc are allowed to reserve.
** |*
** *
*/

# ifdef				LAPIN_ALLOCATOR_OVERLOAD
#  define			malloc						bunny_malloc
#  define			calloc						bunny_calloc
#  define			realloc						bunny_realloc
#  define			free						bunny_free
# endif
# ifdef				LAPIN_ALLOCATOR_DEACTIVATED
#  define			bunny_malloc					malloc
#  define			bunny_calloc					calloc
#  define			bunny_realloc					realloc
#  define			bunny_free					free
# endif

void				*bunny_malloc(size_t				siz);
void				*bunny_calloc(size_t				num,
					      size_t				siz);
void				*bunny_realloc(void				*ptr,
					       size_t				siz);
void				bunny_free(void					*ptr);

void				bunny_set_memory_check(bool			chk);
void				bunny_set_maximum_ram(size_t			byt);

/*
** *****
** ****
** ***  A:\> COLOR
** **
** *|
** || BLACK, RED, GREEN, BLUE, PURPLE, TEAL, YELLOW, WHITE and PINK
** || are macros that contains values that are directly assignable to 32-bits integer (int)
** |*
** *
*/
# include			"lapin/color.h"

# define			BLACK						(255 << (ALPHA_CMP * 8))

# define			RED						(BLACK | (255 << RED_CMP * 8))
# define			GREEN						(BLACK | (255 << GREEN_CMP * 8))
# define			BLUE						(BLACK | (255 << BLUE_CMP * 8))

# define			PURPLE						(RED | BLUE)
# define			TEAL						(GREEN | BLUE)
# define			YELLOW						(RED | GREEN)

# define			WHITE						(RED | GREEN | BLUE)

/*
** My favorite color <3
*/
# define			PINK						0xFF7777FF
# define			PINK2						0xFFB469FF

/*
** *****
** ****
** ***  A:\> POSITION
** **
** *|
** || t_bunny_position is useful when you directly write inside a picture
** || t_bunny_accurate_position is useful when you are making math
** |*
** *
*/
typedef struct			s_bunny_position
{
  int32_t			x;
  int32_t			y;
}				t_bunny_position;
typedef t_bunny_position	t_bunny_size;
typedef struct			s_bunny_accurate_position
{
  double			x;
  double			y;
}				t_bunny_accurate_position;

/*
** *****
** ****
** ***  A:\> WINDOW
** **
** *|
** || t_bunny_buffer is a graphical buffer. window and picture both got one.
** || It contains private data, width and height of the graphical buffer.
** ||
** || t_bunny_window is a window. It contains a buffer with contains information
** || about the width and height of the window, and the window name.
** ||
** || bunny_start create a window. It takes width and height of the window,
** || a parameter to enable or disable fullscreen view and a name for the
** || window. It return a NULL pointer on error.
** ||
** || bunny_display display the content of the window on screen.
** ||
** || bunny_stop destroy the given window.
** ||
** || /!\ Never try to create a t_bunny_buffer or a t_bunny_window by yourself
** ||     with malloc or by puting it on the stack, it won't work. Always
** ||     use bunny_start and a t_bunny_window*.
** |*
** *
*/
typedef struct			s_bunny_buffer
{
  const char			_private[2 * sizeof(size_t)];
  int32_t			width;
  int32_t			height;
}				t_bunny_buffer;

typedef struct			s_bunny_window
{
  t_bunny_buffer		buffer;
  const char * const		name;
}				t_bunny_window;

t_bunny_window			*bunny_start(unsigned int			wid,
					     unsigned int			hei,
					     bool				ful,
					     const char				*nam);
void				bunny_display(const t_bunny_window		*win);
void				bunny_stop(t_bunny_window			*win);


/*
** *****
** ****
** ***  A:\> PIXELARRAY
** **
** *|
** || bunny_new_pixelarray create a t_bunny_pixelarray structure and
** || fill it with defaults values. It return NULL on error. It takes
** || its size as parameter.
** ||
** || t_bunny_pixelarray is a picture in random access memory that can
** || be accessed throught its pointer pixels.
** || It contains a t_bunny_clipable (which contains a t_bunny_buffer) that
** || is composed of properties that modify the way the clipable is blit.
** || clip_* are useful to set a subset of the picture to be draw. origin
** || is useful to move the reference point that is used as origin while
** || rotating, scaling and bliting. Scale change the size while blit, and
** || rotation the orientation. Rotation is a radian number.
** ||
** || /!\ On a pixelarray, clipable properties are ignored, unless you program
** ||     a bunny_blit functions that respect the t_bunny_my_blit type and set
** ||     it inside gl_bunny_my_blit.
** ||
** || bunny_delete_clipable can delete a pixelarray. Consider the object
** || pix as a t_bunny_pixelarray pointer, you can destroy it this way:
** || bunny_delete_clipable(&pix->clipable);
** || Or this way:
** || bunny_delete_clipable((t_bunny_clipable*)pix);
** ||
** || bunny_blit copy the content of a clipable inside a buffer at
** || the specified position. Sending NULL as pos is equivalent to a (0, 0)
** || position. In order to put a t_bunny_pixelarray *pix on a t_bunny_window
** || *win at the (0, 0) call bunny_blit this way:
** || bunny_blit(&win->buffer, &pix->clipable, NULL);
** || Or this way:
** || bunny_blit((t_bunny_buffer*)win, (t_bunny_clipable*)pix, NULL);
** ||
** || gl_bunny_my_blit is a function pointer called when you try
** || to bunny_blit a pixelarray on another pixelarray. If you do
** || not set it before using it, it does nothing.
** |*
** *
*/
typedef struct			s_bunny_clipable
{
  t_bunny_buffer		buffer;
  int32_t			clip_x_position;
  int32_t			clip_y_position;
  int32_t			clip_width;
  int32_t			clip_height;
  t_bunny_accurate_position	origin;
  t_bunny_accurate_position	scale;
  double			rotation;
  t_bunny_color			color_mask;
} PACKED			t_bunny_clipable;

typedef struct			s_bunny_pixelarray
{
  t_bunny_clipable		clipable;
  void * const			pixels;
}				t_bunny_pixelarray;

t_bunny_pixelarray		*bunny_new_pixelarray(unsigned int		wid,
						      unsigned int		hei);
void				bunny_delete_clipable(t_bunny_clipable		*clp);

void				bunny_blit(t_bunny_buffer			*buf,
					   const t_bunny_clipable		*clp,
					   const t_bunny_position		*pos);

typedef void			(*t_bunny_my_blit)(t_bunny_pixelarray		*pix,
						   const t_bunny_pixelarray	*in,
						   const t_bunny_position	*pos);
extern t_bunny_my_blit		gl_bunny_my_blit;

/*
** *****
** ****
** ***  A:\> EVENTS
** **
** *|
** || t_bunny_key, click, move and loop are function pointer type. These type
** || are used by bunny_set_*_response functions and bunny_set_loop_main_function.
** ||
** || bunny_set_*_response and bunny_set_loop_main_function are useful to set
** || functions that will be called under specific circumstance: a key or a mouse
** || button is pressed or released, or the mouse moved, or a specific amount
** || of time passed.
** ||
** || These functions gave to bunny_set_*_response and bunny_set_loop_main_function
** || are called by bunny_loop.
** ||
** || bunny_loop takes the window as first parameter, a frequency as second (which is
** || how many times the bunny_set_loop_main_function defined function is called per
** || second) and a parameter to send to every response function.s
** ||
** || The type t_bunny_response must be returned by response functions. If the return
** || value is different from GO_ON, it makes the bunny_loop exiting while returning
** || value of the response function.
** || EXIT_ON_CROSS should not be used. It is returned when the close button of the window
** || is pressed.
** ||
** || GO_DOWN and GO_UP mean something is just pressed or just released. It may be
** || a key, but also a mouse button or a joystick button.
** ||
** || bunny_get_* functions return arrays or informations about peripherials.
** || /!\ They are active only if you have already set an event response.
** ||
** || These functions works only with a single window.
** || For multiple window functions, see mw functions in lapin_advanced.h
** ||
** || There is more events available in lapin_advance.h
** |*
** *
*/
typedef enum			e_bunny_response
  {
    EXIT_ON_ERROR,
    EXIT_ON_CROSS,
    EXIT_ON_SUCCESS,
    SWITCH_CONTEXT,
    GO_ON
  }				t_bunny_response;
typedef enum			e_bunny_event_state
  {
    GO_DOWN,
    GO_UP,
    CONNECTED			= GO_DOWN,
    DISCONNECTED		= GO_UP
  }				t_bunny_event_state;

typedef t_bunny_response	(*t_bunny_key)(t_bunny_event_state		sta,
					       t_bunny_keysym			sym,
					       void				*dat);
void				bunny_set_key_response(t_bunny_key		key);
const bool			*bunny_get_keyboard(void);

typedef t_bunny_response	(*t_bunny_click)(t_bunny_event_state		sta,
						 t_bunny_mouse_button		but,
						 void				*dat);
void				bunny_set_click_response(t_bunny_click		cli);
const bool			*bunny_get_mouse_button(void);

typedef t_bunny_response	(*t_bunny_move)(const t_bunny_position		*relative,
						void				*dat);
void				bunny_set_move_response(t_bunny_move		mov);
const t_bunny_position		*bunny_get_mouse_position(void);

typedef t_bunny_response	(*t_bunny_loop)(void				*dat);
void				bunny_set_loop_main_function(t_bunny_loop	lop);

t_bunny_response		bunny_loop(t_bunny_window			*win,
					   uint8_t				freq,
					   void					*dat);

/*
** *****
** ****
** ***  A:\> SOUND
** **
** *|
** || t_bunny_sound is a type that can be used by bunny_sound_* functions. It
** || represents anything that is a sound (music or effect)
** ||
** || t_bunny_music is a big sound file that is streamed.
** ||
** || t_bunny_sound is a tiny sound file, fully loaded into memory.
** ||
** || bunny_load_music and bunny_load_effect take file and return pointers to
** || datas. bunny_new_effect create a sound with a precised size in second.
** ||
** || bunny_save_effect allow you to save a sound effect in a file.
** ||
** || bunny_compute_effect must be called before playing an effect
** || if the data behind the sample pointer were modified manually.
** ||
** || bunny_sound_volume, pitch and loop allow to change the volume, the speed
** || of playing the sound and if it loops after its end.
** ||
** || bunny_sound_play and stop play and stop the sound.
** ||
** || bunny_delete_sound simply delete the sound.
** ||
** || Supported formats include ogg, wav and flac. No mp3.
** |*
** *
*/
typedef struct			s_bunny_sound
{
  const char			_private[sizeof(int32_t)];
  const char * const		file;
}				t_bunny_sound;
typedef struct			s_bunny_music
{
  t_bunny_sound			sound;
  const double			duration;
}				t_bunny_music;

typedef struct			s_bunny_effect
{
  t_bunny_sound			sound;
  const size_t			sample_per_second;
  const size_t			duration;
  int16_t * const		sample;
}				t_bunny_effect;

t_bunny_effect			*bunny_new_effect(unsigned int			duration);
t_bunny_music			*bunny_load_music(const char			*file);
t_bunny_effect			*bunny_load_effect(const char			*file);
bool				bunny_save_effect(const t_bunny_effect		*effect,
						  const char			*str);

bool				bunny_compute_effect(t_bunny_effect		*effect);

void				bunny_sound_volume(t_bunny_sound		*sound,
						   double			volume);
void				bunny_sound_pitch(t_bunny_sound			*sound,
						  double			pitch);
void				bunny_sound_loop(t_bunny_sound			*sound,
						 bool				loop);
void				bunny_sound_position(t_bunny_sound		*sound,
						     double			x,
						     double			y,
						     double			z);
void				bunny_sound_attenuation(t_bunny_sound		*sound,
							double			attenuation);

void				bunny_sound_play(t_bunny_sound			*sound);
void				bunny_sound_stop(t_bunny_sound			*sound);

double				bunny_music_get_cursor(t_bunny_music		*music);

void				bunny_delete_sound(t_bunny_sound		*sound);

/*
** *****
** ****
** ***  A:\> CONFIGURATION
** **
** *|
** || bunny_new_ini create an empty three-level hierarchical database.
** ||
** || bunny_load_ini create the same kind of structure and fill it with informations
** || found in the given file
** ||
** || bunny_save_ini save to a file the content of the ini structure.
** ||
** || bunny_ini_delete delete a ini structure.
** ||
** || bunny_ini_get_field allow you to access to a data inside a t_bunny_ini,
** || with the name of its group (the scope), its role (the field) and its position
** || inside the field (the index), considering each field are arrays.
** || The data which is returned must not be modified. Of course, if the ini is
** || destroyed, the data lapses.
** ||
** || If you have this kind of file, with a few of the crew of some Star Trek series
** || and informations about them:
** ||
** || [the_next_generation]
** || captain="jean luc picard"
** || commander="william riker","deanna troi","data","beverly crusher"
** || [deep_space_nine]
** || captain="benjamin sisko"
** || commander="worf"
** ||
** || You can get all commanders in the_next_generation by making this:
** || bunny_ini_get_field(ini, "the_next_generation", "commander", i);
** || And making i loops from 0 until the function return NULL.
** ||
** || bunny_ini_set_field allow you to set a value inside a t_bunny_ini, at
** || a specified position. Give ERASE_INDEX, ERASE_FIELD or ERASE_SCOPE if you
** || want to delete an index, a field or a scope.
** ||
** ||
** |*
** *
*/
typedef void			t_bunny_ini;

extern const char		*DEFAULT_SCOPE;
# define			ERASE_SCOPE					NULL
# define			ERASE_FIELD					((unsigned int)-1)
# define			ERASE_INDEX					NULL

t_bunny_ini			*bunny_new_ini(void);
t_bunny_ini			*bunny_load_ini(const char			*file);
bool				bunny_save_ini(t_bunny_ini			*ini,
					       const char			*file);

const char			*bunny_ini_get_field(const t_bunny_ini		*ini,
						     const char			*scope,
						     const char			*field,
						     unsigned int		index);
void				bunny_ini_set_field(t_bunny_ini			*ini,
						    const char			*scope,
						    const char			*field,
						    unsigned int		index,
						    const char			*value);

void				bunny_delete_ini(t_bunny_ini			*ini);

const char			*bunny_ini_get_error(void);

# include			"lapin/compat.h"
# ifdef				__cplusplus
#  include			"lapin/cpp_guard_end.hpp"
# endif
#endif	/*			__LAPIN_BASIC_H__			*/
