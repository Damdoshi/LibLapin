/*
** Jason Brillante "Damdoshi"
** Hanged Bunny Studio 2014-2016
**
** Bibliotheque Lapin
*/

/*!
** \file misc.h
** Utilities
*/

#ifndef				__LAPIN_MISC_H__
# define			__LAPIN_MISC_H__
# if				!defined(__LAPIN_H__)
#  error			You cannot include this file directly.
# endif
# include			<unistd.h>
# include			<stdio.h>
# define			LITTERAL(fd, str)			write((fd), str "\n", sizeof(str "\n"))

# define			__TOSTRING(a)				#a
# define			STRINGIFY(a)				__TOSTRING(a)
# define			NBRCELL(array)				((int)(sizeof(array) / sizeof(array[0])))

/*!
** Write a litteral string (defined in code, with two double quotes) on stdout.
** \param str The string litteral to write
*/
# define			bunny_printl(str)			LITTERAL(1,  str)

/*!
** Write a litteral string (defined in code, with two double quotes) on stderr.
** \param str The string litteral to write
*/
# define			bunny_printlerr(str)			LITTERAL(2,  str)

/*!
** Print the current file and line in code. Useful for debugging.
*/
# define			bunny_trace()				printf("%s-%d:%d\n", __PRETTY_FUNCTION__, __FILE__, __LINE__)

/*!
** Load an entire file.
** The file is stored in the bunny ressource manager, so loading the same
** file multiple times won't load it several times. To prevent this behaviour,
** you can use the bunny_make_file_unique function.
** \param file The file name
** \param data A pointer to the content of the file (this param is an output)
** \param size A pointer to the size of the file (this param is an output)
** If size is NULL, then an additionnal '\0' is set at the end of the data.
** \return The size of the file if everything went well, else -1
**
** Note that data and size are only changed if everything went well.
*/
ssize_t				bunny_load_file(const char		*file,
						void			**data,
						size_t			*size);

/*!
** Save the sent data into a file.
** \param file The destination file
** \param data The data to save
** \param len The length of the data
** \return True if everything went well, false instead.
*/
bool				bunny_save_file(const char		*file,
						const void		*data,
						size_t			len);

/*!
** When you load a file with bunny_load_file, it is stored inside a ressource
** manager to prevent loading several times the same file.
** If you need to force the duplication of a file, call the following function
** with the loaded data.
** \param data The data that will turn unique
** \param len The size of the data that will be turn unique
** \return The data turned unique. It is actually a copy of the sent data.
*/
void				*bunny_make_file_unique(const char	*file,
							const void	*data,
							size_t		len);

/*!
** Delete a loaded file. Mandatory for loaded file inside the ressource manager,
** but can be used on other too, a simple bunny_free/free will be performed.
** \param data The file to delete.
** \param file The file that was loaded. Mandatory for a managed ressource.
*/
void				bunny_delete_file(void			*data,
						  const char		*file);

/*!
** Compute the operation sent as first parameter. Supported operators are:
** +, -, *, /, %, >, <, >=, <=, !=, ==, ?: and () (not the function call but
** the priority modifier.
** Support doubles and integers and variables. You can use '.' to go inside a
** variable.
** \param operation The operation to compute
** \param env The variable environment
** \return The result or nan("") on error.
*/
double				bunny_evaluate(const char		*operation,
					       t_bunny_configuration	*env);

/*!
** Encode using base64 algorithm the sent data of size len.
** Store the memory space used address at *out or use the one given directly.
** Store the size of the output in *outlen.
** The output size is up to 4 * (len + 2) / 3.
**
** \param data The data to transform.
** \param len The length of the data to transform.
** \param out If *out is NULL, then the function will allocate a memory
** space wide enough with bunny_malloc and store its address in *out.
** If *out is not NULL, then it may allocate, depending on the size sent
** in *outlen being sufficient or not.
** \param outlen The size of the sent buffer in *out, or any space where
** to store the size of the function output. Will be overwritten if
** the function is successful. NULL may be sent if you don't want to
** retrieve the size.
** \return True if the function was successful.
*/
bool				bunny_base64_encode(const void		*data,
						    size_t		len,
						    char		**out,
						    size_t		*outlen);

