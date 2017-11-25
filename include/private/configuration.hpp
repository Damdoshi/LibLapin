/*
** Jason Brillante "Damdoshi"
** Hanged Bunny Studio 2014-2016
**
**
** Bibliotheque Lapin
*/

#ifndef				__LAPIN_PRIVATE_CONFIGURATION_HPP__
# define			__LAPIN_PRIVATE_CONFIGURATION_HPP__
# include			<sstream>

enum				Decision
  {
    BD_ERROR,
    BD_NOT_FOUND,
    BD_OK
  };

# include			"smallconf.hpp"
# include			"dabsic.hpp"
# include			"xml.hpp"
# include			"json.hpp"
# include			"lua.hpp"
# include			"sequence.hpp"
# include			"function.hpp"
# include			"expression.hpp"

void				shrink_single_element_array(SmallConf		&cnf);

std::string			_clean_raw_data(const char			*code,
						size_t				len);

Decision			csv_read(const char				*code,
					 ssize_t				&i,
					 SmallConf				&conf,
					 SmallConf				&root);
t_bunny_configuration		*_bunny_read_ini(const char			*code,
						 t_bunny_configuration		*config);
t_bunny_configuration		*_bunny_read_lua(const char			*code,
						 t_bunny_configuration		*config);
t_bunny_configuration		*_bunny_read_csv(const char			*code,
						 t_bunny_configuration		*config);

char				*_bunny_write_ini(const t_bunny_configuration	*config);
char				*_bunny_write_lua(const t_bunny_configuration	*config);
char				*_bunny_write_csv(const t_bunny_configuration	*config);

int				checkchar(const char				*str,
					  ssize_t				&index,
					  const char				*token);
bool				readchar(const char				*str,
					 ssize_t				&index,
					 const char				*token);
bool				is_in(char					c,
				      const char				*tok);
bool				readtext(const char				*str,
					 ssize_t				&index,
					 const char				*token);

bool				readtext(const char				*str,
					 ssize_t				&index,
					 const std::string			*token,
					 size_t					len = (size_t)-1);
int				checklongesttext(const char			*str,
						 ssize_t			index,
						 const std::string		*token,
						 size_t				len = (size_t)-1);
int				readlongesttext(const char			*str,
						ssize_t				&index,
						const std::string		*token,
						size_t				len = (size_t)-1);
bool				checktext(const char				*str,
					  ssize_t				&index,
					  const std::string			*token,
					  size_t				len = (size_t)-1);
void				skipspace(const char				*str,
					  ssize_t				&i);
void				skipspace_inline(const char			*str,
						 ssize_t			&i);
bool				readfield(const char				*str,
					  ssize_t				&index);
bool				getfieldname(const char				*code,
					     ssize_t				&i,
					     char				*out,
					     ssize_t				len,
					     SmallConf				&scope,
					     bool				overwrite,
					     bool				manda = true);
bool				readdouble(const char				*code,
					   ssize_t				&i,
					   double				&d);
bool				readinteger(const char				*code,
					    ssize_t				&i,
					    int					&d);
bool				readstring(const char				*code,
					   ssize_t				&i,
					   char					*d,
					   ssize_t				len);
bool				readrawchar(const char				*code,
					    ssize_t				&i,
					    char				*d,
					    ssize_t				len,
					    const char				*endtok = NULL);
bool				readvalue(const char				*code,
					  ssize_t				&i,
					  SmallConf				&nod,
					  const char				*endtok = NULL);
bool				readaddress(const char				*code,
					    ssize_t				&i,
					    SmallConf				&nod);
int				whichline(const char				*code,
					  int					i);
void				writestring(std::stringstream			&ss,
					    const std::string			&str);
bool				read_data(const char				*code,
					  ssize_t				&i,
					  SmallConf				&config);
bool				read_sequence(const char			*code,
					      ssize_t				&i,
					      SmallConf				&config);
bool				read_function(const char			*code,
					      ssize_t				&i,
					      SmallConf				&config);
void				writevalue(std::stringstream			&ss,
					   const SmallConf			&cnf);


bool				_bunny_handle_directive(const char		*code,
							ssize_t			&i,
							SmallConf		*node,
							t_bunny_configuration	*fileroot,
							void (*readseparator)(const char*, ssize_t&));
t_bunny_configuration		*_bunny_configuration_go_get_node(const t_bunny_configuration *config,
								  const char		*addr,
								  ssize_t		&i);

extern const char		*fieldname_first_char;
extern const char		*fieldname;
extern const char		*numbers;


#endif	/*			__LAPIN_PRIVATE_CONFIGURATION_HPP__		*/
