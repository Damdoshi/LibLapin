// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2018
//
// Lapin library

#include		"lapin_private.h"

#define			PATTERN		"%d type, %s file, %p config -> %s"

/**
 * @doc
 * @doc-symbol bunny_save_configuration
 * @doc-kind function
 * @doc-module configuration
 * @doc-order 60
 * @doc-since 0
 * @doc-until latest
 * @doc-level beginner
 *
 * @doc-lang en
 * @brief Saves a configuration tree into a file using the requested format.
 * @param type Format used to serialize the tree.
 * @param file Destination file path.
 * @param config Configuration tree to save.
 * @return-success Returns $Ctrue@ on success.
 * @return-failure Returns $Cfalse@ on serialization or file error.
 * @log "ressource,configuration"
 * @see bunny_write_configuration
 *
 * @doc-lang fr
 * @brief Sauvegarde un arbre de configuration dans un fichier avec le format demandé.
 * @param type Format used to serialize the tree.
 * @param file Destination file path.
 * @param config Configuration tree to save.
 * @return-success Renvoie $Ctrue@ en cas de succès.
 * @return-failure Renvoie $Cfalse@ en cas d’erreur de sérialisation ou de fichier.
 * @log "ressource,configuration"
 * @see bunny_write_configuration
 */
bool			bunny_save_configuration(t_bunny_configuration_type		type,
						 const char				*file,
						 t_bunny_configuration			*config)
{
  char			*code;
  bool			out;
  int			len;

  if ((code = bunny_write_configuration(type, config)) == NULL)
    scream_error_if
      (return (false), bunny_errno, PATTERN, "ressource,configuration",
       type, file, config, "false");
  len = strlen(code);
  if (gl_bunny_ressource_ciphering)
    gl_bunny_ressource_ciphering
      (code, len, gl_bunny_ressource_data, true);
  out = bunny_save_file(file, code, len);
  bunny_free(code);
  if (!out)
    scream_error_if
      (return (false), bunny_errno, PATTERN, "ressource,configuration",
       type, file, config, "false");
  scream_log_if(PATTERN, "ressource,configuration", type, file, config, "true");
  return (out);
}

