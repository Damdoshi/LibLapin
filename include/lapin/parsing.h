/*
** Jason Brillante "Damdoshi"
** Hanged Bunny Studio 2014-2016
**
** Bibliotheque Lapin
*/


/**
 * @doc
 * @doc-symbol parsing
 * @doc-kind module
 * @doc-module parsing
 * @doc-order 0
 * @doc-since 12
 * @doc-until latest
 * @doc-level 30
 *
 * @doc-lang en
 * @brief Provides small parsing helpers for strings and binary boxes.
 * @description The parsing module contains cursor-based helpers that check or read characters, identifiers, numbers and escaped strings. The index parameter used by most functions is both an input and an output cursor.
 * @description If gl_bunny_read_whitespace is set, most check/read helpers call it before trying to parse their own token.
 * @header lapin/parsing.h
 *
 * @doc-lang fr
 * @brief Fournit de petits assistants de parsing pour les chaînes et les boîtes binaires.
 * @description Le module parsing contient des assistants à curseur qui vérifient ou lisent des caractères, identifiants, nombres et chaînes échappées. Le paramètre index utilisé par la plupart des fonctions sert à la fois d'entrée et de curseur de sortie.
 * @description Si gl_bunny_read_whitespace est renseigné, la plupart des assistants check/read l'appellent avant d'essayer de parser leur propre jeton.
 * @header lapin/parsing.h
 */
/*!
** \file parsing.h
** Parsing tools.
*/

#ifndef			__LAPIN_PARSING_H__
# define		__LAPIN_PARSING_H__
# if			!defined(__LAPIN_H__)
#  error		You cannot include this file directly.
# endif

/*!
** Check how many char from &str[*index] can be found in token
** before not being found.
** Also useful to check if str[*index] is in token.
** \param str The string to test
** \param index A pointer to indicate the index where to start in string
** \param token Characters that are searched
** \return How many characters browsed before finding a character
** which is not in token.
*/
int			bunny_check_char(const char		*str,
					 ssize_t		*index,
					 const char		*token);

/*!
** Check if the string at &str[*index] match token.
** \param str The string to test
** \param index A pointer to indicate the index where to start in string
** \param token String to test
** \return True if the string was found.
*/
bool			bunny_check_text(const char		*str,
					 ssize_t		*index,
					 const char		*token);

/*!
** Check if the string at &str[*index] match token, ignoring case.
** \param str The string to test
** \param index A pointer to indicate the index where to start in string
** \param token String to test
** \return True if the string was found.
*/
bool			bunny_check_text_case(const char	*str,
					      ssize_t		*index,
					      const char	*token);

/*!
** Increase *index while str[*index] is in token. Indicates if *index
** was modified.
** \param The string to test
** \param index A pointer to indicate the index where to start in string
** \param token Whitelist of characters
** \return If *index was modified at least one time
*/
bool			bunny_read_char(const char		*str,
					ssize_t			*index,
					const char		*token);

/*!
** Increase *index if token is found at &str[*index]. Return if it was
** found.
** \param str The string to test
** \param index A pointer to indicate the index where to start in string
** \param token The string to match
** \return If token was found
*/
bool			bunny_read_text(const char		*str,
					ssize_t			*index,
					const char		*token);

/*!
** Increase *index while str[*index] is any kind of whitespace
** \param str The string to browse
** \param index A pointer to indicate the index where to start in string
*/
void			bunny_skip_space(const char		*str,
					 ssize_t		*index);

/*!
** Increase *index while str[*index] is a space or a tabulation
** \param str The string to browse
** \param index A pointer to indicate the index where to start in string
*/
void			bunny_inline_skip_space(const char	*str,
						ssize_t		*index);

/*!
** Check if &str[*index] is a "field", a valid C like symbol.
** Increase *index to reach the space after it if found. Return if a symbol was found.
** A valid C like symbol is a string beginning with a letter or an underscore
** and that go one with letter, underscore or number.
** \param str The string to browse
** \param index A pointer to indicate the index where to start in string
** \return If a field was found.
*/
bool			bunny_read_field(const char		*str,
					 ssize_t		*index);

