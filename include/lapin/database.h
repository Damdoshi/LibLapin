/*
** Jason Brillante "Damdoshi"
** Hanged Bunny Studio 2014-2016
**
** Bibliotheque Lapin
*/

/*!
** \file database.h

*/

#ifndef				__LAPIN_DATABASE_H__
# define			__LAPIN_DATABASE_H__
# if				!defined(__LAPIN_H__)
#  error			You cannot include this file directly.
# endif
# include			<mysql.h>

typedef struct			s_bunny_database
{
  char				_private[sizeof(size_t)];
  const char * const		url;
  const char * const		login;
  const char * const		password;
  const char * const		database;
  size_t			response_length;
}				t_bunny_database;

typedef struct			s_bunny_database_iterator
{
  const int			index;
  const int			nbr_rows;
}				t_bunny_database_iterator;

t_bunny_database		*bunny_new_database(const char				*url,
						    const char				*login,
						    const char				*password);
void				bunny_delete_database(t_bunny_database			*db);

bool				bunny_database_select(t_bunny_database			*db,
						      const char			*db_name);
bool				bunny_database_query(t_bunny_database			*db,
						     const char				*request);

t_bunny_database_iterator	*bunny_database_first(t_bunny_database			*db);
t_bunny_database_iterator	*bunny_database_next(t_bunny_database			*db,
						     const t_bunny_database_iterator	*it);
t_bunny_database_iterator	*bunny_database_end(t_bunny_database			*db);

const char			*bunny_database_get(t_bunny_database			*db,
						    const t_bunny_database_iterator	*it,
						    const char				*name);

#endif	/*			__LAPIN_DATABASE_H__					*/
