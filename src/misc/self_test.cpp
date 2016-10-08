// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2016
//
// Lapin library

#include		<string.h>
#include		<math.h>
#include		<time.h>
#include		<signal.h>
#include		"lapin_private.h"

typedef int		(*t_bunny_test)(t_bunny_picture			*pic,
					t_bunny_pixelarray		*pix);

static bool		compare_color(t_color				*a,
				      t_color				*b)
{
  int			m;
  int			i;

  for (i = 0, m = 0; i < 4; ++i)
    {
      int		c[2];

      c[0] = a->argb[i] + 1000;
      c[1] = b->argb[i] + 1000;
      m += (abs(c[0] - c[1]) < 40) ? 1 : 0;
    }
  return (m == 4);
}

static bool		compare_neighbor(t_color			*ref,
					 t_color			*std,
					 int				w,
					 int				h,
					 int				i)
{
  t_bunny_position	pos;
  t_bunny_position	off;

  pos.x = i % w;
  pos.y = i / w;
  for (off.y = -1; off.y < 2; ++off.y)
    for (off.x = -1; off.x < 2; ++off.x)
      if (pos.x + off.x >= 0 && pos.x + off.x < w &&
	  pos.y + off.y >= 0 && pos.y + off.y < h)
	if (compare_color
	    (&ref[pos.x + pos.y * w],
	     &std[pos.x + off.x + (pos.y + off.y) * w])
	    != false)
	  return (true);
  return (false);
}

static void		technocore_compare(t_bunny_pixelarray		*_a,
					   t_bunny_pixelarray		*_b,
					   int				*unmatch_cnt)
{
  t_color		*a = (t_color*)_a->pixels;
  t_color		*b = (t_color*)_b->pixels;
  int			len;
  int			i;

  *unmatch_cnt = 0;
  for (i = 0, len = _a->clipable.buffer.width * _a->clipable.buffer.height; i < len; ++i)
    if (a[i].full != 0
	&& compare_neighbor
	(a, b, _a->clipable.buffer.width,
	 _a->clipable.buffer.height, i) == false)
      *unmatch_cnt += 1;
}

static int		save_test(t_bunny_pixelarray		*ref,
				  t_bunny_pixelarray		*std,
				  const char			*test)
{
  t_bunny_pixelarray	*save;
  t_bunny_position	pos;

  pos.x = ref->clipable.buffer.width;
  pos.y = 0;
  if ((save = bunny_new_pixelarray
       (ref->clipable.buffer.width * 2,
	ref->clipable.buffer.height)) == NULL)
    return (-1);
  memset(save->pixels, 0xFF, ref->clipable.buffer.width * ref->clipable.buffer.height * sizeof(unsigned int));
  bunny_blit(&save->clipable.buffer, &ref->clipable, NULL);
  bunny_blit(&save->clipable.buffer, &std->clipable, &pos);
  if (bunny_save_pixelarray(save, test) == false)
    {
      bunny_delete_clipable(&save->clipable);
      return (-1);
    }
  bunny_delete_clipable(&save->clipable);
  return (0);
}

static int		clear_test(t_bunny_picture		*pic,
				   t_bunny_pixelarray		*pix)
{
  t_bunny_pixelarray	*out;
  unsigned int		color;
  int			i;

  if (gl_bunny_my_clear == NULL)
    {
      bunny_printl("\nNo function given to gl_bunny_my_clear.");
      return (0);
    }
  if ((out = bunny_new_pixelarray(pic->buffer.width, pic->buffer.height)) == NULL)
    return (-1);
  bunny_clear(&pic->buffer, PINK2);
  for (i = 0; i < 3000; ++i)
    {
      color = rand() | BLACK;

      pic->clip_width = pix->clipable.clip_width = rand() % (pic->buffer.width - 1) + 1;
      pic->clip_height = pix->clipable.clip_height = rand() % (pic->buffer.height - 1) + 1;
      pic->clip_x_position = pix->clipable.clip_x_position = rand() % (pic->buffer.width - pic->clip_width);
      pic->clip_y_position = pix->clipable.clip_y_position = rand() % (pic->buffer.height - pic->clip_height);

      bunny_clear(&pic->buffer, color);
      bunny_clear(&pix->clipable.buffer, color);
    }
  pic->clip_x_position = pix->clipable.clip_x_position = 0;
  pic->clip_y_position = pix->clipable.clip_y_position = 0;
  pic->clip_width = pix->clipable.clip_width = pix->clipable.buffer.width;
  pic->clip_height = pix->clipable.clip_height = pix->clipable.buffer.height;

  bunny_blit(&out->clipable.buffer, pic, NULL);
  technocore_compare(out, pix, &i);
  if (save_test(out, pix, "bunny_clear.bmp") == -1)
    i = -1;
  bunny_delete_clipable(&out->clipable);
  return (i > 0 ? 0 : (i < 0 ? -1 : 1));
}

