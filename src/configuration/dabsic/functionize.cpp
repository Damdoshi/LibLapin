// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2024
// Pentacle Technologie 2008-2024
// EFRITS 2022-2024
//
// Bibliothèque Lapin

#include		"lapin_private.h"

// Chaque element, enfant et cases, devient une fonction dont les paramètres
// seront params: ceux du noeud contenant
// seront root: root
// seront local: le contenant du noeud en question
// seront artif: le noeud a l'origine de la transformation
//
// Si un noeud est deja une fonction, ca crache une erreur
//
// En gros, un node ou un tableau qui est une fonction
// est une fonction qui se renvoi lui meme ajusté de ses paramètres
// et du contexte
/*
  conf.function = new Function;
  conf.function->parent_node = &conf;
  conf.function->nbr_lines = 0;
  for (size_t i = 0; i < conf.Size(); ++i)
  {
  conf.function->value[conf.function->value.Size()].expression = conf[i].expression;
  conf.function->nbr_lines += 1;
  }
*/

bool			dabsic_functionize(SmallConf		&funcroot,
					   SmallConf		&node)
{
  if (&funcroot != &node)
    {
      if (node.Access(".prototype"))
	scream_error_if
	  (return (false), BE_SYNTAX_ERROR,
	   "A function (%s) cannot be declared inside another function (%s).",
	   "ressource,configuration,syntax",
	   node.address, funcroot.address
	   );
      SmallConf::RecursiveAssign(node[".prototype"], funcroot[".prototype"]);
    }
  for (auto it = node.nodes.begin(); it != node.nodes.end(); ++it)
    if (it->second->name[0] != '.')
      if (dabsic_functionize(funcroot, *it->second) == false)
	return (false);
  for (auto it = node.array.begin(); it != node.array.end(); ++it)
    if (dabsic_functionize(funcroot, **it) == false)
      return (false);
  return (true);
}

