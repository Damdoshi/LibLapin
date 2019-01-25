// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2019
//
// Lapin library

#ifndef			__LAPIN_PRIVATE_LOGS_HPP__
# define		__LAPIN_PRIVATE_LOGS_HPP__
# define		leave(er, statement)			\
  do { bunny_errno = er; statement; } while (0)
# define		quit(er, returned_value)		\
  do { bunny_errno = er; return (returned_value); } while (0)

# ifndef		BUNNY_LOG_LEVEL
#  define		BUNNY_LOG_LEVEL				3
# endif

# if			BUNNY_LOG_LEVEL >= 0
#  define	        PRELOG(...)				\
  do { BunnyLog(__PRETTY_FUNCTION__, __func__, LogType::LOG, ##__VA_ARGS__); } while (0)
# else
#  define	        PRELOG(...)
# endif

# if			BUNNY_LOG_LEVEL >= 1
#  define	        POSTLOG(...)				\
  do { BunnyLog(__PRETTY_FUNCTION__, __func__, LogType::LOG, ##__VA_ARGS__); } while (0)
# else
#  define	        POSTLOG(...)
# endif

# if			BUNNY_LOG_LEVEL >= 2
#  define	        FAILED(statement, er, ...)		\
  do { BunnyLog(__PRETTY_FUNCTION__, __func__, LogType::FAILED, ##__VA_ARGS__); bunny_errno = er; statement;} while (0)
# else
#  define		FAILED(statement, er, ...)		\
  leave(er, statement)
# endif

# if			BUNNY_LOG_LEVEL >= 3
#  define	        CRITICAL(statement, er, ...)		\
  do { BunnyLog(__PRETTY_FUNCTION__, __func__, LogType::CRITICAL, ##__VA_ARGS__); bunny_errno = er; statement;} while (0)
# else
#  define		CRITICAL(statement, er, ...)		\
  leave(er, statement)
# endif


enum class		LogType
  {
    LOG,		// Simple information
    FAILED,		// The function did not achieved its purpose
    CRITICAL		// The function encounter a failure that needs a reaction
  };

template		<typename Arg, class ... Types>
void			BunnyLog(const std::string			&prototype,
				 const std::string			&funcname,
				 LogType				logtype,
				 const std::vector<std::string>		&labels,
				 const std::string			&message,
				 Arg&&					return_value,
				 Args&&...				args)
{
  std::stringstream	ss;
  int			descriptor;
  int			errcode = bunny_errno;

  if (logtype == LogType::LOG)
    {
      if (bunny_filter_label(labels) == false)
	return ;
      if ((descriptor = bunny_get_log_descriptor()) < 0)
	return ;
      ss << "LOG\t";
    }
  else if (logtype == LogType::FAILED)
    {
      if (bunny_filter_label(labels) == false)
	return ;
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

  ss << (long unsigned int)time(NULL) << "\t";

  if (gl_complete_log)
    {
      ss << __FILE__ << ":" << __LINE__ << "\t";
      ss << prototype << "\t";
      ((ss << std::forward<Args>(args)) << " ", ...);
      ss << "-> " << std::forward<Arg>(arg) << "\t";
    }
  else
    ss << funcname << "\t";

  if (message.size())
    ss << message;
  else if (logtype != LogType::LOG)
    ss << "Error code " << errcode << ": " << bunny_strerror(errcode);
  ss << std::endl;

  if (write(descriptor, ss.str().c_str(), ss.str().size()) == -1)
    std::cerr << "Failed to log!" << std::endl;
}


#endif	//		__LAPIN_PRIVATE_LOGS_HPP__

