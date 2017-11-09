/*
** Jason Brillante "Damdoshi"
** Hanged Bunny Studio 2014-2016
**
**
** Bibliotheque Lapin
*/

#ifndef				__LAPIN_PRIVATE_CONFIGURATION_HPP__
# define			__LAPIN_PRIVATE_CONFIGURATION_HPP__
# include			<iomanip>
# include			<sstream>

enum				Decision
  {
    BD_ERROR,
    BD_NOT_FOUND,
    BD_OK
  };
struct				SmallConf;

# include			"dabsic.hpp"
# include			"xml.hpp"

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
bool				readtext(const char				*str,
					 ssize_t				&index,
					 const char				*token);
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
					    char				*endtok = NULL);
bool				readvalue(const char				*code,
					  ssize_t				&i,
					  SmallConf				&nod,
					  char					*endtok = NULL);
int				whichline(const char				*code,
					  int					i);
void				writestring(std::stringstream			&ss,
					    std::string				&str);
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

struct				SmallConf
{
  enum				Construct
    {
      PLAIN,
      ARRAY,
      MAP
    };
  Construct			construct;

  enum				Type
    {
      INTEGER,
      DOUBLE,
      STRING,
      RAWSTRING
    };

  std::map
  <std::string, SmallConf*>	nodes;
  std::vector
  <SmallConf*>			array;
  std::map<
    std::string, SmallConf*
    >::iterator			iterator;

  bool				given_name;
  std::string			name;
  std::string			address;
  mutable bool			have_value;
  mutable std::string		original_value;
  mutable double		converted;
  mutable int			converted_2;
  mutable bool			is_converted;
  static bool			create_mode;
  SmallConf			*father;
  Type				last_type;

  SmallConf			&operator=(const SmallConf			&o)
  {
    if (&o == this)
      return (*this);
    have_value = o.have_value;
    original_value = o.original_value;
    converted = o.converted;
    converted_2 = o.converted_2;
    is_converted = o.is_converted;
    last_type = o.last_type;
    return (*this);
  }

  void				SetCreateMode(bool				cm)
  {
    create_mode = cm;
  }

  std::map
  <std::string, SmallConf*>
  ::iterator			Begin(void)
  {
    return (iterator = nodes.begin());
  }
  std::map
  <std::string, SmallConf*>
  ::iterator			End(void)
  {
    return (nodes.end());
  }
  std::map
  <std::string, SmallConf*>
  ::iterator			&It(void)
  {
    return (iterator);
  }
  size_t			Size(void) const
  {
    return (array.size());
  }
  size_t			NbrChild(void) const
  {
    return (nodes.size());
  }

  SmallConf			&operator[](const std::string			&str)
  {
    SmallConf			**slot;

    if (*(slot = &nodes[str]) == NULL)
      {
	if (create_mode)
	  {
	    std::stringstream	ss;

	    if (father)
	      ss << this->address << "." << str;
	    else
	      ss << this->address << str;
	    *slot = new SmallConf;
	    (*slot)->given_name = true;
	    (*slot)->name = str;
	    (*slot)->father = this;
	    (*slot)->address = ss.str();
	  }
	else
	  {
	    nodes.erase(str);
	    bunny_errno = BE_CANNOT_FIND_ELEMENT;
	    throw 0;
	  }
      }
    return (**slot);
  }
  SmallConf			&operator[](size_t				i)
  {
    size_t			olsize;
    
    if ((olsize = array.size()) <= i)
      {
	if (!create_mode)
	  {
	    bunny_errno = BE_CANNOT_FIND_ELEMENT;
	    throw 0;
	  }
	array.resize(i + 1);
	while (olsize <= i)
	  {
	    std::stringstream ss, sx;

	    sx << this->address << "[" << i << "]";
	    ss << this->name << "[" << i << "]";
	    array[olsize] = new SmallConf;
	    array[olsize]->father = this;
	    array[olsize]->given_name = false;
	    array[olsize]->name = ss.str();
	    array[olsize]->address = sx.str();
	    olsize += 1;
	  }
      }      
    return (*array[i]);
  }
  bool				Access(const std::string			&str)
  {
    return (nodes.find(str) != nodes.end());
  }
  bool				Access(ssize_t					i)
  {
    std::stringstream		ss;
    
    ss << std::setfill('0') << std::setw(8) << i;
    return (nodes.find(ss.str()) != nodes.end());
  }

  void				SetString(const std::string			&in,
					  bool					raw = false)
  {
    original_value = in;
    have_value = true;
    if (raw)
      last_type = RAWSTRING;
    else
      last_type = STRING;
  }
  bool				GetString(const char				**out) const
  {
    if (have_value == false)
      {
	if (array.size() == 1)
	  {
	    if (array[0]->GetString(out) == false)
	      return (false);
	    original_value = *out;
	    return (true);
	  }
	return (false);
      }
    *out = original_value.c_str();
    return (true);
  }

  void				SetInt(int					i)
  {
    std::stringstream		ss;

    ss << i;
    original_value = ss.str();
    converted_2 = converted = i;
    is_converted = true;
    have_value = true;
    last_type = INTEGER;
  }
  bool				GetInt(int					*i) const
  {
    double			d;

    if (GetDouble(&d) == false)
      {
	if (array.size() == 1)
	  {
	    if (array[0]->GetInt(i) == false)
	      return (false);
	    converted = *i;
	    return (true);
	  }
	return (false);
      }
    converted_2 = converted;
    *i = converted_2;
    return (true);
  }

  void				SetDouble(double				v)
  {
    std::stringstream		ss;

    ss << v;
    original_value = ss.str();
    converted_2 = converted = v;
    is_converted = true;
    have_value = true;
    last_type = DOUBLE;
  }
  bool				GetDouble(double				*v) const
  {
    if (have_value == false)
      {
	if (array.size() == 1)
	  {
	    if (array[0]->GetDouble(v) == false)
	      return (false);
	    converted = *v;
	    return (true);
	  }
	return (false);
      }
    if (is_converted == false)
      {
	ssize_t			i = 0;

	if (readdouble(original_value.c_str(), i, converted) == false)
	  return (false);
	is_converted = true;
      }
    *v = converted;
    return (true);
  }

  SmallConf(void)
    : construct(PLAIN),
      given_name(false),
      have_value(false),
      converted(0),
      converted_2(0),
      is_converted(false),
      father(NULL)
  {}
  ~SmallConf(void)
  {
    std::map<std::string, SmallConf*>::iterator	it;
    std::map<std::string, SmallConf*> dup = nodes;
    std::vector<SmallConf*> dupx = array;
    std::vector<SmallConf*>::iterator itx;

    if (father != NULL && father->nodes.find(name) != father->nodes.end())
      father->nodes.erase(name);
    for (it = dup.begin(); it != dup.end(); ++it)
      delete it->second;
    for (itx = dupx.begin(); itx != dupx.end(); ++itx)
      delete *itx;
  }
};

#endif	/*			__LAPIN_PRIVATE_CONFIGURATION_HPP__		*/
