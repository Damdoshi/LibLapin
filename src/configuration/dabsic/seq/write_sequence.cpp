// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2016
//
// Lapin library

#include	"lapin_private.h"

void		restore_sequence(std::stringstream		&ss,
				 SmallConf			&conf,
				 size_t				indent)
{
  if (conf.sequence == NULL)
    return ;
  std::map<int, std::string>::iterator	it;
  Sequence	&seq = *conf.sequence;
  size_t	i, j;

  for (i = 0; i < seq.nbr_lines; ++i)
    {
      if ((it = seq.labels.find(i)) != seq.labels.end())
	{
	  for (j = 0; j < indent - 1; ++j)
	    ss << " ";
	  ss << it->second << ":" << std::endl;
	}
      for (j = 0; j < indent; ++j)
	ss << " ";
      ss << seq.lines[i].command;
      if (seq.lines[i].nbr_parameters)
	{
	  ss << " ";
	  for (j = 0; j < seq.lines[i].nbr_parameters; )
	    {
	      writevalue(ss, seq.lines[i].parameters[j]);
	      if (++j < seq.lines[i].nbr_parameters)
		ss << ", ";
	    }
	}
      ss << std::endl;
    }
}

char
*_bunny_write_dabsic_sequence(const t_bunny_configuration	*config)
{
  std::stringstream	ss;
  char			*ret;

  restore_sequence(ss, *(SmallConf*)config, 2);
  if ((ret = (char*)bunny_malloc(sizeof(*ret) * (ss.str().size() + 1))) == NULL)
    scream_error_if(return (NULL), bunny_errno, "%p -> %s", config, ret);
  strcpy(ret, ss.str().c_str());
  scream_log_if("%p -> %s", config, ret);
  return (ret);
}

