/*
** Jason Brillante "Damdoshi"
** Hanged Bunny Studio 2014-2016
**
** Bibliotheque Lapin
*/

/*!
** \file buffer.h
** The buffer.h file contains the header of every graphic elements in
** the bunny library.
*/

#ifndef				__LAPIN_BUFFER_H__
# define			__LAPIN_BUFFER_H__
# if				!defined(__LAPIN_H__)
#  error			You cannot include this file directly.
# endif
# include			<sys/types.h>
# ifndef			BUNNY_EXTENDED_DATA_LENGTH
#  define			BUNNY_EXTENDED_DATA_LENGTH		4
# endif

typedef union			s_bunny_extended_data
{
  char				space[sizeof(void*)];
  t_bunny_position		position;
  t_bunny_configuration		*configuration;
  const char			*string;
  void				*data;
  int				int_data;
  float				float_data;
}				t_bunny_extended_data;

/*!
** The t_bunny_buffer is a structure that contains foundamental
** informations about a 2D graphic space. It contains its
** width and its height. It also contains a private field
** which is used by the library only.
**
** Several other structure contains a t_bunny_buffer:
** - t_bunny_window
** - t_bunny_clipable / t_bunny_picture
** - t_bunny_pixelarray, throught t_bunny_clipable
*/
typedef struct			s_bunny_buffer
{
  const size_t			_private[4];
  ssize_t			width;
  ssize_t			height;
  t_bunny_extended_data		data[BUNNY_EXTENDED_DATA_LENGTH];
}				t_bunny_buffer;

#endif	/*			__LAPIN_BUFFER_H__		*/
