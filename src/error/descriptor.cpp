// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2018
//
// Lapin library

#include		"lapin_private.h"

static int		log_descriptor = -1;


/**
 * @doc
 * @doc-symbol bunny_set_log_descriptor
 * @doc-kind function
 * @doc-module error
 * @doc-order 220
 * @doc-since 0
 * @doc-until latest
 * @doc-level 20
 *
 * @doc-lang en
 * @brief Sets the file descriptor used for normal logs.
 * @param fd File descriptor to use, or a negative value to disable logs.
 * @see bunny_get_log_descriptor
 *
 * @doc-lang fr
 * @brief Définit le descripteur de fichier utilisé pour les logs normaux.
 * @param fd Descripteur de fichier à utiliser, ou valeur négative pour désactiver les logs.
 * @see bunny_get_log_descriptor
 */
void			bunny_set_log_descriptor(int	fd)
{
  log_descriptor = fd;
}


/**
 * @doc
 * @doc-symbol bunny_get_log_descriptor
 * @doc-kind function
 * @doc-module error
 * @doc-order 240
 * @doc-since 0
 * @doc-until latest
 * @doc-level 20
 *
 * @doc-lang en
 * @brief Gets the file descriptor used for normal logs.
 * @return-success Returns the current normal log file descriptor.
 * @see bunny_set_log_descriptor
 *
 * @doc-lang fr
 * @brief Récupère le descripteur de fichier utilisé pour les logs normaux.
 * @return-success Renvoie le descripteur de fichier courant des logs normaux.
 * @see bunny_set_log_descriptor
 */
int			bunny_get_log_descriptor(void)
{
  return (log_descriptor);
}


