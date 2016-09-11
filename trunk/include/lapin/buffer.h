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
  const char			_private[2 * sizeof(size_t)];
  int32_t			width;
  int32_t			height;
}				t_bunny_buffer;

#endif	/*			__LAPIN_BUFFER_H__		*/
