/*
** Jason Brillante "Damdoshi"
** Hanged Bunny Studio 2014-2019
**
** Joystick panel
*/

#include			"joypanel.h"

/*
** Title: Centered, 100px height
** Followed by joysticks organized this way:
**   800p
** <------>
** +------+------+ |
** |  1   |   7  |140p
** +------+------+ |
** |  2   |   8  |
** +------+------+
** |  3   |   9  |
** +------+------+
** |  4   |  10  |
** +------+------+
** |  5   |  11  |
** +------+------+
** |  6   |  12  |
** +------+------+
*/

static void			draw_joystick(t_program		*prog,
					      int		id,
					      t_bunny_position	pos)
{
  char				buffer[4];
  static const char		*axis_name[LAST_BUNNY_AXIS / 2] =
    {"X/Y", "Z/R", "U/V", "POV"};
  static const t_bunny_position	disk_size = {40, 40};
  static const t_bunny_position	button_size = {10, 10};
  static const t_bunny_position	dot_size = {5, 5};
  t_bunny_position		p, q;
  size_t			i, j;

  if (prog->text)
    {
      prog->text->string = prog->joystick[id]->name;
      bunny_clear(&prog->text->clipable.buffer, 0);
      bunny_draw(&prog->text->clipable);
      bunny_blit(&prog->window->buffer, &prog->text->clipable, &pos);
    }

  p.y = pos.y + 50 + prog->text->clipable.buffer.height;

  for (j = 0, i = 0; j < LAST_BUNNY_AXIS; j += 2)
    // for (i = j = 0; prog->joystick[id]->axis >> i; i += 2, ++j)
    {
      if (!(prog->joystick[id]->axis & (1 << (j + 0)))
	  && !(prog->joystick[id]->axis & (1 << (j + 1))))
	continue ;

      // Back circle
      p.x = pos.x + 50 + (disk_size.x + 50) * i;
      bunny_set_disk(&prog->window->buffer, p, disk_size, GRAY(32), WHITE, 3);

      // Axis label
      if (prog->label)
	{
	  prog->label->string = axis_name[j >> 1];
	  bunny_clear(&prog->label->clipable.buffer, 0);
	  bunny_draw(&prog->label->clipable);
	  bunny_blit(&prog->window->buffer, &prog->label->clipable, &p);
	}

      // Axis dot
      q.x = p.x + (bunny_get_joy_axis()[id][j + 0] / 100.0) * 30;
      q.y = p.y + (bunny_get_joy_axis()[id][j + 1] / 100.0) * 30;
      bunny_set_disk(&prog->window->buffer, q, dot_size, RED, WHITE, 2);

      i += 1;
    }

  p.x = pos.x + 50 + (disk_size.x + 50) * LAST_BUNNY_AXIS / 2;
  for (i = 0; i < prog->joystick[id]->nb_button; ++i)
    {
      p.y = pos.y + 20 + prog->text->clipable.buffer.height;
      if (bunny_get_joy_button()[id][i])
	bunny_set_disk(&prog->window->buffer, p, button_size, RED, WHITE, 2);
      else
	bunny_set_disk(&prog->window->buffer, p, button_size, BLACK, WHITE, 2);

      if (prog->label)
	{
	  snprintf(&buffer[0], sizeof(buffer), "B%0zu", i);
	  prog->label->string = &buffer[0];
	  bunny_clear(&prog->label->clipable.buffer, 0);
	  bunny_draw(&prog->label->clipable);
	  bunny_blit(&prog->window->buffer, &prog->label->clipable, &p);
	}

      if ((i += 1) >= prog->joystick[id]->nb_button)
	break ;

      p.y = pos.y + 80 + prog->text->clipable.buffer.height;
      if (bunny_get_joy_button()[id][i])
	bunny_set_disk(&prog->window->buffer, p, button_size, RED, WHITE, 2);
      else
	bunny_set_disk(&prog->window->buffer, p, button_size, BLACK, WHITE, 2);

      if (prog->label)
	{
	  snprintf(&buffer[0], sizeof(buffer), "B%0zu", i);
	  prog->label->string = &buffer[0];
	  bunny_clear(&prog->label->clipable.buffer, 0);
	  bunny_draw(&prog->label->clipable);
	  bunny_blit(&prog->window->buffer, &prog->label->clipable, &p);
	}

      p.x += 40;
    }
}

t_bunny_response		joypanel_display(t_program	*prog)
{
  t_bunny_position		pos;
  int				i, j;

  // Clear
  bunny_clear(&prog->window->buffer, BLACK);

  // Title
  if (prog->title)
    {
      pos.x = (prog->window->buffer.width - prog->title->clipable.buffer.width) / 2;
      pos.y = 0;
      bunny_blit(&prog->window->buffer, &prog->title->clipable, &pos);
    }

  // Joyinfo
  pos.x = 0 + 10;
  for (j = 0, i = 0; i < prog->nbr_joystick && i < 6; ++i)
    {
      pos.y = single_panel_height * j + 100;
      if (prog->joystick[i])
	{
	  draw_joystick(prog, i, pos);
	  j += 1;
	}
    }
  pos.x = prog->window->buffer.width / 2 + 10;
  for (j = 0, i = 6; i < prog->nbr_joystick; ++i)
    {
      pos.y = single_panel_height * j + 100;
      if (prog->joystick[i])
	{
	  draw_joystick(prog, i, pos);
	  j += 1;
	}
    }

  bunny_display(prog->window);
  return (GO_ON);
}

