// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2020
//
// LibLapin

#include		"lapin_private.h"

t_bunny_graph_node	*bunny_graph_get_node(t_bunny_graph		*g,
					      const char		*id)
{
  return (bunny_map_get_data(g->nodes, id, t_bunny_graph_node*));
}

