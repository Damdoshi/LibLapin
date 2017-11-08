/*
** Jason Brillante "Damdoshi"
** Hanged Bunny Studio 2014-2016
**
**
** Bibliotheque Lapin
*/

#ifndef			__LAPIN_PRIVATE_XML_HPP__
# define		__LAPIN_PRIVATE_XML_HPP__

t_bunny_configuration	*_bunny_read_xml(const char			*code,
					 t_bunny_configuration		*config);
char			*_bunny_write_xml(const t_bunny_configuration	*config);

Decision		xml_read_between_markup(const char		*code,
						ssize_t			&i,
						SmallConf		&conf,
						SmallConf		&root);
Decision		xml_read_markup(const char			*code,
					ssize_t				&i,
					SmallConf			&conf,
					SmallConf			&root);
void			xml_read_separator(const char			*code,
					   ssize_t			&i);
std::string		xml_clean_raw_data(const char			*code,
					   size_t			len);

#endif	/*		__LAPIN_PRIVATE_XML_HPP__			*/