/*!
** Try to read and retrieve a double.
** \param str The string to parse
** \param index Where to start in string
** \param val Where to store the double
** \return If a valid value was found.
*/
bool			bunny_read_double(const char		*str,
					  ssize_t		*index,
					  double		*val);

/*!
** Try to read and retrieve an integer.
** \param str The string to parse
** \param index Where to start in string
** \param val Where to store the integer
** \return If a valid value was found.
*/
bool			bunny_read_integer(const char		*str,
					   ssize_t		*index,
					   int			*val);

/*!
** Try to read and retrieve a C string.
**
** A C String start and end with a double quote.
** Inside a C string, the backslash token can be used to escape characters.
** This function support utf-8 characters.
** This function support hexadecimal with the following syntax: \0xHEXA.
** This function support binary with the following syntax: \0bBINARY.
** This function support octal with the following syntax: \0OCTAL.
**
** \param str The string to parse
** \param index Where to start in string
** \param out Where to store the string
** \param out_len The length of the storage space
** \return If a valid value was found.
*/
bool			bunny_read_cstring(const char		*str,
					   ssize_t		*index,
					   char			*out,
					   size_t		out_len);

bool			bunny_read_cchar(const char		*code,
					 ssize_t		*index,
					 char			*out);

/*!
** Transform the sent string into a c-string format. Turn LF into '\' and 'n',
** for example.
** \param str The string to transform.
** \param out Where the generated string will be saved. Must be free with
** bunny_free. If *out is not NULL, the string is not allocated but
** directly written into the sent buffer.
** \param siz The size of *out if not NULL, ignored in other cases.
** \return True if the string was generated.
*/
bool			bunny_write_cstring(const char		*str,
					    char		**out,
					    size_t		siz);

/*!
** Try to read and retrieve a raw string.
** A raw string is any amount of characters that end with a specific token.
**
** \param str The string to parse
** \param index Where to start in string
** \param out Where to store the string
** \param out_len The length of the storage space
** \param end_token Any token that, if encountered while browsing, end the string.
** \return If a string was retrieved.
*/
bool			bunny_read_rawstring(const char		*str,
					     ssize_t		*index,
					     char		*out,
					     size_t		out_len,
					     char		*end_token);

bool			bunny_read_value(const char		*code,
					 ssize_t		*index,
					 t_bunny_configuration	*node,
					 const char		*end_token);

/*!
** Return on which line str[index] is.
** \param str The string to test.
** \param index The index we want to know the line.
** \return The line on which str[index] is.
*/
int			bunny_which_line(const char		*str,
					 int			index);

size_t			bunny_read_until_it_is_full(int		fd,
						    void	*rd,
						    size_t	len);

# ifdef				__MINGW32__
#  pragma			pack(4)
# endif

/**
 * @doc
 * @doc-symbol t_bunny_binary_box
 * @doc-kind struct
 * @doc-module parsing
 * @doc-order 500
 * @doc-since 12
 * @doc-until latest
 * @doc-level 40
 *
 * @doc-lang en
 * @brief Describes a small binary block with a four-byte key and a payload.
 * @description t_bunny_binary_box is used by the binary box helpers. The structure contains a four-character key, the payload size, then a flexible payload area.
 * @field key Four-byte box identifier. It is not automatically NUL-terminated.
 * @field box_size Payload size in bytes.
 * @field data Beginning of the payload.
 * @see bunny_binary_box_size, bunny_read_binary_box, bunny_load_binary_box, bunny_create_binary_box
 *
 * @doc-lang fr
 * @brief Décrit un petit bloc binaire avec une clé de quatre octets et une charge utile.
 * @description t_bunny_binary_box est utilisé par les assistants de boîtes binaires. La structure contient une clé de quatre caractères, la taille de la charge utile, puis une zone flexible de données.
 * @field key Identifiant de boîte sur quatre octets. Il n'est pas automatiquement terminé par NUL.
 * @field box_size Taille de la charge utile en octets.
 * @field data Début de la charge utile.
 * @see bunny_binary_box_size, bunny_read_binary_box, bunny_load_binary_box, bunny_create_binary_box
 */
