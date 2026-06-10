// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2018
//
// Bibliothèque Lapin

#include	"lapin_private.h"


/**
 * @doc
 * @doc-symbol bunny_position_configuration
 * @doc-kind function
 * @doc-module placement
 * @doc-order 300
 * @doc-since 12
 * @doc-until latest
 * @doc-level 20
 *
 * @doc-lang en
 * @brief Reads an integer position from a two-entry configuration array.
 * @param field The field name to read.
 * @param pos The output position.
 * @param cnf The configuration node to read from.
 * @return-case success BD_OK on success, BD_NOT_FOUND if the first component is missing, BD_ERROR if the second component is missing.
 * @see t_bunny_position, t_bunny_area
 *
 * @doc-lang fr
 * @brief Lit une position entière depuis un tableau de configuration à deux entrées.
 * @param field Le nom du champ à lire.
 * @param pos La position de sortie.
 * @param cnf Le noeud de configuration à lire.
 * @return-case success BD_OK en cas de succès, BD_NOT_FOUND si le premier composant manque, BD_ERROR si le second composant manque.
 * @see t_bunny_position, t_bunny_area
 */

t_bunny_decision bunny_position_configuration(const char			*field,
					      t_bunny_position			*pos,
					      t_bunny_configuration		*cnf)
{
  if (bunny_configuration_getf_int(cnf, &pos->x, "%s[0]", field) == false)
    return (BD_NOT_FOUND);
  if (bunny_configuration_getf_int(cnf, &pos->y, "%s[1]", field) == false)
    return (BD_ERROR);
  return (BD_OK);
}


/**
 * @doc
 * @doc-symbol bunny_position_bind_configuration
 * @doc-kind function
 * @doc-module placement
 * @doc-order 320
 * @doc-since 12
 * @doc-until latest
 * @doc-level 20
 *
 * @doc-lang en
 * @brief Reads an integer position and binds it to a configuration array.
 * @param field The field name to read and bind.
 * @param pos The output position.
 * @param cnf The configuration node to read from and bind to.
 * @return-case success BD_OK on success, BD_NOT_FOUND if the first component is missing, BD_ERROR if the second component is missing.
 * @see t_bunny_position, t_bunny_area
 *
 * @doc-lang fr
 * @brief Lit une position entière et la lie à un tableau de configuration.
 * @param field Le nom du champ à lire et lier.
 * @param pos La position de sortie.
 * @param cnf Le noeud de configuration à lire et auquel lier.
 * @return-case success BD_OK en cas de succès, BD_NOT_FOUND si le premier composant manque, BD_ERROR si le second composant manque.
 * @see t_bunny_position, t_bunny_area
 */

t_bunny_decision bunny_position_bind_configuration(const char			*field,
						   t_bunny_position		*pos,
						   t_bunny_configuration	*cnf)
{
  if (bunny_configuration_bindf_int(cnf, &pos->x, "%s[0]", field) == false)
    return (BD_NOT_FOUND);
  if (bunny_configuration_bindf_int(cnf, &pos->y, "%s[1]", field) == false)
    return (BD_ERROR);
  return (BD_OK);
}


/**
 * @doc
 * @doc-symbol bunny_accurate_position_configuration
 * @doc-kind function
 * @doc-module placement
 * @doc-order 340
 * @doc-since 12
 * @doc-until latest
 * @doc-level 20
 *
 * @doc-lang en
 * @brief Reads a floating-point position from a two-entry configuration array.
 * @param field The field name to read.
 * @param pos The output position.
 * @param cnf The configuration node to read from.
 * @return-case success BD_OK on success, BD_NOT_FOUND if the first component is missing, BD_ERROR if the second component is missing.
 * @see t_bunny_position, t_bunny_area
 *
 * @doc-lang fr
 * @brief Lit une position flottante depuis un tableau de configuration à deux entrées.
 * @param field Le nom du champ à lire.
 * @param pos La position de sortie.
 * @param cnf Le noeud de configuration à lire.
 * @return-case success BD_OK en cas de succès, BD_NOT_FOUND si le premier composant manque, BD_ERROR si le second composant manque.
 * @see t_bunny_position, t_bunny_area
 */

t_bunny_decision bunny_accurate_position_configuration(const char		*field,
						       t_bunny_accurate_position *pos,
						       t_bunny_configuration	*cnf)
{
  if (bunny_configuration_getf_double(cnf, &pos->x, "%s[0]", field) == false)
    return (BD_NOT_FOUND);
  if (bunny_configuration_getf_double(cnf, &pos->y, "%s[1]", field) == false)
    return (BD_ERROR);
  return (BD_OK);
}


/**
 * @doc
 * @doc-symbol bunny_accurate_position_bind_configuration
 * @doc-kind function
 * @doc-module placement
 * @doc-order 360
 * @doc-since 12
 * @doc-until latest
 * @doc-level 20
 *
 * @doc-lang en
 * @brief Reads a floating-point position and binds it to a configuration array.
 * @param field The field name to read and bind.
 * @param pos The output position.
 * @param cnf The configuration node to read from and bind to.
 * @return-case success BD_OK on success, BD_NOT_FOUND if the first component is missing, BD_ERROR if the second component is missing.
 * @see t_bunny_position, t_bunny_area
 *
 * @doc-lang fr
 * @brief Lit une position flottante et la lie à un tableau de configuration.
 * @param field Le nom du champ à lire et lier.
 * @param pos La position de sortie.
 * @param cnf Le noeud de configuration à lire et auquel lier.
 * @return-case success BD_OK en cas de succès, BD_NOT_FOUND si le premier composant manque, BD_ERROR si le second composant manque.
 * @see t_bunny_position, t_bunny_area
 */

t_bunny_decision bunny_accurate_position_bind_configuration(const char		*field,
							    t_bunny_accurate_position *pos,
							    t_bunny_configuration *cnf)
{
  if (bunny_configuration_bindf_double(cnf, &pos->x, "%s[0]", field) == false)
    return (BD_NOT_FOUND);
  if (bunny_configuration_bindf_double(cnf, &pos->y, "%s[1]", field) == false)
    return (BD_ERROR);
  return (BD_OK);
}

