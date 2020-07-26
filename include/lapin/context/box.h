/*
** Jason Brillante "Damdoshi"
** Hanged Bunny Studio 2014-2018
**
** Bibliotheque Lapin
*/

/*!
** \file box.h
**
*/

#ifndef				__LAPIN_BOX_H__
# define			__LAPIN_BOX_H__
# if				!defined(__LAPIN_H__)
#  error			You cannot include this file directly.
# endif

struct s_bunny_box_system;

typedef enum			e_bunny_box_type
  {
    BBT_SIMPLE_BOX,
    BBT_LABEL_BOX,
    BBT_BROWSE_BOX,
    BBT_CUSTOM_BOX
  }				t_bunny_box_type;

extern const char		*gl_bunny_box_type[BBT_CUSTOM_BOX];

typedef enum			e_bunny_picture_display_mode
  {
    BPDM_STRETCH,
    BPDM_MAXIMIZE,
    BPDM_FIT
  }				t_bunny_picture_display_mode;

// Common base
typedef struct			s_bunny_gui_box
{
  t_bunny_box_type		type;
  const char			*id;
  struct s_bunny_gui_box	*parent;
  t_bunny_configuration		*configuration;
  bool				inactive; // Do not respond to events, neither children
  bool				hidden; // Is not displayed, neither children

  t_bunny_map			*children; // Map of string->t_bunny_gui_box
  t_bunny_accurate_position	position; // Relative au parent
  t_bunny_accurate_size		size;

  t_bunny_color			color;
  t_bunny_color			clicked_color;
  t_bunny_color			hovered_color;
  t_bunny_color			focused_color;

  t_bunny_picture		*background;
  t_bunny_picture		*clicked_background;
  t_bunny_picture		*hovered_background;
  t_bunny_picture		*focused_background;
  t_bunny_picture_display_mode	display_mode;

  // Event responses
  t_bunny_configuration		*mouse_button_node;
  t_bunny_response		(*mouse_button)(t_bunny_event_state		state,
						t_bunny_position		pos,
						t_bunny_mouse_button		button,
						struct s_bunny_box_system	*sys,
						struct s_bunny_gui_box		*box);
  t_bunny_configuration		*mouse_move_node;
  t_bunny_response		(*mouse_move)(t_bunny_position			pos,
					      struct s_bunny_box_system		*sys,
					      struct s_bunny_gui_box		*box);
  t_bunny_configuration		*mouse_in_node;
  t_bunny_response		(*mouse_in)(struct s_bunny_box_system		*sys,
					    struct s_bunny_gui_box		*box);
  t_bunny_configuration		*mouse_out_node;
  t_bunny_response		(*mouse_out)(struct s_bunny_box_system		*sys,
					     struct s_bunny_gui_box		*box);
  t_bunny_configuration		*click_node;
  t_bunny_response		(*click)(struct s_bunny_box_system		*sys,
					 struct s_bunny_gui_box			*box);
  t_bunny_configuration		*focus_node;
  t_bunny_response		(*focus)(t_bunny_event_state			state,
					 struct s_bunny_box_system		*sys,
					 struct s_bunny_gui_box			*box);

  // Cyclic and misc
  t_bunny_configuration		*loop_node;
  t_bunny_response		(*loop)(struct s_bunny_box_system		*sys,
					struct s_bunny_gui_box			*box,
					double					delay);
  t_bunny_response		(*display)(struct s_bunny_box_system		*sys,
					   struct s_bunny_gui_box		*bos,
					   const t_bunny_accurate_position	*offset);
  void				(*destructor)(struct s_bunny_gui_box		*box);
}				t_bunny_gui_box;

typedef struct			s_bunny_gui_label
{
  t_bunny_gui_box		box;
  t_bunny_font			*text;
}				t_bunny_gui_label;

typedef t_bunny_gui_box		*(*t_bunny_new_box)(t_bunny_gui_box		*parent,
						    t_bunny_configuration	*cnf);

/*!
** ****************************************************************
** ************** HANGED BUNNY STUDIO GUI SYSTEM ******************
** ****************************************************************
**
** This context is the HBS GUI System. It brings graphic user interface
** object like windows, buttons and textbox.
**
** It is designed to be efficiently used with a subcontext in order
** to work as an overlay. Any other context should be able to be used
** as subcontext of this one as it is transitive (that means that event
** received by the current context that are not handled are transmitted
** to the subcontext - all context should act this way, but this one
** give you the guarantee that is is)
**
** Box events may be handled by Dabsic scripts.
** Box status are transmitted to a runtime configuration so it may
** be reached by Dabsic scripts.
** You may put your own data inside this runtime configuration
** so it could also be reached.
**
** What is the difference between head.subcontext and subcontext?
** The head.subcontext is useful to define specific handlers that
** will allow you to customize the GUI itself.
** The subcontext pointer allow the GUI to be used as an overlay
** of subcontext. Something that will be printed *over* it and
** that will transmist events.
*/
typedef struct			s_bunny_box_system
{
  t_bunny_context_runtime_info	head;
  t_bunny_context_runtime_info	*subhead;
  t_bunny_gui_box		screen;
  t_bunny_gui_box		*focus;
  t_bunny_gui_box		*hovered;
  t_bunny_gui_box		*down_clicked;

  const char			_private[512];
}				t_bunny_box_system;

extern const t_bunny_context	gl_bunny_box_context;
extern const t_bunny_new_box	gl_bunny_new_box[BBT_CUSTOM_BOX];
extern t_bunny_new_box		gl_bunny_custom_new_box;

t_bunny_configuration		*bunny_init_box_environ(int		width,
							int		height);

void				*bunny_new_gui_box(size_t		siz,
						   t_bunny_configuration*cnf);
bool				bunny_load_box(t_bunny_box_system	*bs,
					       const char		*file,
					       t_bunny_configuration	*env);
bool				bunny_read_box(t_bunny_box_system	*bs,
					       t_bunny_configuration	*cnf);
t_bunny_gui_box			*bunny_read_simple_box(t_bunny_gui_box	*nw,
						       t_bunny_gui_box	*parent,
						       t_bunny_configuration *cnf);

void				bunny_delete_box(t_bunny_gui_box	*box);

#endif	/*			__LAPIN_BOX_H__		*/
