/*
** Jason Brillante "Damdoshi"
** Hanged Bunny Studio 2014-2020
**
** LibLapin Test
*/

#include		<assert.h>
#include		<lapin.h>

int			main(void)
{
  t_bunny_graph		*graph;

  assert((graph = bunny_load_graph("./graph.dab")));
  bunny_delete_graph(graph);
  return (0);
}

