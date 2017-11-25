/*
** Jason Brillante "Damdoshi"
** Hanged Bunny Studio 2014-2016
**
**
** Bibliotheque Lapin
*/

#ifndef				__LAPIN_PRIVATE_FUNCTION_HPP__
# define			__LAPIN_PRIVATE_FUNCTION_HPP__
# include			"smallconf.hpp"

struct				Function
{
  enum				Command
    {
      INSTRUCTION,
      IF,
      ELSE_IF,
      ELSE,
      PRINT,
      LAST_COMMAND
    };

  Command			command;
  SmallConf			local_variables;
  SmallConf			value; // operation ;
  std::vector<Function>		lines;
  size_t			nbr_lines;
};

char *_bunny_write_dabsic_function(const t_bunny_configuration		*config);

t_bunny_configuration		*_bunny_read_function(const char	*code,
						      t_bunny_configuration *cnf);
Decision			dabsic_read_inside_function(const char	*code,
							    ssize_t	&i,
							    Function	*func,
							    SmallConf	&conf,
							    SmallConf	&root);
void				restore_function(std::stringstream	&ss,
					       SmallConf		&conf,
					       size_t			indent);
Decision			dabsic_read_function_line(const char	*code,
							  ssize_t	&i,
							  Function	&line,
							  SmallConf	&root);
Decision			dabsic_read_inside_function(const char	*code,
							    ssize_t	&i,
							    Function	&line,
							    SmallConf	&funcnode,
							    SmallConf	&root);
Decision			dabsic_read_variable_declaration(const char *code,
								 ssize_t &i,
								 Function &line,
								 SmallConf &funcnode,
								 SmallConf &root);
Decision			dabsic_read_statement(const char	*code,
						      ssize_t		&i,
						      Function		&line,
						      SmallConf		&funcnode,
						      SmallConf		&root);
Decision			dabsic_read_if(const char		*code,
					       ssize_t			&i,
					       Function			&line,
					       SmallConf		&funcnode,
					       SmallConf		&root);
Decision			dabsic_read_instruction(const char	*code,
							ssize_t		&i,
							Function	&line,
							SmallConf	&funcnode,
							SmallConf	&root);
Decision			dabsic_read_print(const char		*code,
						  ssize_t		&i,
						  Function		&line,
						  SmallConf		&funcnode,
						  SmallConf		&root);

#endif	/*			__LAPIN_PRIVATE_FUNCTION_HPP__		*/
