// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2018
//
// Bibliothèque Lapin

#include		"lapin_private.h"

/**
 * @doc
 * @doc-symbol bunny_init_box_environ
 * @doc-kind function
 * @doc-module context
 * @doc-order 480
 * @doc-since 0
 * @doc-until latest
 * @doc-level advanced
 *
 * @doc-lang en
 * @brief Creates a minimal configuration environment for a root GUI screen box.
 * @param width Screen width.
 * @param height Screen height.
 * @return-success Returns a newly allocated configuration tree.
 * @return-failure Returns $CNULL@ on error.
 * @see t_bunny_box_system
 *
 * @doc-lang fr
 * @brief Crée un environnement de configuration minimal pour une boîte écran racine.
 * @param width Screen width.
 * @param height Screen height.
 * @return-success Renvoie un arbre de configuration nouvellement alloué.
 * @return-failure Renvoie $CNULL@ en cas d’erreur.
 * @see t_bunny_box_system
 */
t_bunny_configuration	*bunny_init_box_environ(int		w,
						int		h)
{
  char			buffer[512];
  static const char	*screen = R"(
    [Screen
      Type="Box"
      Size=%d,%d
      Position=0,0
    ]
  )"; // "

  snprintf(&buffer[0], sizeof(buffer), screen, w, h);
  return (bunny_read_configuration(BC_DABSIC, &buffer[0], NULL));
}