typedef struct		s_bunny_binary_box
{
  char			key[4];
  uint32_t		box_size;
  char			data[__ZERO_LENGTH__];
}			t_bunny_binary_box;

/**
 * @doc
 * @doc-symbol bunny_binary_box_size
 * @doc-kind macro
 * @doc-module parsing
 * @doc-order 510
 * @doc-since 12
 * @doc-until latest
 * @doc-level 40
 *
 * @doc-lang en
 * @brief Computes the allocation size of a binary box payload.
 * @param x Payload size in bytes.
 * @return-success The total number of bytes needed for the t_bunny_binary_box header and x bytes of payload.
 * @see t_bunny_binary_box, bunny_create_binary_box
 *
 * @doc-lang fr
 * @brief Calcule la taille d'allocation d'une charge utile de boîte binaire.
 * @param x Taille de la charge utile en octets.
 * @return-success Le nombre total d'octets nécessaires pour l'en-tête t_bunny_binary_box et x octets de charge utile.
 * @see t_bunny_binary_box, bunny_create_binary_box
 */
# define		bunny_binary_box_size(x)		\
  ((size_t)(sizeof(char[4]) + sizeof(uint32_t) + x))
# pragma		pack()

bool			bunny_test_binary_box(const void	*data,
					      off_t		offset,
					      const char	*str);

off_t			bunny_skip_binary_box(const void	*data,
					      off_t		offset,
					      off_t		maxlen);

t_bunny_binary_box	*bunny_read_binary_box(const void	*data,
					       off_t		*offset,
					       off_t		maxlen);

t_bunny_binary_box	*bunny_load_binary_box(int		fd);

t_bunny_binary_box	*bunny_create_binary_box(size_t		len);


/**
 * @doc
 * @doc-symbol t_bunny_read_whitespace
 * @doc-kind callback
 * @doc-module parsing
 * @doc-order 620
 * @doc-since 12
 * @doc-until latest
 * @doc-level 40
 *
 * @doc-lang en
 * @brief Defines the callback used to skip custom whitespace before parsing.
 * @param code The parsed string.
 * @param i The cursor to update.
 * @return-case true Parsing may continue.
 * @return-case false Parsing must fail immediately.
 * @see gl_bunny_read_whitespace
 *
 * @doc-lang fr
 * @brief Définit le callback utilisé pour sauter des blancs personnalisés avant le parsing.
 * @param code La chaîne parsée.
 * @param i Le curseur à mettre à jour.
 * @return-case true Le parsing peut continuer.
 * @return-case false Le parsing doit échouer immédiatement.
 * @see gl_bunny_read_whitespace
 */
typedef bool		(*t_bunny_read_whitespace)(const char	*code,
						   ssize_t	*i);

/**
 * @doc
 * @doc-symbol gl_bunny_read_whitespace
 * @doc-kind variable
 * @doc-module parsing
 * @doc-order 630
 * @doc-since 12
 * @doc-until latest
 * @doc-level 40
 *
 * @doc-lang en
 * @brief Stores the optional whitespace reader used by parsing helpers.
 * @description When this callback is not NULL, the public check/read helpers call it before reading their own token. This lets a parser centralize comments or custom whitespace handling.
 * @see t_bunny_read_whitespace, bunny_read_text, bunny_read_integer
 *
 * @doc-lang fr
 * @brief Stocke le lecteur optionnel de blancs utilisé par les assistants de parsing.
 * @description Lorsque ce callback n'est pas NULL, les assistants publics de check/read l'appellent avant de lire leur propre jeton. Cela permet à un parseur de centraliser la gestion des commentaires ou des blancs personnalisés.
 * @see t_bunny_read_whitespace, bunny_read_text, bunny_read_integer
 */
extern
t_bunny_read_whitespace	gl_bunny_read_whitespace;

#endif	/*		__LAPIN_PARSING_H__			*/

