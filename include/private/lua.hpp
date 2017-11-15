/*
** Jason Brillante "Damdoshi"
** Hanged Bunny Studio 2014-2016
**
**
** Bibliotheque Lapin
*/

#ifndef			__LAPIN_PRIVATE_LUA_HPP__
# define		__LAPIN_PRIVATE_LUA_HPP__

t_bunny_configuration	*_bunny_read_lua(const char			*code,
					  t_bunny_configuration		*config);
Decision		lua_read_array(const char			*code,
					ssize_t				&i,
					SmallConf			&conf,
					SmallConf			&root);
Decision		lua_read_array_node(const char			*code,
					     ssize_t			&i,
					     SmallConf			&conf,
					     SmallConf			&root);
Decision		lua_read_field(const char			*code,
					ssize_t				&i,
					SmallConf			&conf,
					SmallConf			&root);
Decision		lua_read_inside_array(const char		*code,
					       ssize_t			&i,
					       SmallConf		&conf,
					       SmallConf		&root);
Decision		lua_read_inside_scope(const char		*code,
					       ssize_t			&i,
					       SmallConf		&conf,
					       SmallConf		&root);
Decision		lua_read_scope(const char			*code,
					ssize_t				&i,
					SmallConf			&conf,
					SmallConf			&root);
void			lua_read_separator(const char			*code,
					    ssize_t			&i);
char			*_bunny_write_lua(const t_bunny_configuration	*config);

#endif	/*		__LAPIN_PRIVATE_LUA_HPP__		*/
