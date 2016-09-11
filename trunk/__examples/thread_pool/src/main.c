/*
** Jason Brillante "Damdoshi"
** Hanged Bunny Studio 2014-2016
**
** 
*/

#include		<locale.h>
#include		<time.h>
#include		<stdio.h>
#include		<lapin.h>

void			print_data(void		*data,
				   const void	*add)
{
  int			*n = (int*)data;
  const char		*str = (const char*)add;

  fprintf(stderr, "%s:%d\n", str, *n);
  usleep(1e3);
}

int			main(int		argc,
			     char		**argv)
{
  struct timespec	start;
  struct timespec	end;
  t_bunny_threadpool	*pool;
  int			**collection;
  size_t		i, len;
  
  if (argc != 2)
    {
      puts("Please preecise of many threads you wish to use.");
      return (EXIT_FAILURE);
    }

  len = 4096;
  
  if ((pool = bunny_new_threadpool(atoi(argv[1]))) == NULL)
    return (EXIT_FAILURE);
  if ((collection = bunny_malloc(len * sizeof(*collection))) == NULL)
    {
      bunny_delete_threadpool(pool);
      return (EXIT_FAILURE);
    }
  for (i = 0; i < len; ++i)
    if ((collection[i] = bunny_malloc(sizeof(**collection))) == NULL)
      {
	bunny_delete_threadpool(pool);
	return (EXIT_FAILURE);
      }
    else
      *collection[i] = i;
  clock_gettime(CLOCK_MONOTONIC,  &start);
  if (bunny_thread_foreach(pool, print_data, (void**)&collection[0], len, argv[0]) == false)
    {
      puts("Cannot dispatch orders.");
      bunny_delete_threadpool(pool);
      return (EXIT_FAILURE);
    }
  bunny_thread_wait_completion(pool);
  clock_gettime(CLOCK_MONOTONIC,  &end);
  len = (end.tv_sec - start.tv_sec) * 10e9 + (end.tv_nsec - start.tv_nsec);
  setlocale(LC_NUMERIC, "");
  printf("Time taken: %'zu\n", len);
  bunny_delete_threadpool(pool);
  return (EXIT_SUCCESS);
}

