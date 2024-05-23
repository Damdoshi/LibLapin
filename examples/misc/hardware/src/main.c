/*
** Jason Brillante "Damdoshi"
** Hanged Bunny Studio 2014-2016
**
** 
*/

#include		<stdio.h>
#include		<math.h>
#include		<lapin.h>

t_bunny_vm110n		*hard[4];
int			hardnbr;

void			bye(int			i)
{
  for (i = 0; i < hardnbr; ++i)
    bunny_delete_vm110n(hard[i]);
  puts("\nGood bye");
  exit(EXIT_SUCCESS);
}

int			main(int		argc,
			     char		**argv)
{
  int			k;
  int			j;
  int			i;
  double		val;

  for (i = 1; i < argc; ++i)
    {
      if ((hard[i - 1] = bunny_new_vm110n(atoi(argv[i]))) == NULL)
	{
	  puts("Cannot find the board, or maybe you ain't sudo?");
	  return (EXIT_FAILURE);
	}
      hardnbr = i;
    }
  if (hardnbr == 0)
    return (0);
  
  val = 0;
  while (1)
    {
      if (argc != 2)
	write(1, "\e[2H\e[J", 7);
      else
	write(1, "\r", 1);
      for (i = 0; i < argc - 1; ++i)
	{
	  bunny_vm110n_read(hard[i]);
	  fprintf(stdout, "Board %d - ", i);
	  for (j = 0; j < NBRCELL(hard[i]->digital_inputs); ++j)
	    fprintf(stdout, "%d ", hard[i]->digital_inputs[j]);
	  fprintf(stdout, "%.3lf ", hard[i]->analog_inputs[0]);
	  fprintf(stdout, "%.3lf ", hard[i]->analog_inputs[1]);
	  if (argc == 2)
	    fflush(stdout);
	  else
	    fprintf(stdout, "\n");
      
	  hard[i]->analog_outputs[0] = fabs(cos(val));
	  hard[i]->analog_outputs[1] = fabs(sin(val));
	  for (j = 0; j < NBRCELL(hard[i]->digital_outputs); ++j)
	    hard[i]->digital_outputs[j] = (k / 10) >= j;
	  if ((k += 1) >= 80)
	    k = 0;
	  bunny_vm110n_write(hard[i]);
	}
      val += 0.01;
    }

  return (0);
}

