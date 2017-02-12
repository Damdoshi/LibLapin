/*
** Jason Brillante "Damdoshi"
** Hanged Bunny Studio 2014-2016
**
**
** Bibliotheque Lapin
*/

#ifndef				__LAPIN_PRIVATE_SECURITY_H__
# define			__LAPIN_PRIVATE_SECURITY_H__

void				__bunny_xor(char			*cnt,
					    size_t			len,
					    const t_bunny_cipher_key	*key);
void				__bunny_caesar(char			*cnt,
					       size_t			len,
					       const t_bunny_cipher_key	*key,
					       bool			cipher);
void				__bunny_shaker(char			*cnt,
					       size_t			len,
					       const t_bunny_cipher_key	*key,
					       bool			cipher);

#endif	/*			__LAPIN_PRIVATE_SECURITY_H__	*/
