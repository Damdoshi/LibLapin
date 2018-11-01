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
      PRINT_ERROR,
      WHILE,
      FOR,
      REPEAT,
      DO_WHILE,
      BREAK,
      CONTINUE,
      RETURN,
      BRAKE, // I don't remember what it is. Maybe just to debug, to have a break point.
      WITH,
      SELECT,
      LAST_COMMAND
    };

  Command			command;
  SmallConf			local_variables;
  SmallConf			value; // operation ;
  SmallConf			result;
  SmallConf			additionnal_values[2];
  std::vector<Function>		lines;
  size_t			nbr_lines;

  int				line;
  std::string			file;
};

typedef enum			e_compute_result
  {
    CR_ERROR,
    CR_RETURN,
    CR_BREAK,
    CR_CONTINUE,
    CR_OK
  }				t_compute_result;

typedef t_compute_result	(*t_dabsic_compute)(Function		&func,
						    Function		&mainnod,
						    bool		dry,
						    SmallConf		*root,
						    SmallConf		*local,
						    SmallConf		*artif,
						    SmallConf		*params);
typedef t_compute_result	t_dabsic_compute_f(Function		&func,
						   Function		&mainnod,
						   bool			dry,
						   SmallConf		*root,
						   SmallConf		*local,
						   SmallConf		*artif,
						   SmallConf		*params);

t_dabsic_compute_f		dabsic_compute_instruction;
t_dabsic_compute_f		dabsic_compute_if;
t_dabsic_compute_f		dabsic_compute_while;
t_dabsic_compute_f		dabsic_compute_repeat;
t_dabsic_compute_f		dabsic_compute_do;
t_dabsic_compute_f		dabsic_compute_for;
t_dabsic_compute_f		dabsic_compute_no_execution;
t_dabsic_compute_f		dabsic_compute_print;
t_dabsic_compute_f		dabsic_compute_break;
t_dabsic_compute_f		dabsic_compute_brake;
t_dabsic_compute_f		dabsic_compute_continue;
t_dabsic_compute_f		dabsic_compute_return;
t_dabsic_compute_f		dabsic_compute_with;
t_dabsic_compute_f		dabsic_compute_select;
t_dabsic_compute_f		dabsic_compute_scope;

extern t_dabsic_compute		gl_dabsic_compute[Function::LAST_COMMAND];

bool				dabsic_compute(SmallConf		&func,
					       SmallConf		*proto,
					       bool			dry,
					       SmallConf		*root,
					       SmallConf		*artif,
					       SmallConf		*params);

char *_bunny_write_dabsic_function(const t_bunny_configuration		*config);

t_bunny_configuration		*_bunny_read_function(const char	*code,
						      t_bunny_configuration *cnf);
Decision			dabsic_read_inside_function(const char	*code,
							    ssize_t	&i,
							    Function	*func,
							    SmallConf	&conf,
							    SmallConf	&root);
void				restore_function(std::ostream		&ss,
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
Decision			dabsic_read_with(const char		*code,
						 ssize_t		&i,
						 Function		&line,
						 SmallConf		&funcnode,
						 SmallConf		&root);
Decision			dabsic_read_select(const char		*code,
						   ssize_t		&i,
						   Function		&line,
						   SmallConf		&funcnode,
						   SmallConf		&root);
Decision			dabsic_read_break(const char		*code,
						  ssize_t		&i,
						  Function		&line,
						  SmallConf		&funcnode,
						  SmallConf		&root);
Decision			dabsic_read_continue(const char		*code,
						     ssize_t		&i,
						     Function		&line,
						     SmallConf		&funcnode,
						     SmallConf		&root);
Decision			dabsic_read_return(const char		*code,
						   ssize_t		&i,
						   Function		&line,
						   SmallConf		&funcnode,
						   SmallConf		&root);
Decision			dabsic_read_while(const char		*code,
						  ssize_t		&i,
						  Function		&line,
						  SmallConf		&funcnode,
						  SmallConf		&root);
Decision			dabsic_read_for(const char		*code,
						ssize_t			&i,
						Function		&line,
						SmallConf		&funcnode,
						SmallConf		&root);
Decision			dabsic_read_repeat(const char		*code,
						   ssize_t		&i,
						   Function		&func,
						   SmallConf		&funcnode,
						   SmallConf		&root);
Decision			dabsic_read_do(const char		*code,
					       ssize_t			&i,
					       Function			&func,
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
