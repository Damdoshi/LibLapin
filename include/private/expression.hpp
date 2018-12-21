/*
** Jason Brillante "Damdoshi"
** Hanged Bunny Studio 2014-2016
**
**
** Bibliotheque Lapin
*/

#ifndef				__LAPIN_PRIVATE_EXPRESSION_HPP__
# define			__LAPIN_PRIVATE_EXPRESSION_HPP__

struct				Expression
{
  enum				TypeCast
    {
      NO_CAST,
      INT_CAST,
      REAL_CAST,
      STRING_CAST
    };
  enum				OperatorFamily
    {
      BEOF_ASSIGNATION,
      BEOF_TERNARY,
      BEOF_LOWLOGIC,
      BEOF_HIGHLOGIC,
      BEOF_TEST,
      BEOF_LOWBINARY,
      BEOF_HIGHBINARY,
      BEOF_SHIFT,
      BEOF_LOWMATH,
      BEOF_HIGHMATH,
      BEOF_POW,
      BEOF_CAT,
      LAST_OPERATOR_FAMILY
    };
  enum				Operator
    {
      BEO_ASSIGN		= 0,
      BEO_REC_ASSIGN,
      BEO_ARRAY_ASSIGN,
      BEO_HASH_ASSIGN,
      BEO_LOR_ASSIGN,
      BEO_LXOR_ASSIGN,
      BEO_LAND_ASSIGN,
      BEO_BOR_ASSIGN,
      BEO_BXOR_ASSIGN,
      BEO_BAND_ASSIGN,
      BEO_LSHIFT_ASSIGN,
      BEO_RSHIFT_ASSIGN,
      BEO_ADD_ASSIGN,
      BEO_SUB_ASSIGN,
      BEO_MUL_ASSIGN,
      BEO_DIV_ASSIGN,
      BEO_MOD_ASSIGN,
      BEO_POW_ASSIGN,
      BEO_CAT_ASSIGN,
      // BEO_MOVE,
      // BEO_ASSIGN_ XOR, OR, ETC
      BEO_TERNARY		= 0,
      BEO_TERNARY_ELSE,
      BEO_LOGIC_OR		= 0,
      BEO_LOGIC_XOR,
      BEO_LOGIC_AND		= 0,
      BEO_EQUAL			= 0,
      BEO_REC_EQUAL,
      BEO_DIFF,
      BEO_REC_DIFF,
      BEO_INF_EQU,
      BEO_GRT_EQU,
      BEO_INF,
      BEO_GRT,
      BEO_BIN_OR		= 0,
      BEO_BIN_XOR,
      BEO_BIN_AND		= 0,
      BEO_LSHIFT		= 0,
      BEO_RSHIFT,
      // ROT
      BEO_ADD			= 0,
      BEO_SUB,
      BEO_MUL			= 0,
      BEO_DIV,
      BEO_MOD,
      BEO_POW,
      BEO_CAT			= 0
    };

  static const std::string
  OperatorToken[LAST_OPERATOR_FAMILY][21][8];

  int				optor_family;
  int				optor;

  SmallConf			val;
  std::vector<Expression*>	operand;
  bool				is_const;
  TypeCast			type_cast;

  std::string			file;
  int				line;

  Expression(void)
    : optor_family(-1),
      optor(-1),
      is_const(false),
      type_cast(NO_CAST),
      line(0)
  {}
  ~Expression(void)
  {
    size_t			i;

    for (i = 0; i < operand.size(); ++i)
      delete operand[i];
  }
};

typedef bool			(*t_expr_computation)(Expression	&exp,
						      bool		dry,
						      SmallConf		*root,
						      SmallConf		*local,
						      SmallConf		*artif,
						      SmallConf		*param);
typedef bool			t_expr_computation_func(Expression	&exp,
							bool		dry,
							SmallConf	*root,
							SmallConf	*local,
							SmallConf	*artif,
							SmallConf	*param);

extern const t_expr_computation	gl_expr_computation[Expression::LAST_OPERATOR_FAMILY];

t_expr_computation_func		expr_compute_assign;
t_expr_computation_func		expr_compute_low_logic;
t_expr_computation_func		expr_compute_high_logic;
t_expr_computation_func		expr_compute_test;
t_expr_computation_func		expr_compute_ternary;
t_expr_computation_func		expr_compute_low_bin;
t_expr_computation_func		expr_compute_high_bin;
t_expr_computation_func		expr_compute_shift;
t_expr_computation_func		expr_compute_low_math;
t_expr_computation_func		expr_compute_high_math;
t_expr_computation_func		expr_compute_pow;
t_expr_computation_func		expr_compute_cat;
t_expr_computation_func		expr_compute_function_call;

SmallConf			*expr_get_variable(SmallConf		&variable,
						   bool			dry,
						   SmallConf		*root,
						   SmallConf		*local,
						   SmallConf		*artif,
						   SmallConf		*params);

bool				expr_read_function_call(const char	*code,
							ssize_t		&i,
							Expression	&expr);
Expression			*expr_read_operator(const char		*code,
						    ssize_t		&i,
						    size_t		ope);
Expression			*expr_read_operand(const char		*code,
						   ssize_t		&i);

Decision			expr_read_expression(const char		*code,
						     ssize_t		&i,
						     SmallConf		&conf,
						     int		operation);
void				restore_expression(std::ostream		&ss,
						   Expression		&conf,
						   bool			cmp = false,
						   bool			jsonhex = false);
void				expr_read_separator(const char		*code,
						    ssize_t		&i);


bool				expr_compute(SmallConf			&expr,
					     SmallConf			*proto,
					     bool			dry,
					     SmallConf			*root,
					     SmallConf			*local,
					     SmallConf			*artif,
					     SmallConf			*param);
bool				expr_precompute(SmallConf		&expr);

char				*_bunny_write_expression(const
							 t_bunny_configuration
							 *config);
extern "C" char			*_bunny_write_expression_prec(const
							      t_bunny_configuration
							      *config);
bool				expr_compute_function_call(Expression	&exp,
							   bool		dry,
							   SmallConf	*root,
							   SmallConf	*local,
							   SmallConf	*artif,
							   SmallConf	*param);
bool				expr_compute_cast(Expression		&exp,
						  bool			dry,
						  SmallConf		*root,
						  SmallConf		*local,
						  SmallConf		*artif,
						  SmallConf		*param);
t_bunny_decision		expr_compute_builtins(Expression	&exp,
						      bool		dry,
						      SmallConf		*root,
						      SmallConf		*local,
						      SmallConf		*artif,
						      SmallConf		*param);

t_bunny_configuration		*_bunny_read_expression(const char	*code,
							t_bunny_configuration *config);
bool				expr_test_type(SmallConf		&ope,
					       int			a = -1,
					       int			b = -1,
					       int			c = -1);
bool				check_keywords(const std::string	&str);

#endif	/*			__LAPIN_PRIVATE_EXPRESSION_HPP__	*/