static int		pixel_test(t_bunny_picture		*pic,
				   t_bunny_pixelarray		*pix)
{
  t_bunny_pixelarray	*out;
  t_bunny_position	pos;
  unsigned int		color;
  int			i;

  if (gl_bunny_my_set_pixel == NULL)
    {
      bunny_printl("\nNo function given to gl_bunny_my_set_pixel.");
      return (0);
    }
  if ((out = bunny_new_pixelarray(pic->buffer.width, pic->buffer.height)) == NULL)
    return (-1);
  bunny_clear(&pic->buffer, BLACK);
  bunny_clear(&pix->clipable.buffer, BLACK);
  for (i = 0; i < 20000; ++i)
    {
      color = rand();
      pos.x = rand() % pic->buffer.width;
      pos.y = rand() % pic->buffer.height;
      bunny_set_pixel(&pic->buffer, pos, color);
      bunny_set_pixel(&pix->clipable.buffer, pos, color);
    }
  bunny_blit(&out->clipable.buffer, pic, NULL);
  technocore_compare(out, pix, &i);
  if (save_test(out, pix, "bunny_set_pixel.bmp") == -1)
    i = -1;
  bunny_delete_clipable(&out->clipable);
  return (i > 0 ? 0 : (i < 0 ? -1 : 1));
}

static int		fill_test(t_bunny_picture		*pic,
				  t_bunny_pixelarray		*pix)
{
  t_bunny_pixelarray	*out;
  unsigned int		color;
  int			i;

  if (gl_bunny_my_set_pixel == NULL)
    {
      bunny_printl("\nNo function given to gl_bunny_my_fill.");
      return (0);
    }
  if ((out = bunny_new_pixelarray(pic->buffer.width, pic->buffer.height)) == NULL)
    return (-1);
  bunny_clear(&pic->buffer, BLACK);
  bunny_clear(&pix->clipable.buffer, BLACK);
  for (i = 0; i < 3000; ++i)
    {
      color = rand();

      pic->clip_width = pix->clipable.clip_width = rand() % (pic->buffer.width - 1) + 1;
      pic->clip_height = pix->clipable.clip_height = rand() % (pic->buffer.height - 1) + 1;
      pic->clip_x_position = pix->clipable.clip_x_position = rand() % (pic->buffer.width - pic->clip_width);
      pic->clip_y_position = pix->clipable.clip_y_position = rand() % (pic->buffer.height - pic->clip_height);

      bunny_fill(&pic->buffer, color);
      bunny_fill(&pix->clipable.buffer, color);
    }
  pic->clip_width = pix->clipable.clip_width = pix->clipable.buffer.width;
  pic->clip_height = pix->clipable.clip_height = pix->clipable.buffer.height;
  pic->clip_x_position = pix->clipable.clip_x_position = 0;
  pic->clip_y_position = pix->clipable.clip_y_position = 0;


  bunny_blit(&out->clipable.buffer, pic, NULL);
  technocore_compare(out, pix, &i);
  if (save_test(out, pix, "bunny_fill.bmp") == -1)
    i = -1;
  bunny_delete_clipable(&out->clipable);
  return (i > 0 ? 0 : (i < 0 ? -1 : 1));
}

