/*
** Jason Brillante "Damdoshi"
** Hanged Bunny Studio 2014-2016
**
** Bibliotheque Lapin
*/

/*!
** \file security.h
** This module is about weak security by ciphering.
** It allows you to cipher and uncipher files or buffers with
** a specified key that can also be an internally stored key.
**
** Note that this is not for true security reasons that this
** module is here: the real purpose is to prevent cheating.
*/

#ifndef				__LAPIN_SECURITY_H__
# define			__LAPIN_SECURITY_H__
# if				!defined(__LAPIN_H__)
#  error			You cannot include this file directly.
# endif

/*!
** t_bunny_ciphering's values are ciphering algorithm.
** BS_XOR use the '^' operator to cipher.
** BS_CAESAR use the '+' / '-' operator to cipher / uncipher.
** BS_SHAKER swap the currently ciphered data chunk with another chunk at
** a specified offset
** BS_CUSTOM (and greater values) means that you want to use
** a custom algorithm, so the system will call the function defined
** in gl_bunny_my_cipher or gl_bunny_my_uncipher.
*/
typedef enum			e_bunny_ciphering
  {
    BS_XOR,			/* ^ */
    BS_CAESAR,			/* + */
    BS_SHAKER,			/* swap data in the buffer */
    /* BS_COKTAIL - it mix all previous algorithm */
    BS_CUSTOM			/* any >= BS_CUSTOM */
  }				t_bunny_ciphering;

/*!
** An associative table for an easy enumeration<->string transaction
*/
extern const char * const	gl_bunny_ciphering_table[BS_CUSTOM];

/*!
** Resolve the ciphering algorithm name with the gl_bunny_ciphering_table tbale
*/
t_bunny_ciphering		bunny_get_ciphering(const char		*name);

/*!
** A t_bunny_key represents a ciphering key. The first field is the length
** of the second in bytes. The second field is the key iteself.
** /!\ Thet are NOT characters, that's just bytes. There may be no null
** terminator, you have to use the length field to browse it if you wish
** to.
*/
typedef struct			s_bunny_cipher_key
{
  int32_t			length;
# ifndef			__ANSI__
  char				key[0];
# else
  char				key[1];
# endif
}				t_bunny_cipher_key;

/*!
** Get the binary-embedded key. Its default value is plain 0 that are supposed
** to be replaced by a random value thanks to the bunny_fill_default_key function.
** The ressources you wish to use are supposed to be ciphered with the same key
** after.
** \return The binary-embedded key.
*/
const t_bunny_cipher_key	*bunny_default_key(void);

/*!
** Erase an unset binary-embedded key (filled with the plain 0 default value)
** of the sent file with a randomly generated key. By making so, it enables
** the cipher/unciphering capacity of the bunny security module (because
** the key used won't be 0 anymore)
** \param bunny_program A binary file, designed with LibLapin, to modify
** \param key The key to insert inside the binary. If NULL, a key is generated.
** \return True if every thing went well.
*/
bool				bunny_fill_default_key(const char	*bunny_program,
						       t_bunny_cipher_key *key);

/*!
** The t_bunny_key_twist function type is the type of the function that will be
** called to generate a cipher key from the inside hardcoded key. The purpose
** of this is to make more heavy the protection: the key used for ciphering will not
** be the one which is directly readable inside the program, but a temporary one
** generated from the key and an algorithm.
** Of course, you should avoid non deterministic behavior...
*/
typedef t_bunny_cipher_key	*(*t_bunny_key_twist)(const t_bunny_cipher_key *inkey,
						      t_bunny_cipher_key *outkey);

/*!
** The function that will be called to tweak the hardcoded key.
** If not set, a default algorithm will be applied.
*/
extern t_bunny_key_twist	gl_bunny_my_key_twist;

/*!
** Create a new key of the given size. The key is filled with random values.
** \param len The size of the key. Should be greater than 0.
** \return The generated key or NULL on error.
*/
t_bunny_cipher_key		*bunny_new_key(size_t			len);

/*!
** Delete the given key.
** \param key The key to delete.
*/
void				bunny_delete_key(t_bunny_cipher_key	*key);

/*!
** Open the given file, load its content, cipher it and save it right after.
** \param file The file to cipher.
** \param ciphering The algorithm to use.
** \param key The key used by the ciphering algorithm
** \return True if everything went well, false on errror.
*/
bool				bunny_cipher_file(const char		*file,
						  t_bunny_ciphering	ciphering,
						  const t_bunny_cipher_key *key);

/*!
** Open the given file, load its content, uncipher it and save it right after.
** \param file The file to uncipher.
** \param ciphering The algorithm to use.
** \param key The key used by the unciphering algorithm
** \return True if everything went well, false on errror.
*/
bool				bunny_uncipher_file(const char		*file,
						    t_bunny_ciphering	ciphering,
						    const t_bunny_cipher_key *key);

/*!
** Cipher the sent buffer.
** \param data The buffer to cipher
** \param datalen The length of the buffer to cipher.
** \param ciphering The algorithm to use.
** \param key The key used by the ciphering algorithm
*/
void				bunny_cipher_data(void			*data,
						  size_t		datalen,
						  t_bunny_ciphering	ciphering,
						  const t_bunny_cipher_key *key);

/*!
** Uncipher the sent buffer.
** \param data The buffer to uncipher
** \param datalen The length of the buffer to uncipher.
** \param ciphering The algorithm to use.
** \param key The key used by the unciphering algorithm
*/
void				bunny_uncipher_data(void		*data,
						    size_t		data_len,
						    t_bunny_ciphering	ciphering,
						    const t_bunny_cipher_key *key);

/*!
** The type of the gl_bunny_my_cipher function pointer, that may be used
** if you wish to bring your own ciphering algorithm.
** The ciphering parameter is the value sent to bunny_cipher_* as ciphering
** parameter: it should be BS_CUSTOM or any greater value (You choose...)
*/
typedef void			(*t_bunny_my_cipher)(t_bunny_ciphering	ciphering,
						     char		*buffer,
						     size_t		len,
						     const t_bunny_cipher_key *key);

/*!
** A function pointer that contains a function that will be called if 
** bunny_cipher_* is called with BS_CUSTOM or any greater value as ciphering
** algorithm.
*/
extern t_bunny_my_cipher	gl_bunny_my_cipher;

/*!
** The type of the gl_bunny_my_uncipher function pointer, that may be used
** if you wish to bring your own unciphering algorithm.
** The ciphering parameter is the value sent to bunny_uncipher_* as ciphering
** parameter: it should be BS_CUSTOM or any greater value (You choose...)
*/
typedef void			(*t_bunny_my_uncipher)(t_bunny_ciphering ciphering,
						       char		*buffer,
						       size_t		len,
						       const t_bunny_cipher_key *key);

/*!
** A function pointer that contains a function that will be called if 
** bunny_uncipher_* is called with BS_CUSTOM or any greater value as ciphering
** algorithm.
*/
extern t_bunny_my_uncipher	gl_bunny_my_uncipher;

#endif	/*			__LAPIN_SECURITY_H__			*/

