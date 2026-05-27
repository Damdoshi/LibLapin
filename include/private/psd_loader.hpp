/*
** Jason Brillante "Damdoshi"
** Hanged Bunny Studio 2014-2026
**
** Bibliotheque Lapin
*/

#ifndef				__LAPIN_PRIVATE_PSD_LOADER_HPP__
# define			__LAPIN_PRIVATE_PSD_LOADER_HPP__

# include			<stddef.h>
# include			<stdbool.h>

bool				_bunny_is_psd_filename(const char			*file);
bool				_bunny_is_psd_buffer(const void				*buffer,
						     size_t				len);

t_bunny_picture			*_bunny_load_psd_picture_from_memory(const void		*buffer,
								     size_t		len,
								     const char		*file);

t_bunny_pixelarray		*_bunny_load_psd_pixelarray_from_memory(const void	*buffer,
									size_t		len,
									const char	*file);

#endif	/*			__LAPIN_PRIVATE_PSD_LOADER_HPP__			*/
