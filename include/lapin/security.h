/*
** Jason Brillante "Damdoshi"
** Hanged Bunny Studio 2014-2016
**
** Bibliotheque Lapin
*/

/*!
** \file security.h

*/

#ifndef				__LAPIN_SECURITY_H__
# define			__LAPIN_SECURITY_H__
# if				!defined(__LAPIN_H__)
#  error			You cannot include this file directly.
# endif

typedef enum			e_bunny_ciphering
  {
    BS_XOR,			/* ^ */
    BS_CAESAR,			/* + */
    BS_SHAKER			/* swap data in the buffer */
  }				t_bunny_ciphering;

typedef struct			s_bunny_key
{
  const size_t			length;
# ifndef			__ANSI__
  const char			key[0];
# else
  const char			key[1];
# endif
}				t_bunny_key;

const t_bunny_key		*bunny_default_key(void);
bool				bunny_fill_default_key(const char	*bunny_program);

t_bunny_key			*bunny_new_key(size_t			len);
void				bunny_delete_key(t_bunny_key		*key);

bool				bunny_cipher_file(const char		*file,
						  t_bunny_ciphering	ciphering,
						  const t_bunny_key	*key);
bool				bunny_uncipher_file(const char		*file,
						    t_bunny_ciphering	ciphering,
						    const t_bunny_key	*key);

void				bunny_cipher_data(void			*data,
						  size_t		datalen,
						  t_bunny_ciphering	ciphering,
						  const t_bunny_key	*key);
void				bunny_uncipher_data(void		*data,
						    size_t		data_len,
						    t_bunny_ciphering	ciphering,
						    const t_bunny_key	*key);

#endif	/*			__LAPIN_SECURITY_H__			*/
