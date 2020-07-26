// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2020
//
// Bibliothèque Lapin

#include		"lapin_private.h"

t_bunny_gui_box		*bunny_read_browse_box(t_buny_gui_browse	*nw,
					       t_bunny_gui_box		*parent,
					       t_bunny_configuration	*cnf)
{
  const char		*str;

  (void)parent;
  if (bunny_configuration_getf_string(cnf, &str, "Font"))
    {
      t_bunny_position	siz = {20, 20};
      unsigned int	w;

      if (nw->box.size < 200)
	w = nw->box.size;
      else
	w = 200;
      if ((nw->file_font = bunny_load_font(w, 30, str, &siz)) == NULL)
	return (NULL);
    }

  t_bunny_configuration	*tmpcnf;
  char			buffer[1024];
  const char		*pattern = R"!!(
    Type="Label"
    Position=%d, %d
    Size=%d, %d
    Text="%s"
    Font="%s"

  )!!";

  // BOUTON OK
  snprintf(&buffer[0], sizeof(buffer), pattern, a, b, c, d, e, f);
  if ((tmpcnf = bunny_read_configuration(BC_DABSIC, tmpcnf, NULL)) == NULL)
    return (NULL);
  nw->buttons[0] = bunny_new_label_box(&nw->box, tmpcnf);
  bunny_delete_configuration(tmpcnf);
  if (nw->buttons[0] == NULL)
    return (NULL);

}

t_bunny_gui_box		*bunny_new_browse_box(t_bunny_gui_box		*parent,
					      t_bunny_configuration	*cnf)
{
  t_bunny_gui_browse	*nw;

  if ((nw = (t_bunny_gui_browse*)bunny_new_gui_box(sizeof(*nw), cnf)) == NULL)
    return (NULL);
  nw->box.type = BBT_BROWSE_BOX;
  if (bunny_read_simple_box((t_bunny_gui_box*)nw, parent, cnf) == NULL)
    goto Error;
  if (bunny_read_browse_box(nw, parent, cnf) == NULL)
    goto Error;
  return ((t_bunny_gui_browse*)nw);

 Error:
  if (nw->file_font)
    bunny_delete_clipable(&nw->file_font->clipable);
  bunny_delete_box(&nw->box);
  return (NULL);
}
