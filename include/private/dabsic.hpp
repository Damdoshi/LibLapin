/*
** Jason Brillante "Damdoshi"
** Hanged Bunny Studio 2014-2016
**
**
** Bibliotheque Lapin
*/

#ifndef			__LAPIN_PRIVATE_DABSIC_HPP__
# define		__LAPIN_PRIVATE_DABSIC_HPP__

t_bunny_configuration	*_bunny_read_dabsic(const char			*code,
					    t_bunny_configuration	*config);
void			dabsic_sequence_read_separator(const char	*code,
						       ssize_t		&i);
void			dabsic_read_separator(const char		*code,
					      ssize_t			&i);
Decision		dabsic_read_inside_scope(const char		*code,
						 ssize_t		&i,
						 SmallConf		&conf,
						 SmallConf		&root);
Decision		dabsic_read_inside_xml(const char		*code,
					       ssize_t			&i,
					       SmallConf		&conf,
					       SmallConf		&root);
Decision		dabsic_read_inside_array(const char		*code,
						 ssize_t		&i,
						 SmallConf		&conf,
						 SmallConf		&root);

Decision		dabsic_read_scope(const char			*code,
					  ssize_t			&i,
					  SmallConf			&conf,
					  SmallConf			&root);
Decision		dabsic_read_csv(const char			*code,
					ssize_t				&i,
					SmallConf			&conf,
					SmallConf			&root);
Decision		dabsic_read_array(const char			*code,
					  ssize_t			&i,
					  SmallConf			&conf,
					  SmallConf			&root);
Decision		dabsic_read_field(const char			*code,
					  ssize_t			&i,
					  SmallConf			&conf,
					  SmallConf			&root);
Decision		dabsic_read_function(const char			*code,
					     ssize_t			&i,
					     SmallConf			&conf,
					     SmallConf			&root);
Decision		dabsic_read_sequence(const char			*code,
					     ssize_t			&i,
					     SmallConf			&conf,
					     SmallConf			&root);
Decision		dabsic_read_xml(const char			*code,
					ssize_t				&i,
					SmallConf			&conf,
					SmallConf			&root);

Decision		dabsic_read_field_value(const char		*code,
						ssize_t			&i,
						SmallConf		&conf,
						SmallConf		&root);
Decision		dabsic_read_litterals(const char		*code,
					      ssize_t			&i,
					      SmallConf			&conf,
					      SmallConf			&root);
SmallConf		*dabsic_field_name(const char			*code,
					   ssize_t			&i,
					   SmallConf			&conf,
					   bool				manda = true);

char			*_bunny_write_dabsic(const t_bunny_configuration *config);

#endif	/*		__LAPIN_PRIVATE_DABSIC_HPP__			*/
