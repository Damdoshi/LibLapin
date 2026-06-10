// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2018
//
// Lapin library

#include		"lapin_private.h"

bool			SmallConf::create_mode = false;
std::stack<std::string>	SmallConf::file_read;
std::list<std::string>	SmallConf::file_path;
int			SmallConf::just_pushed;

/**
 * @doc
 * @doc-symbol bunny_new_configuration
 * @doc-kind function
 * @doc-module configuration
 * @doc-order 30
 * @doc-since 0
 * @doc-until latest
 * @doc-level beginner
 *
 * @doc-lang en
 * @brief Creates an empty configuration tree.
 * @return-success Returns a newly allocated $Tt_bunny_configuration@.
 * @return-failure Returns $CNULL@ if allocation fails.
 * @log "ressource,configuration"
 * @see bunny_delete_configuration
 *
 * @doc-lang fr
 * @brief Crée un arbre de configuration vide.
 * @return-success Renvoie un $Tt_bunny_configuration@ nouvellement alloué.
 * @return-failure Renvoie $CNULL@ si l’allocation échoue.
 * @log "ressource,configuration"
 * @see bunny_delete_configuration
 */
t_bunny_configuration	*bunny_new_configuration(void)
{
  SmallConf		*conf;

  try
    {
      conf = new SmallConf;
    }
  catch (...)
    {
      scream_error_if(return (NULL), ENOMEM, " -> %p", "ressource,configuration", (void*)NULL);
    }
  scream_log_if(" -> %p", "ressource,configuration", conf);
  return ((t_bunny_configuration*)conf);
}

