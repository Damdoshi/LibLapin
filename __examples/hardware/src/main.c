/*
** Jason Brillante "Damdoshi"
** Hanged Bunny Studio 2014-2016
**
** 
*/

#include		<stdio.h>
#include		<math.h>
#include		<lapin.h>

t_bunny_hardware	*hard;

void			bye(int			i)
{
  (void)i;
  bunny_delete_hardware(hard);
  puts("\nGood bye");
  exit(EXIT_SUCCESS);
}

int			main(void)
{
  size_t		k;
  double		j;
  size_t		i;

  j = 0;
  if ((hard = bunny_new_hardware(0)) == NULL)
    {
      puts("Cannot find the board, or maybe you ain't sudo?");
      return (EXIT_FAILURE);
    }
 start:
  bunny_hardware_read(hard);
  write(1, "\r", 1);
  for (i = 0; i < sizeof(hard->digital_inputs) / sizeof(hard->digital_inputs[0]); ++i)
    fprintf(stdout, "%d ", hard->digital_inputs[i]);
  fprintf(stdout, "%.3lf ", hard->analog_inputs[0]);
  fprintf(stdout, "%.3lf ", hard->analog_inputs[1]);
  fflush(stdout);
  
  hard->analog_outputs[0] = fabs(cos(j += 0.01));
  hard->analog_outputs[1] = fabs(sin(j));
  for (i = 0; i < sizeof(hard->digital_outputs) / sizeof(hard->digital_outputs[0]); ++i)
    hard->digital_outputs[i] = (k / 10) >= i;
  if ((k += 1) >= 80)
    k = 0;
  bunny_hardware_write(hard);

  goto start;
  return (-42);
}

