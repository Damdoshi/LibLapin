// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2020
//
// LibLapin

#include		"lapin_private.h"

static bool		read_shape(t_bunny_space_node			*nod,
				   t_bunny_configuration		*shape)
{
  (void)nod;
  (void)shape;
  return (NULL);
}

static bool		add_graph_node(t_bunny_graph			*graph,
				       t_bunny_configuration		*cnf)
{
  t_bunny_configuration	*shape;
  t_bunny_accurate_position pos;
  t_bunny_graph_node	*nod;

  if (bunny_accurate_position_configuration("Position", &pos, cnf) == BD_OK)
    { // Dot node
      t_bunny_dot_node *dot;

      if ((dot = (t_bunny_dot_node*)bunny_malloc(sizeof(*dot))) == NULL)
	return (false);
      dot->node.type = GNT_DOT;
      dot->position = pos;
      nod = &dot->node;
    }
  else if (bunny_configuration_getf_node(cnf, &shape, "Shape"))
    { // Space node
      t_bunny_space_node *space;

      if ((space = (t_bunny_space_node*)bunny_malloc(sizeof(*space))) == NULL)
	return (false);
      space->node.type = GNT_SPACE;
      if (read_shape(space, shape) == false)
	{
	  bunny_free(space);
	  return (false);
	}
      nod = &space->node;
    }
  else
    { // Simple node
      if ((nod = (t_bunny_graph_node*)bunny_malloc(sizeof(*nod))) == NULL)
	return (false);
      nod->type = GNT_SIMPLE;
    }

  // Propriété générale
  if (bunny_configuration_getf_string(cnf, &nod->id, "Name") == false)
    nod->id = bunny_configuration_get_name(cnf);
  nod->configuration = cnf;
  nod->data = NULL;
  nod->nbr_io = 0;

  if (bunny_map_set_data(graph->nodes, nod->id, nod, t_bunny_graph_node*) == NULL)
    {
      bunny_free(nod);
      return (false);
    }
  return (true);
}

static bool		add_graph_link(t_bunny_graph			*graph,
				       t_bunny_configuration		*cnf)
{
  (void)graph;
  (void)cnf;
  return (false);
}

t_bunny_graph		*bunny_read_graph(t_bunny_configuration		*cnf)
{
  t_bunny_graph		*graph = (t_bunny_graph*)bunny_malloc(sizeof(*graph));
  t_bunny_map		**mapnode;

  if ((graph->nodes = bunny_new_map(string_map)) == NULL)
    {
      bunny_free(graph);
      return (NULL);
    }
  if (bunny_configuration_getf_string(cnf, &graph->name, "Name") == false)
    graph->name = "";
  graph->own_configuration = false;
  graph->configuration = cnf;
  t_bunny_configuration	*nodes;
  t_bunny_configuration *subnode;
  int			i;

  if (!bunny_configuration_getf_node(cnf, &nodes, "Nodes"))
    return (graph);
  for (bunny_configuration_all_children(nodes, subnode))
    if (add_graph_node(graph, subnode) == false)
      goto Error;
  for (i = 0; bunny_configuration_getf_node(cnf, &subnode, "[%d]", i); ++i)
    if (add_graph_node(graph, subnode) == false)
      goto Error;

  for (bunny_configuration_all_children(nodes, subnode))
    if (add_graph_link(graph, subnode) == false)
      goto Error;
  for (i = 0; bunny_configuration_getf_node(cnf, &subnode, "[%d]", i); ++i)
    if (add_graph_link(graph, subnode) == false)
      goto Error;

  return (graph);
 Error:

  for (bunny_map_all(graph->nodes, mapnode))
    {
      t_bunny_graph_node *x = bunny_map_data(*mapnode, t_bunny_graph_node*);

      bunny_free(x);
    }
  // Supprimer les noeuds
  bunny_delete_map(graph->nodes);
  bunny_free(graph);
  return (NULL);
}

