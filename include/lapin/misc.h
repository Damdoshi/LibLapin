/*
** Jason Brillante "Damdoshi"
** Hanged Bunny Studio 2014-2019
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

/**
 * @doc
 * @doc-symbol misc
 * @doc-kind module
 * @doc-module misc
 * @doc-order 0
 * @doc-since 0
 * @doc-until latest
 * @doc-level beginner
 *
 * @doc-lang en
 * @brief Groups small utility helpers used throughout LibLapin programs.
 * @description The misc module contains file helpers, byte/string utilities, base64 helpers, simple movement helpers, resource-manager inspection functions and a few convenience macros.
 * @header lapin/misc.h
 *
 * @doc-lang fr
 * @brief Regroupe de petits utilitaires utilisés dans les programmes LibLapin.
 * @description Le module misc contient des aides pour les fichiers, les octets et chaînes, la base64, les déplacements simples, l'inspection du gestionnaire de ressources et quelques macros pratiques.
 * @header lapin/misc.h
 */
# define			LITTERAL(fd, str)			write((fd), str "\n", sizeof(str "\n"))

# define			__TOSTRING(a)				#a

/**
 * @doc
 * @doc-symbol STRINGIFY
 * @doc-kind macro
 * @doc-module misc
 * @doc-order 260
 * @doc-since 0
 * @doc-until latest
 * @doc-level beginner
 *
 * @doc-lang en
 * @brief Converts a preprocessor token to a string literal after expansion.
 * @param a Token or macro expression to stringify.
 * @return-success Expands to a C string literal.
 * @see NBRCELL
 *
 * @doc-lang fr
 * @brief Convertit un jeton du préprocesseur en littéral chaîne après expansion.
 * @param a Jeton ou expression macro à transformer en chaîne.
 * @return-success Produit un littéral chaîne C.
 * @see NBRCELL
 */
# define			STRINGIFY(a)				__TOSTRING(a)

/**
 * @doc
 * @doc-symbol NBRCELL
 * @doc-kind macro
 * @doc-module misc
 * @doc-order 280
 * @doc-since 0
 * @doc-until latest
 * @doc-level beginner
 *
 * @doc-lang en
 * @brief Counts the number of elements in a fixed-size C array.
 * @param array Fixed-size array expression.
 * @return-success Expands to the array cell count as an int.
 * @description This macro uses sizeof and must not be used on a pointer.
 * @see STRINGIFY
 *
 * @doc-lang fr
 * @brief Compte le nombre d'éléments d'un tableau C de taille fixe.
 * @param array Expression de tableau de taille fixe.
 * @return-success Produit le nombre de cases du tableau sous forme de int.
 * @description Cette macro utilise sizeof et ne doit pas être utilisée sur un pointeur.
 * @see STRINGIFY
 */
# define			NBRCELL(array)				((int)(sizeof(array) / sizeof(array[0])))


/**
 * @doc
 * @doc-symbol t_bunny_string_couple
 * @doc-kind struct
 * @doc-module misc
 * @doc-order 20
 * @doc-since 12
 * @doc-until latest
 * @doc-level advanced
 *
 * @doc-lang en
 * @brief Stores a pair of string pointers.
 * @field first First string of the pair.
 * @field second Second string of the pair.
 * @see gl_empty_string_couple, bunny_search_string_couple
 *
 * @doc-lang fr
 * @brief Stocke une paire de pointeurs vers chaînes.
 * @field first Première chaîne de la paire.
 * @field second Seconde chaîne de la paire.
 * @see gl_empty_string_couple, bunny_search_string_couple
 */
typedef struct			s_bunny_string_couple
{
  const char			*first;
  const char			*second;
}				t_bunny_string_couple;

/**
 * @doc
 * @doc-symbol gl_empty_string_couple
 * @doc-kind variable
 * @doc-module misc
 * @doc-order 30
 * @doc-since 12
 * @doc-until latest
 * @doc-level advanced
 *
 * @doc-lang en
 * @brief Empty string couple sentinel.
 * @description Both fields are NULL. It can be used as a terminator or default value for arrays of t_bunny_string_couple.
 * @see t_bunny_string_couple, bunny_search_string_couple
 *
 * @doc-lang fr
 * @brief Sentinelle de couple de chaînes vide.
 * @description Ses deux champs valent NULL. Elle peut servir de terminateur ou de valeur par défaut pour des tableaux de t_bunny_string_couple.
 * @see t_bunny_string_couple, bunny_search_string_couple
 */
extern const t_bunny_string_couple gl_empty_string_couple;
t_bunny_string_couple		*bunny_search_string_couple(t_bunny_string_couple *couple,
							    size_t	len,
							    const char	*a,
							    const char	*b);

/*!
** Write a litteral string (defined in code, with two double quotes) on stdout.
** \param str The string litteral to write
*/

