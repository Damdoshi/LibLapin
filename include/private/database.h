/*
** Jason Brillante "Damdoshi"
** Hanged Bunny Studio 2014-2016
**
**
** Bibliotheque Lapin
*/

#ifndef				__LAPIN_PRIVATE_DATABASE_H__
# define			__LAPIN_PRIVATE_DATABASE_H__

struct				bunny_database
{
  char				_private[sizeof(size_t)]; // things
  char				*url;
  char				*login;
  char				*password;
  char				*database;
  size_t			response_length;
};

struct				bunny_database_iterator
{
  int				index;
  int				nbr_rows;
  // hbs::Dictionnary<size_t>	*dic;
};


#endif	/*			__LAPIN_PRIVATE_DATABASE_H__	*/
