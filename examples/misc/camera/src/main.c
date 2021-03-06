/*
** Jason Brillante "Damdoshi"
** Hanged Bunny Studio 2014-2016
**
** Webcam && Headtracking module
*/

#include		<assert.h>
#include		<stdio.h>
#include		<lapin.h>

t_bunny_window		*window;
t_bunny_pixelarray	*pix;
t_bunny_picture		*square;
t_bunny_camera		*camera;
t_bunny_capture		*capture;
t_bunny_position	capture_size;
t_bunny_area		face[2];
int			curface;

t_bunny_response	key(t_bunny_event_state		state,
			    t_bunny_keysym		sym,
			    void			*unused)
{
  (void)state;
  (void)unused;
  if (sym == BKS_ESCAPE)
    return (EXIT_ON_SUCCESS);
  return (GO_ON);
}

t_bunny_response	loop(void			*unused)
{
  t_bunny_position	pos;
  bool			done;

  (void)unused;
  bunny_clear(&window->buffer, PINK2);

  bunny_capture(camera, capture);
  assert(bunny_capture_to_pixelarray(capture, pix));
  bunny_blit(&window->buffer, &pix->clipable, NULL);

  done = false;
  if (bunny_camera_headtrack(capture, &face[curface == -1 ? 0 : curface]))
    {
      if (curface == -1)
	{
	  curface = 0;
	  memcpy(&face[1], &face[0], sizeof(face[1]));
	}
      else
	bunny_stabilize_headtrack(&face[!curface], &face[curface], 0.0);
      done = true;
    }
  square->clip_width = face[curface].w;
  square->clip_height = face[curface].h;
  pos.x = face[curface].x;
  pos.y = face[curface].y;
  bunny_blit(&window->buffer, square, &pos);

  if (done)
    curface = !curface;

  bunny_display(window);
  return (GO_ON);
}

int			main(void)
{
  assert(window = bunny_start(800, 600, false, "HeadTrack!"));
  assert(pix = bunny_new_pixelarray(window->buffer.width, window->buffer.height));
  assert(square = bunny_new_picture(window->buffer.width, window->buffer.height));
  assert(camera = bunny_new_camera(0));
  assert(capture = bunny_new_capture(camera));
  bunny_capture_get_size(capture, &capture_size);

  bunny_clear(&square->buffer, ALPHA(128, BLACK));
  curface = -1;

  bunny_set_key_response(key);
  bunny_set_loop_main_function(loop);

  bunny_loop(window, 25, NULL);

  bunny_delete_clipable(&pix->clipable);
  bunny_stop(window);

  return (EXIT_SUCCESS);
}