/**
 * @doc
 * @doc-symbol bunny_printl
 * @doc-kind macro
 * @doc-module misc
 * @doc-order 300
 * @doc-since 0
 * @doc-until latest
 * @doc-level beginner
 *
 * @doc-lang en
 * @brief Writes a string literal followed by a newline to standard output.
 * @param str String literal to write.
 * @see bunny_printlerr, bunny_trace
 *
 * @doc-lang fr
 * @brief Écrit un littéral chaîne suivi d'un retour à la ligne sur la sortie standard.
 * @param str Littéral chaîne à écrire.
 * @see bunny_printlerr, bunny_trace
 */
# define			bunny_printl(str)			LITTERAL(1,  str)

/*!
** Write a litteral string (defined in code, with two double quotes) on stderr.
** \param str The string litteral to write
*/

/**
 * @doc
 * @doc-symbol bunny_printlerr
 * @doc-kind macro
 * @doc-module misc
 * @doc-order 320
 * @doc-since 0
 * @doc-until latest
 * @doc-level beginner
 *
 * @doc-lang en
 * @brief Writes a string literal followed by a newline to standard error.
 * @param str String literal to write.
 * @see bunny_printl, bunny_trace
 *
 * @doc-lang fr
 * @brief Écrit un littéral chaîne suivi d'un retour à la ligne sur la sortie d'erreur.
 * @param str Littéral chaîne à écrire.
 * @see bunny_printl, bunny_trace
 */
# define			bunny_printlerr(str)			LITTERAL(2,  str)

/*!
** Print the current file and line in code. Useful for debugging.
*/

/**
 * @doc
 * @doc-symbol bunny_trace
 * @doc-kind macro
 * @doc-module misc
 * @doc-order 340
 * @doc-since 0
 * @doc-until latest
 * @doc-level beginner
 *
 * @doc-lang en
 * @brief Prints the current function, file and line for quick debugging.
 * @description This macro is intentionally simple and writes directly with printf.
 * @see bunny_printl, bunny_printlerr
 *
 * @doc-lang fr
 * @brief Affiche la fonction, le fichier et la ligne courants pour du debug rapide.
 * @description Cette macro est volontairement simple et écrit directement avec printf.
 * @see bunny_printl, bunny_printlerr
 */
# define			bunny_trace()				printf("%s-%d:%d\n", __PRETTY_FUNCTION__, __FILE__, __LINE__)

/*!
**
*/
int				bunny_vsnprintf(char			*buffer,
						size_t			buflen,
						va_list			lst);
int				bunny_snprintf(char			*buffer,
					       size_t			buflen,
					       ...);

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

