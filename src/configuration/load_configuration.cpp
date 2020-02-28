// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2018
//
// Lapin library

#include		<libgen.h>
#include		"lapin_private.h"

#define			PATTERN		"%d type, %s file, %p config -> %p"

t_bunny_configuration	*bunny_load_configuration(t_bunny_configuration_type		type,
						  const char				*file,
						  t_bunny_configuration			*config)
{
  std::list<std::string>::reverse_iterator it;
  t_bunny_configuration	*outconf = NULL;
  char			buffer[1024];
  char			because_dirname[1024];
  char			*code;
  size_t		siz;

  if (SmallConf::file_path.size() == 0)
    SmallConf::file_path.push_back("");

  for (it = SmallConf::file_path.rbegin(); it != SmallConf::file_path.rend(); ++it)
    {
      if (*it != "")
	snprintf(&buffer[0], sizeof(buffer), "%s/%s", it->c_str(), file);
      else
	snprintf(&buffer[0], sizeof(buffer), "%s", file);
      if (bunny_load_file(&buffer[0], (void**)&code, &siz) != -1)
	{
	  if (gl_bunny_ressource_ciphering)
	    gl_bunny_ressource_ciphering(code, siz, gl_bunny_ressource_data, false);
	  break ;
	}
    }
  if (it == SmallConf::file_path.rend())
    scream_error_if
      (return (NULL), ENOENT, PATTERN,
       "ressource,configuration", type, file, config, outconf
       );

  SmallConf::file_read.push(file);
  snprintf(&because_dirname[0], sizeof(because_dirname), "%s", file);
  SmallConf::file_path.push_back(dirname(&because_dirname[0]));

  if (type == BC_DATA)
    outconf = _bunny_read_data(code, siz, config);
  else
    outconf = bunny_read_configuration(type, code, config);

  SmallConf::file_path.pop_back();
  SmallConf::file_read.pop();
  bunny_delete_file(code, &buffer[0]);
  if (!outconf)
    scream_error_if
      (, bunny_errno, PATTERN, "ressource,configuration", type, file, config, outconf);
  scream_log_if(PATTERN, "ressource,configuration", type, file, config, outconf);
  return (outconf);
}

