/*
** Jason Brillante "Damdoshi"
** Hanged Bunny Studio 2014-2020
**
** Bibliotheque Lapin
*/

#ifndef			__LAPIN_CONFIGURATION_HPP__
# define		__LAPIN_CONFIGURATION_HPP__
# ifndef		BUNNY_COMPILATION // Indicates that the current built is not the one of the bunny library

inline bool		bunny_configuration_setf(t_bunny_configuration		*cnf,
						 const t_bunny_configuration	*data,
						 const std::string		&pattern,
						 ...)
{
  va_list		lst;

  va_start(lst, pattern);
  return (bunny_configuration_vsetf_node(cnf, data, pattern.c_str(), lst));
}

inline bool		bunny_configuration_setf(t_bunny_configuration		*cnf,
						 const std::string		&data,
						 const std::string		&pattern,
						 ...)
{
  va_list		lst;

  va_start(lst, pattern);
  return (bunny_configuration_vsetf_string(cnf, data.c_str(), pattern.c_str(), lst));
}

inline bool		bunny_configuration_setf(t_bunny_configuration		*cnf,
						 int				data,
						 const std::string		&pattern,
						 ...)
{
  va_list		lst;

  va_start(lst, pattern);
  return (bunny_configuration_vsetf_int(cnf, data, pattern.c_str(), lst));
}

inline bool		bunny_configuration_setf(t_bunny_configuration		*cnf,
						 double				data,
						 const std::string		&pattern,
						 ...)
{
  va_list		lst;

  va_start(lst, pattern);
  return (bunny_configuration_vsetf_double(cnf, data, pattern.c_str(), lst));
}

inline bool		bunny_configuration_getf(t_bunny_configuration		*cnf,
						 t_bunny_configuration		**data,
						 const std::string		&pattern,
						 ...)
{
  va_list		lst;

  va_start(lst, pattern);
  return (bunny_configuration_vgetf_node(cnf, data, pattern.c_str(), lst));
}

inline bool		bunny_configuration_getf(t_bunny_configuration		*cnf,
						 std::string			&data,
						 const std::string		&pattern,
						 ...)
{
  va_list		lst;
  const char		*str;
  bool			ret;

  va_start(lst, pattern);
  if ((ret = bunny_configuration_vgetf_string(cnf, &str, pattern.c_str(), lst)))
    data = str;
  return (ret);
}

inline bool		bunny_configuration_getf(t_bunny_configuration		*cnf,
						 int				&data,
						 const std::string		&pattern,
						 ...)
{
  va_list		lst;

  va_start(lst, pattern);
  return (bunny_configuration_vgetf_int(cnf, &data, pattern.c_str(), lst));
}

inline bool		bunny_configuration_getf(t_bunny_configuration		*cnf,
						 bool				&data,
						 const std::string		&pattern,
						 ...)
{
  va_list		lst;

  va_start(lst, pattern);
  return (bunny_configuration_vgetf_bool(cnf, &data, pattern.c_str(), lst));
}

inline bool		bunny_configuration_getf(t_bunny_configuration		*cnf,
						 double				&data,
						 const std::string		&pattern,
						 ...)
{
  va_list		lst;

  va_start(lst, pattern);
  return (bunny_configuration_vgetf_double(cnf, &data, pattern.c_str(), lst));
}

# endif
#endif	/*		__LAPIN_CONFIGURATION_HPP__	*/
