// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2019
//
// Lapin library

// Il faut faire de cette gestion d'erreur une gestion utilisable coté utilisateur
// De manière a ce qu'un utilisateur puisse ajouter ses propres cascades d'erreurs
// A celle de la LibLapin.

#ifndef			__LAPIN_PRIVATE_LOGS_HPP__
# define		__LAPIN_PRIVATE_LOGS_HPP__
# include		<iostream>
# include		<sstream>
# include		<stack>
# include		<string>
# include		<sys/types.h>
# include		<unistd.h>
# include		<vector>

# ifndef		__LAPIN_H__
#  define		__LAPIN_H__
# endif
# include		"lapin2/error.h"

# ifdef			BUNNY_DISABLE_ALL_LOG
#  ifndef		BUNNY_DISABLE_PRE_LOG
#   define		BUNNY_DISABLE_PRE_LOG
#  endif
#  ifndef		BUNNY_DISABLE_POST_LOG
#   define		BUNNY_DISABLE_POST_LOG
#  endif
#  ifndef		BUNNY_DISABLE_FAILURE_LOG
#   define		BUNNY_DISABLE_FAILURE_LOG
#  endif
#  ifndef		BUNNY_DISABLE_CRITICAL_LOG
#   define		BUNNY_DISABLE_CRITICAL_LOG
#  endif
# endif

# ifdef			BUNNY_DISABLE_PRE_LOG
#  define		Prelog(...)				\
  { ::bunny::Log(BLV_DISPLAY_PRELOG, __PRETTY_FUNCTION__, __func__, BLT_LOG, ##__VA_ARGS__); }
# else
#  define		Prelog(...)
# endif

# ifdef			BUNNY_DISABLE_POST_LOG
#  define		Postlog(...)				\
  { ::bunny::Log(BLV_DISPLAY_POSTLOG, __PRETTY_FUNCTION__, __func__, BLT_LOG, ##__VA_ARGS__); ::bunny::TryFlushReturn(); }
# else
#  define		Postlog(...)				::bunny::TryFlushReturn()
# endif

# ifdef			BUNNY_DISABLE_FAILURE_LOG
#  define		Failure(statement, er, ...)		\
  { ::bunny::Log(BLV_DISPLAY_FAILURE, __PRETTY_FUNCTION__, __func__, BLT_FAILED, ##__VA_ARGS__); bunny_errno = er; statement; }
# else
#  define		Failure(statement, er, ...)		{ bunny_errno = er; statement; }
# endif

# ifdef			BUNNY_DISABLE_CRITICAL_LOG
#  define		Critical(statement, er, ...)		\
  { ::bunny::Log(BLV_DISPLAY_CRITICAL, __PRETTY_FUNCTION__, __func__, BLT_CRITICAL, ##__VA_ARGS__); bunny_errno = er; statement; }
# else
#  define		Critical(statement, er, ...)		{ bunny_errno = er; statement; }
# endif

namespace		bunny
{
  extern std::stack<
    std::pair<int, std::string>
    >			LogStack;
  extern int		LogVerbosity;
  extern
  t_bunny_log_length	LogLength;
  extern bool		FlushOnError;
  extern bool		FlushOnReturn;
  extern std::vector<
    std::string>	AcceptedLabels;

  inline void		DropLog(void)
  {
    while (!LogStack.empty())
      LogStack.pop();
  }

  inline int		FlushLog(void)
  {
    size_t		indent = 0;

    while (!LogStack.empty())
      {
	auto		top = LogStack.top();

	for (size_t i = 0; i < indent; ++i)
	  (void)write(top.first, "  ", 2);
	if (write(top.first, top.second.c_str(), top.second.size()) == -1)
	  std::cerr << "Failed to log : " << top.second << std::endl;
	LogStack.pop();
	indent += 1;
      }
    return (indent);
  }

  inline int		TryFlushError(void)
  {
    if (FlushOnError || FlushOnReturn)
      return (FlushLog());
    return (0);
  }

  inline int		TryFlushReturn(void)
  {
    if (FlushOnReturn)
      return (FlushLog());
    return (0);
  }

  template		<typename Arg, class ... Types>
  void			Log(int					loglevel,
			    const std::string			&prototype,
			    const std::string			&funcname,
			    t_bunny_log_type			logtype,
			    const std::vector<std::string>	&labels,
			    const std::string			&message,
			    Arg&&				return_value,
			    Types&&...				args)
  {
    int			errcode = bunny_errno;
    int			descriptor;
    std::stringstream	ss;

    if (!(loglevel & LogVerbosity))
      return ;
    if (logtype != BLT_CRITICAL)
      {
	int		count = 0;

	for (auto it = labels.begin(); it != labels.end(); ++it)
	  for (auto itx = AcceptedLabels.begin(); itx != AcceptedLabels.end(); ++itx)
	    if (*it == *itx)
	      {
		count += 1;
		goto out;
	      }
      out:
	if (count == 0)
	  return ;
      }
    if (logtype == BLT_LOG)
      {
	if ((descriptor = bunny_get_log_descriptor()) < 0)
	  return ;
	ss << "LOG\t";
      }
    else if (logtype == BLT_FAILED)
      {
	if ((descriptor = bunny_get_fail_descriptor()) < 0)
	  return ;
	ss << "FAIL\t";
      }
    else
      {
	if ((descriptor = bunny_get_critical_descriptor()) < 0)
	  return ;
	ss << "CRIT\t";
      }

    if (LogLength == BLL_FULL_LOG)
      {
	ss << (long unsigned int)time(NULL) << "\t";
	ss << __FILE__ << ":" << __LINE__ << "\t";
	ss << prototype << "\t";
	((ss << std::forward<Types>(args) << " "), ...);
	ss << "-> " << std::forward<Arg>(return_value) << "\t";
      }
    else
      ss << funcname << "\t";

    if (message.size())
      ss << message;
    else if (logtype != BLT_LOG)
      ss << "(Error code " << errcode << ": " << bunny_strerror(errcode) << ")";
    ss << std::endl;

    if (logtype != BLT_LOG)
      LogStack.push({descriptor, ss.str()});
    else if (write(descriptor, ss.str().c_str(), ss.str().size()) == -1)
      std::cerr << "Failed to log : " << ss.str() << std::endl;
  }
}

#endif	//		__LAPIN_PRIVATE_LOGS_HPP__
