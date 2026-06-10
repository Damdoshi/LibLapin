// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2018
//
// Lapin library

#include		"lapin_private.h"

static int		error_descriptor = -1;


/**
 * @doc
 * @doc-symbol bunny_set_error_descriptor
 * @doc-kind function
 * @doc-module error
 * @doc-order 180
 * @doc-since 0
 * @doc-until latest
 * @doc-level 20
 *
 * @doc-lang en
 * @brief Sets the file descriptor used for error logs.
 * @param fd File descriptor to use, or a negative value to disable error logs.
 * @see bunny_get_error_descriptor
 *
 * @doc-lang fr
 * @brief Définit le descripteur de fichier utilisé pour les logs d’erreur.
 * @param fd Descripteur de fichier à utiliser, ou valeur négative pour désactiver les logs d’erreur.
 * @see bunny_get_error_descriptor
 */
void			bunny_set_error_descriptor(int	fd)
{
  error_descriptor = fd;
}


/**
 * @doc
 * @doc-symbol bunny_get_error_descriptor
 * @doc-kind function
 * @doc-module error
 * @doc-order 200
 * @doc-since 0
 * @doc-until latest
 * @doc-level 20
 *
 * @doc-lang en
 * @brief Gets the file descriptor used for error logs.
 * @return-success Returns the current error log file descriptor.
 * @see bunny_set_error_descriptor
 *
 * @doc-lang fr
 * @brief Récupère le descripteur de fichier utilisé pour les logs d’erreur.
 * @return-success Renvoie le descripteur de fichier courant des logs d’erreur.
 * @see bunny_set_error_descriptor
 */
int			bunny_get_error_descriptor(void)
{
  return (error_descriptor);
}


