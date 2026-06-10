// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2018
//
// Lapin Library

#include		"lapin_private.h"

/**
 * @doc
 * @doc-symbol _bunny_add_monitored_value
 * @doc-kind function
 * @doc-module monitor
 * @doc-order 125
 * @doc-since 12
 * @doc-until latest
 * @doc-level 30
 *
 * @doc-lang en
 * @brief Registers a typed value in the debug monitor.
 * @description _bunny_add_monitored_value is the function behind the C11 bunny_add_monitored_value macro. It registers ptr under name and uses type to know how it must be displayed later.
 * @description No copy is made, neither for name nor for ptr. The pointed variable must remain alive as long as it is registered.
 * @param name The name of the monitored value.
 * @param type The type of the pointed value.
 * @param ptr The pointer to monitor. It must match type: char* for BMT_STRING, int* for BMT_INTEGER and double* for BMT_DOUBLE.
 * @return-case success On $Bsuccess@, returns true.
 * @return-case failure On $Bfailure@, returns false.
 * @error ENOMEM Historically documented for allocation failure while registering the value. The current implementation returns false when the C++ map insertion throws, without explicitly setting bunny_errno.
 * @see t_bunny_monitored_type
 * @see bunny_add_monitored_value
 * @see bunny_remove_monitored_value
 *
 * @doc-lang fr
 * @brief Enregistre une valeur typée dans le moniteur de débogage.
 * @description _bunny_add_monitored_value est la fonction utilisée par la macro C11 bunny_add_monitored_value. Elle enregistre ptr sous name et utilise type pour savoir comment l'afficher plus tard.
 * @description Aucune copie n'est faite, ni pour name ni pour ptr. La variable pointée doit rester vivante tant qu'elle est enregistrée.
 * @param name Le nom de la valeur surveillée.
 * @param type Le type de la valeur pointée.
 * @param ptr Le pointeur à surveiller. Il doit correspondre à type : char* pour BMT_STRING, int* pour BMT_INTEGER et double* pour BMT_DOUBLE.
 * @return-case success En cas de $Bsuccès@, renvoie true.
 * @return-case failure En cas d'$Béchec@, renvoie false.
 * @error ENOMEM Historiquement documenté pour un échec d'allocation lors de l'enregistrement de la valeur. L'implémentation courante renvoie false lorsque l'insertion dans la map C++ lève une exception, sans renseigner explicitement bunny_errno.
 * @see t_bunny_monitored_type
 * @see bunny_add_monitored_value
 * @see bunny_remove_monitored_value
 */
bool			_bunny_add_monitored_value(const char		*name,
						   t_bunny_monitored_type type,
						   const void		*ptr)
{
  struct bunny_monitored_value v;

  try
    {
      v.type = type;
      v.data = ptr;
      gl_monitor[std::string(name)] = v;
    }
  catch (...)
    {
      return (false);
    }
  return (true);
}