static int		line_test(t_bunny_picture		*pic,
				  t_bunny_pixelarray		*pix)
{
  t_bunny_pixelarray	*out;
  t_bunny_position	pos[2];
  unsigned int		color[2];
  int			res;
  double		j;
  double		i;

  if (gl_bunny_my_set_line == NULL)
    {
      bunny_printl("\nNo function given to gl_bunny_my_set_line.");
      return (0);
    }
  if ((out = bunny_new_pixelarray(pic->buffer.width, pic->buffer.height)) == NULL)
    return (-1);
  bunny_clear(&pic->buffer, BLACK);
  bunny_clear(&pix->clipable.buffer, BLACK);

  pos[0].x = pic->buffer.width / 2;
  pos[0].y = pic->buffer.height / 2;
  for (j = 0; j < (2 * M_PI) / 32.0; j += 0.01)
    for (i = 0; i < 2 * M_PI; i += (2.0 * M_PI) / 32.0)
      {
	pos[1].x = cos(i + j) * (pos[0].x > pos[0].y ? pos[0].y * 0.9 : pos[0].x * 0.9) + pos[0].x;
	pos[1].y = sin(i + j) * (pos[0].x > pos[0].y ? pos[0].y * 0.9 : pos[0].x * 0.9) + pos[0].y;
	color[0] = rand();
	color[1] = rand();
	bunny_set_line(&pic->buffer, &pos[0], &color[0]);
	bunny_set_line(&pix->clipable.buffer, &pos[0], &color[0]);
      }

  bunny_blit(&out->clipable.buffer, pic, NULL);
  technocore_compare(out, pix, &res);
  if (save_test(out, pix, "bunny_set_line.bmp") == -1)
    res = -1;
  bunny_delete_clipable(&out->clipable);
  return (res > 300 ? 0 : (res < 0 ? -1 : 1));
}

static int		polygon_test(t_bunny_picture		*pic,
				     t_bunny_pixelarray		*pix)
{
  t_bunny_pixelarray	*out;
  t_bunny_position	pos[3];
  unsigned int		color[3];
  int			res;
  int			i;
  int			j;

  if (gl_bunny_my_set_polygon == NULL)
    {
      bunny_printl("\nNo function given to gl_bunny_my_set_polygon.");
      return (0);
    }
  if ((out = bunny_new_pixelarray(pic->buffer.width, pic->buffer.height)) == NULL)
    return (-1);
  bunny_clear(&pic->buffer, BLACK);
  bunny_clear(&pix->clipable.buffer, BLACK);

  for (i = 0; i < 200; ++i)
    {
      for (j = 0; j < 3; ++j)
	{
	  pos[j].x = rand() % pic->buffer.width;
	  pos[j].y = rand() % pic->buffer.height;
	  color[j] = rand();

	  bunny_set_polygon(&pic->buffer, &pos[0], &color[0]);
	  bunny_set_polygon(&pix->clipable.buffer, &pos[0], &color[0]);
	}
    }

  bunny_blit(&out->clipable.buffer, pic, NULL);
  technocore_compare(out, pix, &res);
  if (save_test(out, pix, "bunny_set_polygone.bmp") == -1)
    res = -1;
  bunny_delete_clipable(&out->clipable);
  return (res > 50 ? 0 : (res < 0 ? -1 : 1));
}

static bool		do_a_test(const char			*str,
				  t_bunny_test			test,
				  t_bunny_picture		*pic,
				  t_bunny_pixelarray		*pix)
{
  int			i;

  bunny_printl("]> The TechnoCore is testing: ");
  write(1, str, strlen(str));
  if ((i = test(pic, pix)) == -1)
    {
      bunny_printlerr("Out of memory!");
      return (false);
    }
  else if (i == 1)
    bunny_printl(" -- Success!");
  else
    bunny_printl(" -- Failure!");
  return (true);
}

void			bunny_self_test(void)
{
  t_bunny_picture	*pic;
  t_bunny_pixelarray	*pix;

  srand(time(NULL));
  pic = bunny_new_picture(400, 400);
  pix = bunny_new_pixelarray(pic->buffer.width, pic->buffer.height);
  bunny_printl("]> Welcome to the Technocore Self Test module.");
  if (gl_bunny_my_blit == NULL)
    {
      bunny_printl("]> A minimal gl_bunny_my_blit function is required.");
      return ;
    }

  if (do_a_test("bunny_clear", clear_test, pic, pix) == false)
    kill(getpid(), SIGINT);
  if (do_a_test("bunny_set_pixel", pixel_test, pic, pix) == false)
    kill(getpid(), SIGINT);
  if (do_a_test("bunny_fill", fill_test, pic, pix) == false)
    kill(getpid(), SIGINT);
  if (do_a_test("bunny_set_line", line_test, pic, pix) == false)
    kill(getpid(), SIGINT);
  if (do_a_test("bunny_set_polygon", polygon_test, pic, pix) == false)
    kill(getpid(), SIGINT);

  return ;
  if (do_a_test("bunny_set_geometry", pixel_test, pic, pix) == false)
    kill(getpid(), SIGINT);
  if (do_a_test("bunny_load_pixelarray", pixel_test, pic, pix) == false)
    kill(getpid(), SIGINT);
}

