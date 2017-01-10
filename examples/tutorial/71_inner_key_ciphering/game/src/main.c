/*
** Jason Brillante "Damdoshi"
** Hanged Bunny Studio 2014-2016
**
** LibLapin - Basic Ciphering
**
** All bunny functions are from lapin/security.h
**
*/

#include		<stdlib.h> /* EXIT_FAILURE, EXIT_SUCCESS */
#include		<string.h> /* strcmp, memcpy, strerror */
#include		<errno.h> /* ...errno... */
#include		<stdio.h> /* fprintf */
#include		<lapin.h>

static t_bunny_response	key(t_bunny_event_state	state,
			    t_bunny_keysym	sym,
			    void		*data)
{
  (void)state;
  (void)data;
  return (sym == BKS_ESCAPE ? EXIT_ON_SUCCESS : GO_ON);
}

static t_bunny_response	loop(void		*v)
{
  bunny_display(v);
  return (GO_ON);
}

int			main(void)
{
  t_bunny_window	*win;
  t_bunny_picture	*pic;
  const t_bunny_cipher_key *ckey;
  void			*picbuf;
  size_t		len;
  
  if (bunny_load_file("sexy.png", &picbuf, &len) == false)
    return (EXIT_FAILURE);
  ckey = bunny_default_key();
  bunny_uncipher_data(picbuf, len, BS_SHAKER, ckey);
  if ((pic = bunny_read_picture(picbuf, len)) == NULL)
    {
      bunny_free(picbuf);
      return (EXIT_FAILURE);
    }
  bunny_free(picbuf);
  if ((win = bunny_start(pic->buffer.width, pic->buffer.height, false, "Little program")) == NULL)
    {
      bunny_delete_clipable(picbuf);
      return (EXIT_FAILURE);
    }

  bunny_clear(&win->buffer, BLACK);
  bunny_blit(&win->buffer, pic, NULL);
  bunny_set_key_response(key);
  bunny_set_loop_main_function(loop);
  bunny_loop(win, 25, win);
  bunny_stop(win);
  return (EXIT_SUCCESS);
}

