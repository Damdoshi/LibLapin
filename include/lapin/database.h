/*
** Jason Brillante "Damdoshi"
** Hanged Bunny Studio 2014-2016
**
** Bibliotheque Lapin
*/

/*!
** \file database.h
** The database module is useful to talk with a MySQL database server.
** It wraps the MySQL client library.
**
** /!\ DOES NOT WORK YET /!\
**
*/

#ifndef				__LAPIN_DATABASE_H__
# define			__LAPIN_DATABASE_H__
# if				!defined(__LAPIN_H__)
#  error			You cannot include this file directly.
# endif
// # include			<mysql/mysql.h>

/*!
** The t_bunny_database structure contains datas
** that were used to open the communication with the
** database server.
** - The first field is private and should not be modified.
** - The url is where your database is. It can be an IP or "localhost".
** - The login and password fields are the login and password
**   that were used to connect to the database.
** - The database field is the database chosen inside the
** database system, the one you will browse and edit.
*/
typedef struct			s_bunny_database
{
  const char			_private[sizeof(size_t)];
  const char * const		url;
  const char * const		login;
  const char * const		password;
  const char * const		database;
  size_t			response_length;
}				t_bunny_database;

/*!
** The t_bunny_database_iterator is the structure that
** will be used to browse the results of a database query.
** The first field is the index that is currently browse.
** The nbr_rows field is maximum index + 1.
** The data is the retrieved from database data.
*/
typedef struct			s_bunny_database_iterator
{
  const int			index;
  const int			nbr_rows;
}				t_bunny_database_iterator;

/*!
** Open a communicaton with the database server.
** \param url Where is the database? Can be a domain, an IP or "localhost".
** \param login The login to send to the database server.
** \param password The password to use with the database server.
** \return A structure gathering these informations on success, NULL on error.
*/
t_bunny_database		*bunny_new_database(const char				*url,
						    const char				*login,
						    const char				*password);

/*!
** Disconnect from the sent database server.
** \param db The database server to disconnect from.
*/
void				bunny_delete_database(t_bunny_database			*db);

/*!
** Select a specific database on the database server for future queries.
** \param db The database server.
** \param db_name The name of the database to use.
** \return True if everything went well. False on the other case.
*/
bool				bunny_database_select(t_bunny_database			*db,
						      const char			*db_name);

/*!
** Send a SQL query to the database server. It could be any MySQL valid SQL request.
** \param db The database server.
** \param request An SQL request.
** \return True if everything went well. False on the other case.
*/
bool				bunny_database_query(t_bunny_database			*db,
						     const char				*request);

/*!
** Get the first returned by the database server value. (We assume that you sent a SELECT
** query with bunny_database_query before).
**
** This is the way:
**
** bunny_databas_query(db, ...);
** for (it = bunny_database_first(db);
**      it != bunny_database_end(db);
**      it = bunny_database_next(db, it))
** {}
**
** \param db The database server.
** \return An iterator to the first value.
*/
t_bunny_database_iterator	*bunny_database_first(t_bunny_database			*db);

/*!
** Get the next returned by the database server value.
** \param db The database server.
** \param it The current value, that was returned by bunny_database_first or bunny_database_next.
** \return An iterator to the next value.
*/
t_bunny_database_iterator	*bunny_database_next(t_bunny_database			*db,
						     const t_bunny_database_iterator	*it);

/*!
** Return the last iterator.
** \param db The database server.
** \return THe last iterator.
*/
t_bunny_database_iterator	*bunny_database_end(t_bunny_database			*db);

/*!
**  Get the value that is associated with the sent name.
** \param db The database server.
** \param it An iterator to a database value
** \param name The name of the field you want to fetch
** \return The requested value or NULL on error.
*/
const char			*bunny_database_get(t_bunny_database			*db,
						    const t_bunny_database_iterator	*it,
						    const char				*name);

#endif	/*			__LAPIN_DATABASE_H__					*/
