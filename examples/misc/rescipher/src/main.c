/*
** Jason Brillante "Damdoshi"
** Hanged Bunny Studio 2014-2017
**
** Bibliotheque Lapin
*/

#include		<string.h>
#include		<lapin.h>

t_bunny_window		*win;
t_bunny_picture		*pic;

/* ashiciphs : a shitty ciphering system */
static void		ashiciph(char		*data,
				 size_t		len,
				 void		*dat,
				 bool		cipher)
{
  (void)data;
  (void)len;
  (void)dat;
  (void)cipher;
  if (cipher)
    {
      bunny_cipher_data(data, len, BS_CAESAR, dat);
      bunny_cipher_data(data, len, BS_XOR, dat);
      bunny_cipher_data(data, len, BS_SHAKER, dat);
      bunny_cipher_data(data, len, BS_SWITCH, dat);
    }
  else
    {
      bunny_uncipher_data(data, len, BS_SWITCH, dat);
      bunny_uncipher_data(data, len, BS_SHAKER, dat);
      bunny_uncipher_data(data, len, BS_XOR, dat);
      bunny_uncipher_data(data, len, BS_CAESAR, dat);
    }
}

t_bunny_response	keyexit(t_bunny_event_state state,
				t_bunny_keysym	sym,
				void		*data)
{
  (void)sym;
  (void)data;
  if (state == GO_DOWN)
    return (EXIT_ON_SUCCESS);
  return (GO_ON);
}

t_bunny_response	loop(void		*data)
{
  (void)data;
  bunny_display(win);
  return (GO_ON);
}

int			main(int		argc,
			     char		**argv)
{
  const char		*key_content = "abcdef";
  size_t		len = strlen(key_content);
  t_bunny_cipher_key	*key = bunny_alloca(sizeof(*key) + len + 1);

  strcpy(&key->key[0], key_content);
  key->length = len;

  gl_bunny_ressource_ciphering = ashiciph;
  gl_bunny_ressource_data = key;

  if (argc != 2)
    {
      printf("%s picture_file\n", argv[0]);
      return (EXIT_FAILURE);
    }

  if ((pic = bunny_load_picture(argv[1])) == NULL)
    return (EXIT_FAILURE);
  if ((win = bunny_start
       (pic->buffer.width, pic->buffer.height, false, "Picture cipher")) == NULL)
    {
      bunny_delete_clipable(pic);
      return (EXIT_FAILURE);
    }

  bunny_set_key_response(keyexit);
  bunny_set_loop_main_function(loop);

  bunny_blit(&win->buffer, pic, NULL);
  bunny_loop(win, 20, NULL);

  bunny_delete_clipable(pic);
  bunny_stop(win);

  return (EXIT_SUCCESS);
}

