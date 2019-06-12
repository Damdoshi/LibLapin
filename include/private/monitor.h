/*
** Jason Brillante "Damdoshi"
** Hanged Bunny Studio 2014-2016
**
**
** Bibliotheque Lapin
*/

#ifndef				__LAPIN_PRIVATE_MONITOR_H__
# define			__LAPIN_PRIVATE_MONITOR_H__

struct bunny_monitored_value
{
  t_bunny_monitored_type	type;
  std::list<int>		ihistory;
  std::list<double>		dhistory;
  std::list<std::string>	shistory;
  const void			*data;
};

extern std::map<std::string, struct bunny_monitored_value> gl_monitor;

ssize_t				_bunny_monitor_prepare_buffer(char		*buf,
							      ssize_t		len,
							      const char	*n);

#endif	/*			__LAPIN_PRIVATE_MONITOR_H__	*/
