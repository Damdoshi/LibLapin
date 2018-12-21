/*
** Jason Brillante "Damdoshi"
** Hanged Bunny Studio 2014-2016
**
**
** Bibliotheque Lapin
*/

#ifndef				__LAPIN_PRIVATE_SEQUENCE_HPP__
# define			__LAPIN_PRIVATE_SEQUENCE_HPP__

struct				Sequence
{
  struct			Line
  {
    std::string			command;
    size_t			nbr_parameters;
    std::vector<SmallConf>	parameters;
  };

  std::map<int, std::string>	labels;
  std::vector<Line>		lines;
  size_t			nbr_lines;

  std::stack<int>		instruction_pointer;

  // For asynchronous execution of wait
  t_bunny_time			previous;
};

void				restore_sequence(std::ostream		&ss,
						 SmallConf		&conf,
						 size_t			indent);
char
*_bunny_write_dabsic_sequence(const t_bunny_configuration		*config);

t_bunny_configuration		*_bunny_read_sequence(const char	*code,
						      t_bunny_configuration *config);

bool				dabsic_read_sequence_label(const char	*code,
							   ssize_t	&i,
							   std::string	&out);
Decision			dabsic_read_sequence_line(const char	*code,
							  ssize_t	&i,
							  Sequence::Line &line,
							  SmallConf	&root);
Decision			dabsic_read_inside_sequence(const char	*code,
							    ssize_t	&i,
							    SmallConf	&conf,
							    SmallConf	&root);


bool				sequence_compute(SmallConf		&func,
						 SmallConf		*proto,
						 SmallConf		*root,
						 SmallConf		*local,
						 SmallConf		*params,
						 const t_bunny_sequence_fallback_command *fb,
						 void			*dat);

#endif	/*			__LAPIN_PRIVATE_SEQUENCE_HPP__	*/
