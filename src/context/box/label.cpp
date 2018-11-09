// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2018
//
// Bibliothèque Lapin

#include		"lapin_private.h"

t_bunny_response	bunny_display_label_box(t_bunny_box_system		*sys,
						t_bunny_gui_box			*box,
						const t_bunny_accurate_position	*off);

t_bunny_gui_box		*bunny_read_label_box(t_bunny_gui_label		*nw,
					      t_bunny_gui_box		*parent,
					      t_bunny_configuration	*cnf)
{
  t_bunny_configuration	*nod, *nod2;
  const char		*str;

  (void)parent;

  if (bunny_configuration_getf_string(cnf, &str, "Font"))
    {
      if ((nw->text = bunny_load_text(str)) == NULL)
	return (NULL);
      if (bunny_configuration_bindf_string(cnf, (char**)&nw->text->string, "Text") == false)
	{
	  bunny_delete_clipable(&nw->text->clipable);
	  return (NULL);
	}
    }
  else if (bunny_configuration_getf_node(cnf, &nod, "Font"))
    {
      if ((nw->text = bunny_read_textbox(nod)) == NULL)
	return (NULL);
      if (bunny_configuration_getf_string(cnf, &str, "Text"))
	{
	  if (nw->text->string)
	    bunny_free((char*)nw->text->string);
	  if ((nw->text->string = bunny_strdup(str)) == NULL)
	    {
	      bunny_delete_clipable(&nw->text->clipable);
	      return (NULL);
	    }
	}
      else
	bunny_configuration_setf_string(cnf, nw->text->string, "Text");
      bunny_configuration_setf_string(cnf, nw->text->string, "Font.Text");

      bunny_configuration_getf_node(cnf, &nod, "Text");
      bunny_configuration_getf_node(cnf, &nod2, "Font.Text");
      bunny_configuration_link(nod2, nod);
      bunny_configuration_bindf_string(cnf, (char**)&nw->text->string, "Font.Text");
    }
  else if (bunny_configuration_getf_string(cnf, NULL, "RessourceFile"))
    {
      if ((nw->text = bunny_read_textbox(cnf)) == NULL)
	return (NULL);
      if (bunny_configuration_bindf_string(cnf, (char**)&nw->text->string, "Text") == false)
	{
	  bunny_delete_clipable(&nw->text->clipable);
	  return (NULL);
	}
    }
  else
    return (NULL);

  nw->box.display = bunny_display_label_box;
  return (&nw->box);
}

t_bunny_gui_box		*bunny_new_label_box(t_bunny_gui_box			*parent,
					     t_bunny_configuration		*cnf)
{
  t_bunny_gui_label	*nw;

  if ((nw = (t_bunny_gui_label*)bunny_new_gui_box(sizeof(*nw), cnf)) == NULL)
    return (NULL);
  nw->box.type = BBT_LABEL_BOX;
  if (bunny_read_simple_box((t_bunny_gui_box*)nw, parent, cnf) == NULL)
    goto Error;
  if (bunny_read_label_box(nw, parent, cnf) == NULL)
    goto Error;
  return ((t_bunny_gui_box*)nw);

 Error:
  bunny_delete_box(&nw->box);
  return (NULL);
}

