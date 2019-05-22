// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2018
//
// Lapin library

#include		<sys/stat.h>
#include		<dirent.h>
#include		"lapin_private.h"

#define			PATTERN						\
  "%s code, %zd i, %p node, %p fileroot -> %s (%s %s on line %d)"

bool			isdir(const char				*d,
			      const char				*f)
{
  char			buffer[512];
  struct stat		stbuf;

  if (*d != '\0')
    {
      snprintf(&buffer[0], sizeof(buffer), "%s/%s", d, f);
      f = &buffer[0];
    }
  if (stat(f, &stbuf) == -1)
    return (false);
  return (stbuf.st_mode & S_IFDIR);
}

Decision		_bunny_handle_directive(const char		*code,
						ssize_t			&i,
						SmallConf		*node,
						t_bunny_configuration	*fileroot,
						void			(*read_separator)
						(const char*,ssize_t&))
{
  t_bunny_configuration_type fmt;
  DIR			*dir;
  struct dirent		*f;
  char			buffer[512];

  if (readtext(code, i, "@include") && fileroot)
    {
      read_separator(code, i);
      if (readstring(code, i, &buffer[0], sizeof(buffer)) == false)
	return (BD_ERROR);

      if (isdir("", &buffer[0]) == false)
	{
	  if (bunny_load_configuration
	      (bunny_which_format(&buffer[0]), &buffer[0], fileroot) == NULL)
	    scream_error_if(return (BD_ERROR), BE_SYNTAX_ERROR, PATTERN,
			    "ressource,configuration",
			    code, i, node, fileroot, "false", "Error while loading ",
			    &buffer[0], whichline(code, i));
	}
      else
	{
	  if ((dir = opendir(&buffer[0])) == NULL)
	    scream_error_if(return (BD_ERROR), bunny_errno, PATTERN,
			    "ressource,configuration",
			    code, i, node, fileroot, "false", "Error while opening directory ",
			    &buffer[0], whichline(code, i));
	  bunny_configuration_push_path(&buffer[0]);
	  bunny_errno = 0;
	  while ((f = readdir(dir)) != NULL)
	    {
	      if (bunny_errno)
		{
		  closedir(dir);
		  scream_error_if(return (BD_ERROR), bunny_errno, PATTERN,
				  "ressource,configuration",
				  code, i, node, fileroot, "false", "Error while browsing directory ",
				  &buffer[0], whichline(code, i));
		}
	      if (f->d_name[0] != '.' && isdir(&buffer[0], &f->d_name[0]) == false && (fmt = bunny_which_format(&f->d_name[0])) != BC_CUSTOM)
		if (bunny_load_configuration(fmt, &f->d_name[0], fileroot) == NULL)
		  {
		    closedir(dir);
		    scream_error_if(return (BD_ERROR), BE_SYNTAX_ERROR, PATTERN,
				    "ressource,configuration",
				    code, i, node, fileroot, "false", "Error while loading ",
				    &buffer[0], whichline(code, i));
		  }
	      bunny_errno = 0;
	    }
	  bunny_configuration_pop_path();
	}
    }
  else if (readtext(code, i, "@insert") && node)
    {
      read_separator(code, i);
      if (readstring(code, i, &buffer[0], sizeof(buffer)) == false)
	return (BD_ERROR);

      if (isdir("", &buffer[0]) == false)
	{
	  if (bunny_load_configuration
	      (bunny_which_format(&buffer[0]), &buffer[0], node) == NULL)
	    scream_error_if(return (BD_ERROR), BE_SYNTAX_ERROR, PATTERN,
			    "ressource,configuration",
			    code, i, node, fileroot, "false", "Error while loading ",
			    &buffer[0], whichline(code, i));
	}
      else
	{
	  if ((dir = opendir(&buffer[0])) == NULL)
	    scream_error_if(return (BD_ERROR), bunny_errno, PATTERN,
			    "ressource,configuration",
			    code, i, node, fileroot, "false", "Error while opening directory ",
			    &buffer[0], whichline(code, i));
	  bunny_configuration_push_path(&buffer[0]);
	  bunny_errno = 0;
	  while ((f = readdir(dir)) != NULL)
	    {
	      if (bunny_errno)
		{
		  closedir(dir);
		  scream_error_if(return (BD_ERROR), bunny_errno, PATTERN,
				  "ressource,configuration",
				  code, i, node, fileroot, "false", "Error while browsing directory ",
				  &buffer[0], whichline(code, i));
		}
	      if (f->d_name[0] != '.' && isdir(&buffer[0], &f->d_name[0]) == false && (fmt = bunny_which_format(&f->d_name[0])) != BC_CUSTOM)
		if (bunny_load_configuration(fmt, &f->d_name[0], node) == NULL)
		  {
		    closedir(dir);
		    scream_error_if(return (BD_ERROR), BE_SYNTAX_ERROR, PATTERN,
				    "ressource,configuration",
				    code, i, node, fileroot, "false", "Error while loading ",
				    &buffer[0], whichline(code, i));
		  }
	      bunny_errno = 0;
	    }
	  bunny_configuration_pop_path();
	}
    }
  else
    return (BD_NOT_FOUND);
  scream_log_if(PATTERN, "ressource,configuration",
		code, i, node, fileroot, "false", "Success", "", whichline(code, i));
  return (BD_OK);
}

