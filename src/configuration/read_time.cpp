// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2018
//
// Lapin library

#include	"lapin_private.h"

#define		PATTERN		"%p, %s, %p -> %s"

/**
 * @doc
 * @doc-symbol bunny_configuration_read_time
 * @doc-kind function
 * @doc-module configuration
 * @doc-order 615
 * @doc-since 0
 * @doc-until latest
 * @doc-level advanced
 *
 * @doc-lang en
 * @brief Reads a duration field from a configuration node.
 * @param cnf Configuration node to inspect.
 * @param fld Field name.
 * @param secs Output duration in seconds.
 * @return-success Returns $Ctrue@ and stores the duration.
 * @return-failure Returns $Cfalse@ on missing or invalid field.
 * @log "configuration"
 *
 * @doc-lang fr
 * @brief Lit un champ de durée depuis un nœud de configuration.
 * @param cnf Configuration node to inspect.
 * @param fld Field name.
 * @param secs Output duration in seconds.
 * @return-success Renvoie $Ctrue@ et stocke la durée.
 * @return-failure Renvoie $Cfalse@ si le champ est absent ou invalide.
 * @log "configuration"
 */
bool		bunny_configuration_read_time(const t_bunny_configuration	*_cnf,
					      const char			*field,
					      double				*out)
{
  SmallConf	*cnf = (SmallConf*)_cnf;

  if (!cnf || !cnf->Access(field))
    scream_error_if
      (return (false), EINVAL,
       PATTERN ": A configuration and a field '%s' were expected.",
       "ressource,sound_sprite,syntax", _cnf, field, out, "false", field);
  SmallConf	&arr = (*cnf)[field];
  double	tmp;
  int		index = 0;

  *out = 0;
  switch (arr.Size())
    {
    case 3:
      if (arr[index].GetDouble(&tmp) == false)
	goto end;
      index += 1;
      *out += (int)tmp * 60 * 60;
      [[fallthrough]];
    case 2:
      if (arr[index].GetDouble(&tmp) == false)
	goto end;
      index += 1;
      *out += (int)tmp * 60;
      [[fallthrough]];
    case 1:
      if (arr[index].GetDouble(&tmp) == false)
	goto end;
      *out += tmp;
      return (true);
    case 0:
      if (arr.GetDouble(out) == false)
	goto end;
      return (true);
    default:
      break ;
    }
 end:
  scream_error_if
    (return (false), BE_SYNTAX_ERROR,
     PATTERN ": [seconds], [minutes, seconds] or [hours, minutes, seconds] was "
     "expected as time format."
     , "ressource,sound_sprite,syntax", _cnf, field, out, "false");
  return (false);
}

