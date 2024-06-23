/*
** *****************************************************************************
** damdoshi <damdoshi@blacklatex>
** Ecole 89 - 27/11/2020 11:36:03
**
** - BMP TO DABSIC -
**
** *****************************************************************************
*/

#include			<lapin.h>

t_bunny_configuration		*convert_bmp_to_dabsic(t_bunny_pixelarray	*pix)
{
  t_bunny_configuration		*cnf;
  int				i;
  int				j;

  if ((cnf = bunny_new_configuration()) == NULL)
    {
      bunny_printlerr("Failed to create a new configuration.");
      return (NULL);
    }
  if (!bunny_configuration_setf(cnf, "Surface", "Objects[0].Type"))
    {
      bunny_printlerr("Failed to write field Height");
      goto Delete;
    }
  if (!bunny_configuration_setf(cnf, (int)pix->clipable.buffer.width, "Objects[0].Width"))
    {
      bunny_printlerr("Failed to write field Width");
      goto Delete;
    }
  if (!bunny_configuration_setf(cnf, (int)pix->clipable.buffer.height, "Objects[0].Height"))
    {
      bunny_printlerr("Failed to write field Height");
      goto Delete;
    }
  for (i = 0; i < pix->clipable.buffer.width * pix->clipable.buffer.height; ++i)
    {
      t_bunny_color		col;
      unsigned int		med;

      col.full = ((unsigned int*)pix->pixels)[i];
      for (med = 0, j = RED_CMP; j < ALPHA_CMP; ++j)
	med += col.argb[j];
      med /= 4;
      if (!bunny_configuration_setf(cnf, (int)med, "Objects[0].Data[%d]", i))
	{
	  fprintf(stderr, "Failed to write field Data[%d].", i);
	  goto Delete;
	}
      if (!bunny_configuration_setf(cnf, (int)col.full, "Objects[0].Color[%d]", i))
	{
	  fprintf(stderr, "Failed to write field Data[%d].", i);
	  goto Delete;
	}
    }

  return (cnf);

 Delete:
  bunny_delete_configuration(cnf);
  return (NULL);
}
