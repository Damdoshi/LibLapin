/*
** Jason Brillante "Damdoshi"
** Hanged Bunny Studio 2014-2020
**
** Bibliotheque Lapin
**
** Built to serve for:
** - The Bunny Adventure game engine, to define walkable path and make characters walk.
**   Graph can be 5-50 nodes wide in this context (depending on how wide is a single landscape)
** - Allan, mainly for the space_node ability to define random shape and collide, there may be
     1-10 nodes.
**   that can be used to define room-sized limitation for camera (in a pretty overkill way)
** - Macroboy Y, for the same reason plus the ability to use it for doing a "camera rail"
**   thanks to the ability to find the closest inbetween point.
**
*/

#ifndef				__LAPIN_GRAPH_H__
# define			__LAPIN_GRAPH_H__

struct				s_bunny_graph_node;

typedef enum			e_bunny_graph_node_type
  {
   GNT_SIMPLE,
   GNT_DOT,
   GNT_SPACE
  }				t_bunny_graph_node_type;

typedef struct			s_bunny_space_node_shape
{
  t_bunny_accurate_position	center;
  t_bunny_accurate_position	position[15];
  size_t			nbr_position;
}				t_bunny_space_node_shape;

typedef struct			s_bunny_space_node_io
{
  t_bunny_accurate_position	position;		// Position of the i/o on the current space node
  struct s_bunny_graph_node	*link;			// Link to a target node
  int				number;			// If the target is a space node, precise the io
  t_bunny_configuration		*configuration;		// Configuration of the link - if requested
  void				*data;			// To be allocated, filled and freed by user.
}				t_bunny_space_node_io;

// The base struct of a graph node, to be derived from (or not)
typedef struct			s_bunny_graph_node
{
  t_bunny_graph_node_type	type;
  const char			*id;
  t_bunny_space_node_io		io[32];
  size_t			nbr_io;
  t_bunny_configuration		*configuration;
  void				*data;			// To be allocated, filled and free by user.
}				t_bunny_graph_node;

typedef struct			s_bunny_space_node
{
  t_bunny_graph_node		node;
  t_bunny_space_node_shape	shape[8];
  size_t			nbr_shape;
}				t_bunny_space_node;

typedef struct			s_bunny_dot_node
{
  t_bunny_graph_node		node;
  t_bunny_accurate_position	position;
}				t_bunny_dot_node;

typedef struct			s_bunny_graph
{
  t_bunny_map			*nodes;		// string -> t_bunny_graph_node and derivates
  const char			*name;
  t_bunny_configuration		*configuration;
  bool				own_configuration;
}				t_bunny_graph;

t_bunny_graph			*bunny_load_graph(const char				*file);
t_bunny_graph			*bunny_read_graph(t_bunny_configuration			*cnf);
void				bunny_delete_graph(t_bunny_graph			*graph,
						   void					(*dtor)
						   (const char				*id,
						    t_bunny_configuration		*cnf,
						    void				*d));
int				bunny_graph_dump(t_bunny_graph				*graph);

t_bunny_graph_node		*bunny_graph_get_node(t_bunny_graph			*graph,
						      const char			*id);

t_bunny_graph_node		*bunny_graph_collide_node(t_bunny_graph			*graph,
							  t_bunny_accurate_position	pos);
bool				bunny_graph_collide_space(t_bunny_space_node		*node,
							  t_bunny_accurate_position	pos);

typedef struct			s_bunny_graph_path
{
  t_bunny_graph_node		*steps[64];		// 0 is target, nbr_node - 1 the current pos
  size_t			nbr_node;
  t_bunny_accurate_position	current_position;	// The current position in pixel
}				t_bunny_graph_path;

bool				bunny_graph_set_travel(t_bunny_graph			*graph,
						       t_bunny_graph_path		*path,
						       const char			*start,
						       const t_bunny_accurate_position	*curpos,
						       const char			*target);
bool				bunny_graph_travel(t_bunny_graph_path			*path,
						   t_bunny_accurate_position		*new_pos,
						   double				speed);
bool				bunny_graph_get_closest_step(t_bunny_graph		*graph,
							     t_bunny_graph_path		*path,
							     t_bunny_accurate_position	pos);
void				bunny_graph_path_dump(t_bunny_graph_path		*path);

#endif	/*		__LAPIN_GRAPH_H__						*/
