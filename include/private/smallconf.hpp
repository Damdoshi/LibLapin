/*
** Jason Brillante "Damdoshi"
** Hanged Bunny Studio 2014-2016
**
**
** Bibliotheque Lapin
*/

#ifndef				__LAPIN_PRIVATE_SMALLCONF_HPP__
# define			__LAPIN_PRIVATE_SMALLCONF_HPP__
# include			<iomanip>
# include			<sstream>
# include			<stack>
# include			<list>

struct				Sequence;
struct				Expression;
struct				Function;

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
      NOTYPE			= -1, // "void"
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

  mutable SmallConf		*alias_on;
  mutable char			**distant_string;
  mutable double		*distant_double;
  mutable int			*distant_int;
  mutable char			*distant_char;
  mutable bool			*distant_bool;

  mutable bool			is_converted;
  static bool			create_mode;
  static std::stack<std::string> file_read;
  static std::list<std::string> file_path;
  SmallConf			*father;
  Type				last_type = NOTYPE;
  bool				symbol;

  enum				e_politic
    {
      NO_POLITIC,
      DYNAMIC_POLITIC,
      LOCAL_POLITIC,
      RECURSIVE_POLITIC
    };

  e_politic			is_const = NO_POLITIC;
  e_politic			is_solid = NO_POLITIC;
  e_politic			is_eternal = NO_POLITIC;

  Sequence			*sequence;
  Function			*function;
  Expression			*expression;
  int				line;

  SmallConf			&Assign(const SmallConf				&a,
					SmallConf				*root = NULL,
					SmallConf				*local = NULL,
					SmallConf				*artif = NULL,
					SmallConf				*param = NULL);
  SmallConf			&operator=(const SmallConf			&o);
  bool				operator==(const SmallConf			&o) const;
  bool				operator!=(const SmallConf			&o) const;
  bool				operator<(const SmallConf			&o) const;
  bool				operator<=(const SmallConf			&o) const;
  bool				operator>(const SmallConf			&o) const;
  bool				operator>=(const SmallConf			&o) const;

  static bool			RecursiveCheck(const SmallConf			&a,
					       const SmallConf			&b);
  static bool			RecursiveAssign(SmallConf			&a,
						const SmallConf			&b,
						bool				hsh,
						bool				arr);

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
  ::const_iterator		Begin(void) const
  {
    return (nodes.begin());
  }
  std::map
  <std::string, SmallConf*>
  ::const_iterator		End(void) const
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

  SmallConf			&operator[](const std::string		&str);
  SmallConf			&operator[](size_t			i);
  const SmallConf		&operator[](const std::string		&str) const;
  const SmallConf		&operator[](size_t			i) const;

  void				Remove(const std::string		&str);
  void				Remove(size_t				i);

  bool				Access(const std::string		&str) const;
  bool				Access(ssize_t				i) const;

  void				SetString(const std::string		&v,
					  bool				raw = false);
  bool				GetString(const char			**out,
					  SmallConf			*root = NULL,
					  SmallConf			*local = NULL,
					  SmallConf			*artif = NULL,
					  SmallConf			*param = NULL) const;
  void				SetInt(int				v);
  bool				GetInt(int				*v,
				       SmallConf			*root = NULL,
				       SmallConf			*local = NULL,
				       SmallConf			*artif = NULL,
				       SmallConf			*param = NULL) const;
  void				SetDouble(double			v);
  bool				GetDouble(double			*v,
					  SmallConf			*root = NULL,
					  SmallConf			*local = NULL,
					  SmallConf			*artif = NULL,
					  SmallConf			*param = NULL) const;

  void				Bind(int				*v);
  void				Bind(bool				*v);
  void				Bind(double				*v);
  void				Bind(char				**v);
  void				Bind(char				*v);
  void				Unbind(void);

  void				Link(SmallConf				*x);

  void				Clear(void);

  SmallConf(void);
  ~SmallConf(void);
};

std::ostream			&operator<<(std::ostream		&os,
					    const SmallConf		&cnf);

#endif	//			__LAPIN_PRIVATE_SMALLCONF_HPP__