/*!
** Decode using base64 algorithm the sent data of size len.
** Store the memory space used address at *out or use the one given directly.
** Store the size of the output in *outlen.
** The output size is up to 3 * len / 4.
**
** \param data The data to transform.
** \param len The length of the data to transform.
** \param out If *out is NULL, then the function will allocate a memory
** space wide enough with bunny_malloc and store its address in *out.
** If *out is not NULL, then it may allocate, depending on the size sent
** in *outlen being sufficient or not.
** \param outlen The size of the sent buffer in *out, or any space where
** to store the size of the function output. Will be overwritten if the function
** is successful. NULL may be sent if you don't want to retrieve the size.
** \return True if the functon was successful.
*/
bool				bunny_base64_decode(const char		*data,
						    size_t		len,
						    void		**out,
						    size_t		*outlen);

/*!
** Check if the sent data is valid as base64 encoded data.
** \param data The data to check.
** \param len The length of the data.
** \return True if the data is valid (compose of [A-Za-z0-9+/]+[=]* and
** with coherent size.
*/
bool				bunny_base64_check(const char		*data,
						   size_t		len);

/*!
** Split the given string accordingly to sent tokens.
** For example:
** const char tok[3] = {",", "==", NULL};
**
** bunny_split("a, b == c", &tok[0], false);
** Will return "a", " b" and " c".
**
** The "aggregate" parameter is useful to ignore several following tokens
** For example:
** const char tok[2] = {" ", NULL};
**
** bunny_split("a b c  d", &tok[0], false);
** Will return "a", "b", "c", "" and "d".
**
** While:
** bunny_split("a b c  d", &tok[0], true);
** Will return "a", "b", "c" and "d".
**
** Pay attention with the order in tokens: the priority is the order of the
** tokens themselves! The more they are close to the beginning, the higher
** they are.
**
** \param str The string to split. bunny_split only handle less than 4096 words.
** \param tokens An array of string that are separator for the string to split/
**        It must be NULL terminated. There can't be more than 31 tokens.
** \param aggregate Can separator be stacked or not
** \return A NULL terminated string array. NULL on error.
*/
const char * const		*bunny_split(const char			*str,
					     const char			**tokens,
					     bool			aggregate);

/*!
** Free the value returned by bunny_split and every string inside.
** \param tab The array to free.
*/
void				bunny_delete_split(const char * const	*tab);

/*!
** Some of you may find const char * const * too long to write and prefer this
** typedef which is shorter, but also occulting.
*/
typedef const char * const *	t_bunny_split;

/*!
** Duplicate the chunk of size len pointed by ptr
** \param ptr The address of the chunk to duplicate
** \param len The size of the chunk to duplicate
**
*/
void				*bunny_memdup(const void		*ptr,
					      size_t			len);

void				bunny_randomize(void			*data,
						size_t			len);

/*!
** Swap two pointers of any type
** \param a The pointer to swap with b
** \param b The pointer to swap with a
*/
void				bunny_swap(void				**a,
					   void				**b);

/*!
** A nice curve for leveling.
** \param lvl The current_level of your character
** \return The experience required to achieve this level. You may multiply it
** by 1000 to have more granularity.
*/
int				bunny_next_level_experience(int		lvl);

/*!
** Create a smooth move between two points. Used by bunny_stabilize_headtrack
** and quite useful for camera on tile based graphics.
** \param target The coordinates the second point want to rejoin
** \param current The coordinates of the current position, they will be edited.
** \param speed A value between 0 and 1 that is the distance
** the point will travel at each call. This value is relative to
** the distance in both points.
*/
void				bunny_smooth_move(const t_bunny_position *target,
						  t_bunny_position	*current,
						  double		speed);

/*
**
**
*/
bool				bunny_reach(double			*value,
					    double			limit,
					    double			step);

/*
** Self evaluation.
** Test public/privates structures consistancy.
** List all managed ressource.
*/
void				bunny_consistancy(void);
void				bunny_managed_ressource(void);
void				bunny_set_ressource_management(bool	enabled);

/*!
** May be useful for wide trashable datas. Some functions use it, it is always
** written in their description when they do.
*/
extern char			bunny_big_buffer[16 * 1024 * 1024];

#endif	/*			__LAPIN_MISC_H__			*/

