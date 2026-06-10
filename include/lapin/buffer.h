/*
** Jason Brillante "Damdoshi"
** Hanged Bunny Studio 2014-2016
**
** Bibliotheque Lapin
*/


/**
 * @doc
 * @doc-symbol buffer
 * @doc-kind module
 * @doc-module buffer
 * @doc-order 0
 * @doc-since 0
 * @doc-until latest
 * @doc-level 0
 *
 * @doc-lang en
 * @brief Describes the common root of graphic buffers.
 * @description The buffer module exposes the small structures shared by windows, pictures, pixelarrays and other drawable objects. t_bunny_buffer is intentionally placed as the first field of several graphic structures so that those objects can be passed to functions expecting a buffer when the API documents that behaviour.
 * @header lapin/buffer.h
 *
 * @doc-lang fr
 * @brief Décrit la racine commune des tampons graphiques.
 * @description Le module buffer expose les petites structures partagées par les fenêtres, les pictures, les pixelarrays et les autres objets affichables. t_bunny_buffer est volontairement placé comme premier champ de plusieurs structures graphiques afin que ces objets puissent être transmis aux fonctions attendant un buffer lorsque l'API le documente.
 * @header lapin/buffer.h
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
# include			<sys/types.h>

/**
 * @doc
 * @doc-symbol BUNNY_EXTENDED_DATA_LENGTH
 * @doc-kind macro
 * @doc-module buffer
 * @doc-order 80
 * @doc-since 0
 * @doc-until latest
 * @doc-level 30
 *
 * @doc-lang en
 * @brief Defines how many user data slots are available in t_bunny_buffer.
 * @description Define BUNNY_EXTENDED_DATA_LENGTH before including lapin.h to change the number of t_bunny_extended_data entries embedded in each t_bunny_buffer. The default value is 4.
 * @see t_bunny_buffer, t_bunny_extended_data
 *
 * @doc-lang fr
 * @brief Définit le nombre d'emplacements de données utilisateur disponibles dans t_bunny_buffer.
 * @description Définissez BUNNY_EXTENDED_DATA_LENGTH avant d'inclure lapin.h pour changer le nombre d'entrées t_bunny_extended_data embarquées dans chaque t_bunny_buffer. La valeur par défaut est 4.
 * @see t_bunny_buffer, t_bunny_extended_data
 */
# ifndef			BUNNY_EXTENDED_DATA_LENGTH
#  define			BUNNY_EXTENDED_DATA_LENGTH		4
# endif


/**
 * @doc
 * @doc-symbol t_bunny_extended_data
 * @doc-kind union
 * @doc-module buffer
 * @doc-order 90
 * @doc-since 0
 * @doc-until latest
 * @doc-level 20
 *
 * @doc-lang en
 * @brief Stores one user-defined value inside a t_bunny_buffer.
 * @description t_bunny_extended_data is a convenience union used by the data array of t_bunny_buffer. It lets user code attach a small pointer-sized value, such as a position, a configuration pointer, a string pointer or a numeric value, directly to a graphic object.
 * @field space Raw storage with the size of a pointer.
 * @field position Integer 2D position storage.
 * @field configuration Configuration node pointer storage.
 * @field string String pointer storage.
 * @field data Generic pointer storage.
 * @field int_data Integer storage.
 * @field float_data Floating-point storage.
 * @see t_bunny_buffer, BUNNY_EXTENDED_DATA_LENGTH
 *
 * @doc-lang fr
 * @brief Stocke une valeur définie par l'utilisateur dans un t_bunny_buffer.
 * @description t_bunny_extended_data est une union de confort utilisée par le tableau data de t_bunny_buffer. Elle permet au code utilisateur d'attacher directement à un objet graphique une petite valeur de taille pointeur, comme une position, un pointeur de configuration, une chaîne ou une valeur numérique.
 * @field space Stockage brut de la taille d'un pointeur.
 * @field position Stockage d'une position 2D entière.
 * @field configuration Stockage d'un pointeur vers un noeud de configuration.
 * @field string Stockage d'un pointeur vers une chaîne.
 * @field data Stockage d'un pointeur générique.
 * @field int_data Stockage entier.
 * @field float_data Stockage flottant.
 * @see t_bunny_buffer, BUNNY_EXTENDED_DATA_LENGTH
 */
typedef union			s_bunny_extended_data
{
  char				space[sizeof(void*)];
  t_bunny_position		position;
  t_bunny_configuration		*configuration;
  const char			*string;
  void				*data;
  int				int_data;
  float				float_data;
}				t_bunny_extended_data;


/**
 * @doc
 * @doc-symbol t_bunny_buffer
 * @doc-kind struct
 * @doc-module buffer
 * @doc-order 100
 * @doc-since 0
 * @doc-until latest
 * @doc-level 0
 *
 * @doc-lang en
 * @brief Describes the common header of a 2D graphic buffer.
 * @description t_bunny_buffer stores the size of a graphic space and private backend information. It is used as a root structure by several other LibLapin types, in a style similar to simple C inheritance.
 * @description User code may read width, height and data. The _private field belongs to LibLapin and must not be modified.
 * @field _private Private LibLapin storage. Do not read or write it.
 * @field width Width of the buffer in pixels.
 * @field height Height of the buffer in pixels.
 * @field data User data slots associated with the buffer.
 * @see t_bunny_window, t_bunny_clipable, t_bunny_picture, t_bunny_pixelarray, t_bunny_extended_data
 *
 * @doc-lang fr
 * @brief Décrit l'en-tête commun d'un tampon graphique 2D.
 * @description t_bunny_buffer stocke la taille d'un espace graphique et des informations privées du backend. Il sert de structure racine à plusieurs autres types de la LibLapin, dans un style proche d'un héritage simple en C.
 * @description Le code utilisateur peut lire width, height et data. Le champ _private appartient à la LibLapin et ne doit pas être modifié.
 * @field _private Stockage privé de la LibLapin. Ne le lisez pas et ne l'écrivez pas.
 * @field width Largeur du buffer en pixels.
 * @field height Hauteur du buffer en pixels.
 * @field data Emplacements de données utilisateur associés au buffer.
 * @see t_bunny_window, t_bunny_clipable, t_bunny_picture, t_bunny_pixelarray, t_bunny_extended_data
 */
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
  const size_t			_private[5];
  ssize_t			width;
  ssize_t			height;
  t_bunny_extended_data		data[BUNNY_EXTENDED_DATA_LENGTH];
}				t_bunny_buffer;

#endif	/*			__LAPIN_BUFFER_H__		*/
