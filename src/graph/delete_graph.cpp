// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2020
//
// LibLapin

#include		"lapin_private.h"

void			bunny_delete_graph(t_bunny_graph	*graph,
					   void			(*dtor)
					   (const char		*id,
					    t_bunny_configuration	*cnf,
					    void			*d))
{
  t_bunny_map		**mapnode;

  if (graph->nodes)
    {
      for (bunny_map_all(graph->nodes, mapnode))
	{
	  t_bunny_graph_node *x = bunny_map_data(*mapnode, t_bunny_graph_node*);

	  if (x->data && dtor)
	    dtor(x->id, x->configuration, x->data);
	  bunny_free(x);
	}
      bunny_delete_map(graph->nodes);
    }
  bunny_free(graph);
}
