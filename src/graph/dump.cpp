// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2020
//
// LibLapin

#include		"lapin_private.h"

int			bunny_graph_dump(t_bunny_graph		*graph)
{
  t_bunny_map		**mapnode;
  int			cnt = 0;

  for (bunny_map_all(graph->nodes, mapnode))
    {
      t_bunny_graph_node *x = bunny_map_data(*mapnode, t_bunny_graph_node*);

      cnt += printf("Node %s\n", x->id);
      cnt += printf(" Type: %d\n", x->type);
      if (x->type == GNT_DOT)
	{
	  t_bunny_dot_node *d = (t_bunny_dot_node*)x;

	  cnt += printf(" Position: %.2f, %.2f\n", d->position.x, d->position.y);
	}
      else if (x->type == GNT_SPACE)
	{
	  t_bunny_space_node *d = (t_bunny_space_node*)x;

	  for (size_t i = 0; i < d->nbr_shape; ++i)
	    {
	      cnt += printf(" Shape: %.2f, %.2f\n", d->shape[i].center.x, d->shape[i].center.y);
	      for (size_t j = 0; j < d->shape[i].nbr_position; ++j)
		cnt += printf("  %.2f, %.2f\n", d->shape[i].position[j].x, d->shape[i].position[j].y);
	    }
	}
      cnt += printf(" IO:\n");
      for (size_t i = 0; i < x->nbr_io; ++i)
	{
	  cnt += printf("  ");
	  if (x->type == GNT_SPACE)
	    {
	      cnt += printf("Position(%.2f, %.2f) ", x->io[i].position.x, x->io[i].position.y);
	      cnt += printf("Number(%d) ", x->io[i].number);
	    }
	  cnt += printf("Target(%s)\n", x->io[i].link->id);
	}
    }
  return (cnt);
}
