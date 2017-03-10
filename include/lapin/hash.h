/*
** Jason Brillante "Damdoshi"
** Hanged Bunny Studio 2014-2017
**
** Bibliotheque Lapin
*/

/*!
** \file hash.h
** Hash function. As bunny_security, they are not
** made to be safe in term of crack or hack.
*/

#ifndef				__LAPIN_HASH_H__
# define			__LAPIN_HASH_H__

/*!
** t_unny_hash's value are hash algorithm.
** BH_MULTIPLIER works well with ASCII strings
** BH_FNV with bytes
** Any value equal or greater than BH_CUSTOM will call the gl_bunny_my_hash function pointer.
*/
typedef enum			e_bunny_hash
  {
    BH_MULTIPLIER,
    BH_FNV,
    BH_CUSTOM
  }				t_bunny_hash;

/*!
** Compute a short hash. 
** \param hash The algorithm to use.
** \param ptr The data to hash
** \param len The size of the data to hash
** \return The data hash
*/
uint64_t			bunny_hash(t_bunny_hash			hash,
					   const void			*ptr,
					   size_t			len);

/*!
** The type of the function that will be called when BH_CUSTOM or greater is
** passed to bunny_hash.
*/
typedef uint64_t		(*t_bunny_my_hash)(t_bunny_hash		hash,
						   const void		*ptr,
						   size_t		len);

/*!
** The function pointer that will point on the function that will be called
** when bunny_hash is called with BH_CUSTOM or greater as hash.
*/
extern t_bunny_my_hash		gl_bunny_my_hash;


#endif	/*			__LAPIN_HASH_H__	*/
