/*
** From https://blog.noctua-software.com/named-parameters-in-c.html
** Thank you for that. It is pretty great.
**
** *************************
**
** Jason Brillante "Damdoshi"
** Hanged Bunny Studio 2014-2019
**
** Bibliotheque Lapin
**
** Side effect of parameter naming: default values for unused parameter.
** They're set to zero, which can be pretty useful. ;)
**
** How to use it?
** Write a macro that looks like that:
** #define function(...) bunny_named_call(real_function_name, (int x, float y), __VA_ARGS__)
** Replace (int x, float y) by the real prototype.
**
** After that, you can write:
** function(.x = 42, .y = 4.2)
*/

#ifndef		__LAPIN_NAMED_PARAMETER_H__
# define	__LAPIN_NAMED_PARAMETER_H__
# ifdef		__GNUC__
#  define	FE_0(a, a0, X)				a0(0, X)
#  define	FE_1(a, a0, X, ...)			a(1, X)FE_0(a, a0, __VA_ARGS__)
#  define	FE_2(a, a0, X, ...)			a(2, X)FE_1(a, a0, __VA_ARGS__)
#  define	FE_3(a, a0, X, ...)			a(3, X)FE_2(a, a0, __VA_ARGS__)
#  define	FE_4(a, a0, X, ...)			a(4, X)FE_3(a, a0, __VA_ARGS__)
#  define	FE_5(a, a0, X, ...)			a(4, X)FE_4(a, a0, __VA_ARGS__)
#  define	FE_6(a, a0, X, ...)			a(4, X)FE_5(a, a0, __VA_ARGS__)
#  define	FE_7(a, a0, X, ...)			a(4, X)FE_6(a, a0, __VA_ARGS__)
#  define	FE_8(a, a0, X, ...)			a(4, X)FE_7(a, a0, __VA_ARGS__)
#  define	FE_9(a, a0, X, ...)			a(4, X)FE_8(a, a0, __VA_ARGS__)
#  define	GET_MACRO(_0, _1, _2, _3, _4, _5, _6, _7, _8, _9, NAME, ...) NAME

#  define	FOR_EACH(a, a0, ...)					\
  GET_MACRO(__VA_ARGS__, FE_9, FE_8, FE_7, FE_6, FE_5, FE_4, FE_3, FE_2, FE_1, FE_0) \
  (a, a0, __VA_ARGS__)

#  define	ARGS_STRUCT_ATTR(n, attr)		union {attr, _##n;};

#  define	ARGS_STRUCT(...)		       \
  struct {					       \
    FOR_EACH(ARGS_STRUCT_ATTR, ARGS_STRUCT_ATTR,       \
	     __VA_ARGS__)			       \
  }

#  define	ARGS_PASS(n, attr)			_args._##n,
#  define	ARGS_PASS0(n, attr)			_args._##n
#  define	PASS_STRUCT(...)		\
  FOR_EACH(ARGS_PASS, ARGS_PASS0, __VA_ARGS__)

#  define	bunny_named_call(func, args, ...) ({	\
      ARGS_STRUCT args _args = {__VA_ARGS__};		\
      func(PASS_STRUCT args);				\
    })

# else
#  define	bunny_named_call(func, args, ...)
# endif
#endif	/*	__LAPIN_NAMED_PARAMETER_H__		*/

