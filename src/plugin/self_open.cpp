// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2018
//
// Lapin library

#include		"lapin_private.h"

/**
 * @doc
 * @doc-symbol bunny_plugin_self_open
 * @doc-kind function
 * @doc-module plugin
 * @doc-order 260
 * @doc-since 13
 * @doc-until latest
 * @doc-level 40
 *
 * @doc-lang en
 * @brief Opens a dynamic-library handle on the current process.
 * @description bunny_plugin_self_open opens the current program image as a dynamic-library handle and caches the result for later calls.
 * @return-case success On $Bsuccess@, returns a handle that can be used to retrieve symbols from the current process.
 * @return-case failure On $Bfailure@, returns NULL.
 * @see bunny_plugin_get_self_function
 * @see bunny_plugin_get_function
 *
 * @doc-lang fr
 * @brief Ouvre un handle de bibliothèque dynamique sur le processus courant.
 * @description bunny_plugin_self_open ouvre l'image du programme courant comme un handle de bibliothèque dynamique et met le résultat en cache pour les appels suivants.
 * @return-case success En cas de $Bsuccès@, renvoie un handle utilisable pour récupérer des symboles du processus courant.
 * @return-case failure En cas d'$Béchec@, renvoie NULL.
 * @see bunny_plugin_get_self_function
 * @see bunny_plugin_get_function
 */
void			*bunny_plugin_self_open(void)
{
  static bool		opened = false;
  static void		*self_handler;

  if (opened == false)
    {
#if			_WIN32 || __WIN32__
      if ((self_handler = LoadLibrary(NULL)) == NULL)
#else
      if ((self_handler = dlopen(NULL, RTLD_NOW)) == NULL)
#endif
	return (NULL);
      opened = true;
    }
  return (self_handler);
}

/**
 * @doc
 * @doc-symbol bunny_plugin_get_self_function
 * @doc-kind function
 * @doc-module plugin
 * @doc-order 280
 * @doc-since 13
 * @doc-until latest
 * @doc-level 40
 *
 * @doc-lang en
 * @brief Retrieves a symbol from the current process.
 * @description bunny_plugin_get_self_function uses bunny_plugin_self_open and retrieves the symbol named n from the current program image.
 * @param n The name of the function or symbol to fetch from the current process.
 * @return-case success On $Bsuccess@, returns the address of the requested symbol. You must cast it to the correct type yourself.
 * @return-case failure On $Bfailure@, returns NULL if the current process cannot be opened or if n cannot be found.
 * @see bunny_plugin_self_open
 * @see bunny_plugin_get_function
 *
 * @doc-lang fr
 * @brief Récupère un symbole depuis le processus courant.
 * @description bunny_plugin_get_self_function utilise bunny_plugin_self_open et récupère le symbole nommé n depuis l'image du programme courant.
 * @param n Le nom de la fonction ou du symbole à récupérer depuis le processus courant.
 * @return-case success En cas de $Bsuccès@, renvoie l'adresse du symbole demandé. Vous devez le convertir vous-même vers le bon type.
 * @return-case failure En cas d'$Béchec@, renvoie NULL si le processus courant ne peut pas être ouvert ou si n est introuvable.
 * @see bunny_plugin_self_open
 * @see bunny_plugin_get_function
 */
void			*bunny_plugin_get_self_function(const char	*n)
{
  void			*x = bunny_plugin_self_open();

  if (!x)
    return (x);
#if			_WIN32 || __WIN32__
  return ((void*)GetProcAddress((HMODULE)x, n));
#else
  return (dlsym(x, n));
#endif
}

