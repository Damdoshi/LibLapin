// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2024
//
// Lapin library

#include		<SFML/Graphics.hpp>
#include		<SFML/OpenGL.hpp>
#include		"lapin_private.h"

void			bunny_set_zpolygon(t_bunny_buffer		*_buffer,
					   const t_bunny_accurate_zposition *pos,
					   const unsigned int		*_col)
{
  struct bunny_window	*buffer = (struct bunny_window*)_buffer;
  struct bunny_picture	*picture = (struct bunny_picture*)_buffer;
  sf::RenderTarget	*rdtar = NULL;
  t_bunny_color		*col = (t_bunny_color*)_col;

  if (buffer->type == WINDOW)
    rdtar = buffer->window;
  else
    rdtar = picture->texture;
  if (rdtar == NULL)
    {
      if (buffer->type != SYSTEM_RAM)
	return ;
      // euh, mais du coup, ca peut pas etre un pixelarray, vu qu'il manque le zbuffer...
      gl_bunny_my_set_zpolygon((t_bunny_pixelarray*)_buffer, pos, _col);
      return ;
    }
  if (!buffer->glactive)
    {
      rdtar->setActive(true);
      buffer->glactive = true;
      glBegin(GL_TRIANGLES);
      glViewport(0, 0, buffer->width, buffer->height);
    }
  for (int i = 0; i < 3; ++i)
    {
      glColor3ub(col[i].argb[RED_CMP],
		 col[i].argb[GREEN_CMP],
		 col[i].argb[BLUE_CMP]);
      glVertex3f(pos[i].x, pos[i].y, pos[i].z);
    }
}
