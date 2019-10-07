/*
** Jason Brillante "Damdoshi"
** Hanged Bunny Studio 2014-2021
**
** LibLapin Test
*/

#include		<stdio.h>
#include		<lapin.h>

typedef struct		s_program
{
  t_bunny_window	*win;
  t_bunny_server	*srv;
  unsigned int		color;
  int			player;
}			t_program;

t_bunny_response	loop(void		*data)
{
  t_program		*prg = data;
  
  bunny_clear(&prg->win->buffer, prg->color);
  bunny_display(prg->win);
  return (GO_ON);
}

t_bunny_response	key(t_bunny_event_state	state,
			    t_bunny_keysym	sym,
			    void		*data)
{
  (void)data;
  (void)state;
  if (sym == BKS_ESCAPE)
    return (EXIT_ON_SUCCESS);
  return (GO_ON);
}

t_bunny_response	myconnect(int		fd,
				  t_bunny_event_state state,
				  void		*data)
{
  t_program		*prg = data;

  if (state == DISCONNECTED)
    {
      if (prg->player == fd)
	prg->player = -1;
      return (GO_ON);
    }
  if (prg->player == -1)
    prg->player = fd;
  else
    bunny_server_doom_client(prg->srv, fd);
  return (GO_ON);
}

t_bunny_response	mymessage(int		fd,
				  const void	*buffer,
				  size_t		size,
				  void		*data)
{
  t_program		*prg = data;
  char			buf[128];

  bunny_trace();
  if (prg->player != fd)
    return (GO_ON);
  if (size > sizeof(buf) - 1)
    return (GO_ON);
  memcpy(&buf[0], buffer, size);
  buf[size] = '\0';
  if (strcmp(buf, "red\n") == 0)
    prg->color = RED;
  else if (strcmp(buf, "pink\n") == 0)
    prg->color = PINK2;
  return (GO_ON);
}

int			main(int		argc,
			     char		**argv)
{
  t_program		prg;

  prg.player = -1;
  prg.win = bunny_start(800, 600, false, "The Color server");
  prg.srv = bunny_new_server(2000);

  bunny_set_loop_main_function(loop);
  bunny_set_key_response(key);
  bunny_set_server_to_scheduler(prg.srv);
  bunny_set_connect_response(myconnect);
  bunny_set_message_response(mymessage);

  bunny_loop(prg.win, 50, &prg);

  bunny_delete_server(prg.srv);
  bunny_stop(prg.win);
  return (EXIT_SUCCESS);
}

