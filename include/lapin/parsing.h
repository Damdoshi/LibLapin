/*
** Jason Brillante "Damdoshi"
** Hanged Bunny Studio 2014-2016
**
** Bibliotheque Lapin
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

/*!
** Return on which line str[index] is.
** \param str The string to test.
** \param index The index we want to know the line.
** \return The line on which str[index] is.
*/
int			bunny_which_line(const char		*str,
					 int			index);

#endif	/*		__LAPIN_PARSING_H__			*/

