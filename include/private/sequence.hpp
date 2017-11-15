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
};

void				restore_sequence(std::stringstream	&ss,
						 SmallConf		&conf,
						 size_t			indent);
bool				dabsic_read_sequence_label(const char	*code,
							   ssize_t	&i,
							   std::string	&out);
Decision			dabsic_read_sequence_line(const char	*code,
							  ssize_t	&i,
							  Sequence::Line &line,
							  SmallConf	&root);

#endif	/*			__LAPIN_PRIVATE_SEQUENCE_HPP__	*/