bool				bunny_read_base64(const char		*data,
						  ssize_t		*i,
						  void			**out,
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

size_t				bunny_split_len(const char * const	*tab);

char				*bunny_stick(const char * const		*tab,
					     const char			*glue,
					     bool			no_last);

/*!
** Some of you may find const char * const * too long to write and prefer this
** typedef which is shorter, but also occulting.
*/

/**
 * @doc
 * @doc-symbol t_bunny_split
 * @doc-kind type
 * @doc-module misc
 * @doc-order 240
 * @doc-since 0
 * @doc-until latest
 * @doc-level beginner
 *
 * @doc-lang en
 * @brief Short alias for the NULL-terminated array returned by bunny_split.
 * @description The pointed strings and the array itself must be released with bunny_delete_split when they come from bunny_split.
 * @see bunny_split, bunny_delete_split, bunny_split_len
 *
 * @doc-lang fr
 * @brief Alias court pour le tableau terminé par NULL renvoyé par bunny_split.
 * @description Les chaînes pointées et le tableau lui-même doivent être libérés avec bunny_delete_split lorsqu'ils viennent de bunny_split.
 * @see bunny_split, bunny_delete_split, bunny_split_len
 */
typedef const char * const *	t_bunny_split;

void				bunny_randomize(void			*data,
						size_t			len);

void				bunny_shuffle(void			*data,
					      size_t			datalen,
					      size_t			nmemb);

void				bunny_memswap(void			*a,
					      void			*b,
					      size_t			datalen);

bool				bunny_is_directory(const char		*file);
bool				bunny_file_exists(const char		*file);

bool				bunny_join_binary_directory(const char	*argv0);

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

double				bunny_clamp(double			value,
					    double			min,
					    double			max);

double				bunny_rclamp(double			value,
					     double			min,
					     double			max);

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

/**
 * @doc
 * @doc-symbol bunny_big_buffer
 * @doc-kind variable
 * @doc-module misc
 * @doc-order 400
 * @doc-since 0
 * @doc-until latest
 * @doc-level advanced
 *
 * @doc-lang en
 * @brief Shared 16 MiB scratch buffer.
 * @description Some legacy APIs use this buffer for large temporary data. Its content is volatile and can be overwritten by unrelated LibLapin calls.
 *
 * @doc-lang fr
 * @brief Tampon temporaire partagé de 16 Mio.
 * @description Certaines anciennes API utilisent ce tampon pour de grosses données temporaires. Son contenu est volatil et peut être écrasé par d'autres appels LibLapin.
 */
extern char			bunny_big_buffer[16 * 1024 * 1024];

# if				defined(__STDC_VERSION__) && __STDC_VERSION__ == 201112L

/**
 * @doc
 * @doc-symbol bunny_typename
 * @doc-kind macro
 * @doc-module misc
 * @doc-order 420
 * @doc-since 12
 * @doc-until latest
 * @doc-level advanced
 *
 * @doc-lang en
 * @brief Returns a string describing the C11 generic type of an expression.
 * @param x Expression whose type is inspected.
 * @return-success Expands to a string literal naming the recognized type, or $L"other"@.
 * @see bunny_typef
 *
 * @doc-lang fr
 * @brief Renvoie une chaîne décrivant le type C11 générique d'une expression.
 * @param x Expression dont le type est inspecté.
 * @return-success Produit un littéral chaîne nommant le type reconnu, ou $L"other"@.
 * @see bunny_typef
 */
#  define			bunny_typename(x)			\
  _Generic((x),								\
	   _Bool: "bool",						\
	   unsigned char: "unsigned char",				\
	   char: "char",						\
	   short int: "short int",					\
	   unsigned short int: "unsigned short int",			\
	   int: "int",							\
	   unsigned int: "unsigned int",				\
	   long int: "long int",					\
	   unsigned long int: "unsigned long int",			\
	   long long int: "long long int",				\
	   unsigned long long int: "unsigned long long int",		\
	   float: "float",						\
	   double: "double",						\
	   long double: "long double",					\
	   char *: "char*",						\
	   void *: "void*",						\
	   int *: "int*",						\
	   char **: "char**",						\
	   void **: "void**",						\
	   int **: "int**",						\
  default: "other")


/**
 * @doc
 * @doc-symbol bunny_typef
 * @doc-kind macro
 * @doc-module misc
 * @doc-order 430
 * @doc-since 12
 * @doc-until latest
 * @doc-level advanced
 *
 * @doc-lang en
 * @brief Returns a printf-like format string for the C11 generic type of an expression.
 * @param x Expression whose type is inspected.
 * @return-success Expands to a format string for recognized scalar or pointer types.
 * @see bunny_typename
 *
 * @doc-lang fr
 * @brief Renvoie un format de type printf pour le type C11 générique d'une expression.
 * @param x Expression dont le type est inspecté.
 * @return-success Produit une chaîne de format pour les types scalaires ou pointeurs reconnus.
 * @see bunny_typename
 */
#  define			bunny_typef(x)				\
  _Generic((x),								\
	   _Bool: "%d",							\
	   unsigned char: "%ux",					\
	   char: "%c",							\
	   short int: "%d",						\
	   unsigned short int: "%ud",					\
	   int: "%d",							\
	   unsigned int: "%u",						\
	   long int: "%ld",						\
	   unsigned long int: "%lud",					\
	   long long int: "%Ld",					\
	   unsigned long long int: "%Lu",				\
	   float: "%f",							\
	   double: "%f",						\
	   long double: "%lf",						\
	   char *: "%s",						\
	   void *: "(void*)%p",						\
	   int *: "(int*)%p",						\
	   char *: "(char**)%p",					\
	   void *: "(void**)%p",					\
	   int *: "(int**)%p",						\
  default: "%%other")
# endif


/**
 * @doc
 * @doc-symbol bunny_zero
 * @doc-kind macro
 * @doc-module misc
 * @doc-order 440
 * @doc-since 12
 * @doc-until latest
 * @doc-level beginner
 *
 * @doc-lang en
 * @brief Clears the object pointed to by a pointer with zero bytes.
 * @param a Pointer to the object to clear.
 * @description This macro clears sizeof(*a) bytes and must receive a valid pointer expression.
 * @see bunny_erase, bunny_erase_and_free
 *
 * @doc-lang fr
 * @brief Remplit de zéro l'objet pointé par un pointeur.
 * @param a Pointeur vers l'objet à effacer.
 * @description Cette macro efface sizeof(*a) octets et doit recevoir une expression de pointeur valide.
 * @see bunny_erase, bunny_erase_and_free
 */
# define			bunny_zero(a)				\
  memset((void*)a, 0, sizeof(*a))

/**
 * @doc
 * @doc-symbol bunny_erase
 * @doc-kind macro
 * @doc-module misc
 * @doc-order 450
 * @doc-since 12
 * @doc-until latest
 * @doc-level advanced
 *
 * @doc-lang en
 * @brief Clears the memory range between two pointers with zero bytes.
 * @param a First boundary pointer.
 * @param b Second boundary pointer.
 * @description The two pointers must delimit a valid writable range in the same object or allocation.
 * @see bunny_zero, bunny_erase_and_free
 *
 * @doc-lang fr
 * @brief Remplit de zéro l'intervalle mémoire situé entre deux pointeurs.
 * @param a Premier pointeur de borne.
 * @param b Deuxième pointeur de borne.
 * @description Les deux pointeurs doivent délimiter une zone accessible en écriture dans le même objet ou la même allocation.
 * @see bunny_zero, bunny_erase_and_free
 */
# define			bunny_erase(a, b)			\
  memset((void*)((b) > (a) ? (a) : (b)), 0, (b) > (a) ? (b) - (a) : (a) - (b))

void				bunny_erase_and_free(void		*ptr,
						     size_t		len);

#endif	/*			__LAPIN_MISC_H__			*/

