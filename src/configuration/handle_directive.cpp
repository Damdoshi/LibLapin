// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2018
//
// Lapin library

#include		<sys/stat.h>
#include		<dirent.h>
#include		<string.h>
#include		"lapin_private.h"

struct			Directive
{
  std::string		token;
  SmallConf		*node;
};

#define			PATTERN						\
  "'%.10s...' code, %zd i, %p node, %p fileroot -> %s (%s %s on line %d)"

Decision		dabsic_read_text_conf(const char		*code,
					      ssize_t			&i,
					      std::string		&vartok,
					      std::string		&eoftok,
					      std::string		&comtok);

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
						(const char*,ssize_t&),
						Expression::OperatorFamily family)
{
  Directive		directives[] = {
    {"@include", (SmallConf*)fileroot},
    {"@insert", (SmallConf*)node},
    {"@push", NULL}
  };
  int			directive;

  ////////////////////////////////////////////////////
  /// On cherche la directive qui nous concerne
  for (directive = 0;
       directive < NBRCELL(directives) &&
	 !readtext(code, i, directives[directive].token.c_str());
       ++directive);
  if (directive == NBRCELL(directives))
    return (BD_NOT_FOUND);
  read_separator(code, i);
  
  /////////////////////////////////////////////////////////
  // Il y a peut etre un spécificateur de format ensuite
  t_bunny_configuration_type type = BC_CUSTOM;
  int			l = i;

  if (readfield(code, i))
    {
      char		buffer[32] = {'.', 0};
      
      if (i - l < NBRCELL(buffer) - 1)
	strncpy(&buffer[1], &code[l], i - l);
      type = bunny_which_format(buffer);
    }
  read_separator(code, i);

  ///////////////////////////////////////////////////////
  // Il y a peut etre un configurateur de parseur après
  std::vector<std::string> conf;
  std::string		symbol;
  std::string		path;
  t_bunny_configuration	*chk;

  if (readtext(code, i, "("))
    {
      read_separator(code, i);
      
      // @directive txt [(vartok[,endtok[,comtok]])] "file"
      if (type == BC_TEXT)
	{
	  conf.resize(3);
	  if (dabsic_read_text_conf(code, i, conf[0], conf[1], conf[2]) == BD_ERROR)
	    return (BD_ERROR);
	  conf[1] = conf[1] + "]";
	}

      read_separator(code, i);
      if (!readtext(code, i, ")"))
	scream_error_if
	  (return (BD_ERROR), BE_SYNTAX_ERROR,
	   "The token ')' was expected to close the text terminator "
	   "specification for the directive "
	   "on line %s:%d",
	   "ressource,configuration,syntax",
	   SmallConf::file_read.top().c_str(), whichline(code, i)
	   );
    }
  read_separator(code, i);

  ///////////////////////////////////////////////////////////////
  // Ensuite il y a normalement une chaine de caractère
  // mais sous la forme d'une expression permettant l'utilisation de variables
  SmallConf		dirconf;
  const char		*tmp;

  if (expr_read_expression(code, i, dirconf, family)
      == BD_ERROR)
    return (BD_ERROR);
  read_separator(code, i);
  if (expr_compute(dirconf, NULL, false, (SmallConf*)bunny_configuration_get_root(node), (SmallConf*)node, NULL, NULL) == false)
    scream_error_if
      (return (BD_ERROR), BE_SYNTAX_ERROR, PATTERN,
       "ressource,configuration",
       code, i, node, fileroot, "false", "Cannot resolve directive ",
       directives[directive], whichline(code, i));
  dirconf.GetString(&tmp, (SmallConf*)bunny_configuration_get_root(node), (SmallConf*)node, NULL, NULL);

  std::string		filepath = tmp;
  const char		*res;

  if ((res = bunny_configuration_resolve_path(filepath.c_str())) == NULL)
    scream_error_if
      (return (BD_ERROR), BE_SYNTAX_ERROR, PATTERN,
       "ressource,configuration",
       code, i, node, fileroot, "false", "Cannot find file ",
       filepath.c_str(), whichline(code, i));

  ////////////////////////////////////////////////////////////////
  // Ensuite on regarde si la chaine contient un dossier ou un fichier
  // Si c'est un dossier, on recupère son contenu
  // Il serait interessant plus tard de permettre de spécifier un
  // chargement récursif
  std::vector<std::string> flist;
  
  if (isdir("", res))
    {
      struct dirent	*f;
      DIR		*dir;

      if ((dir = opendir(res)) == NULL)
	scream_error_if
	  (return (BD_ERROR), bunny_errno, PATTERN,
	   "ressource,configuration",
	   code, i, node, fileroot, "false", "Error while opening directory ",
	   res, whichline(code, i));
      bunny_configuration_push_path(res);
      bunny_errno = 0;
      while ((f = readdir(dir)) != NULL)
	{
	  if (bunny_errno)
	    {
	      closedir(dir);
	      scream_error_if
		(return (BD_ERROR), bunny_errno, PATTERN,
		 "ressource,configuration",
		 code, i, node, fileroot, "false",
		 "Error while browsing directory ",
		 res, whichline(code, i));
	    }
	  if (f->d_name[0] != '.' && isdir(res, &f->d_name[0]) == false)
	    flist.push_back(f->d_name);
	}
    }
  else
    flist.push_back(res);

  ////////////////////////////////////////////////////////////////////////
  // On parcoure l'ensemble des fichiers qui doivent etre chargé
  for (auto it = flist.begin(); it != flist.end(); ++it)
    {
      // Si on @push, alors il faut ajouter au tableau chaque fichier
      if (directive == 2)
	{
	  int		len = bunny_configuration_childrenf(node, ".");
	  bool		cmode = SmallConf::create_mode;
      
	  SmallConf::create_mode = true;
	  bunny_configuration_getf_node
	    (node, (t_bunny_configuration**)&directives[directive].node, "[%d]", len);
	  SmallConf::create_mode = cmode;
	}

      if (type == BC_CUSTOM)
	chk = bunny_open_configuration(it->c_str(), directives[directive].node);
      else if (type == BC_TEXT)
	chk = bunny_load_configuration
	  (type, it->c_str(), directives[directive].node,
	   conf[0].c_str(), conf[1].c_str(), conf[2].c_str()
	   );
      else
	chk = bunny_load_configuration(type, it->c_str(), directives[directive].node);
      if (!chk)
	scream_error_if
	  (return (BD_ERROR), BE_SYNTAX_ERROR, PATTERN,
	   "ressource,configuration",
	   code, i, node, fileroot, "false", "Error while loading ",
	   it->c_str(), whichline(code, i));
    }
  
  scream_log_if
    (PATTERN, "ressource,configuration",
     code, i, node, fileroot, "false", "Success", "", whichline(code, i));
  return (BD_OK);
}

