/*
** Jason Brillante "Damdoshi"
** Hanged Bunny Studio 2014-2017
**
** LibLapin Test
*/

#include		<unistd.h>
#include		<fcntl.h>
#include		<string.h>
#include		<stdio.h>
#include		<time.h>
#include		<signal.h>
#include		<assert.h>
#include		<stdlib.h>
#include		<lapin.h>

static void		sighandler(int		sig)
{
  (void)sig;
  exit(EXIT_FAILURE);
}

void			test(const char		*file)
{
  char			data_to_encode[4096];
  size_t		len_to_encode;

  char			data_encoded[8128];
  char			*ptr_encoded = &data_encoded[0];
  size_t		len_encoded = sizeof(data_encoded);

  char			data_restored[8218];
  void			*ptr_restored = &data_restored[0];
  size_t		len_restored = sizeof(data_restored);

  size_t		i;

  if (file == NULL)
    {
      len_to_encode = rand() % (sizeof(data_to_encode) - 1) + 1;
      for (i = 0; i < len_to_encode; ++i)
	data_to_encode[i] = (unsigned char)(rand() % 256);
      data_to_encode[i] = '\0';
    }
  else
    {
      if ((i = open(file, O_RDONLY)) == (size_t)-1)
	{
	  perror("open");
	  exit(EXIT_FAILURE);
	}
      if ((len_to_encode = read(i, &data_to_encode[0], sizeof(data_to_encode))) == (size_t)-1)
	{
	  perror("read");
	  exit(EXIT_FAILURE);
	}
      close(i);
    }

  if (bunny_base64_encode
      (&data_to_encode[0], len_to_encode, &ptr_encoded, &len_encoded) == false)
    {
      printf("\nTo encode: %s failed\n", &data_to_encode[0]);
      exit(EXIT_FAILURE);
    }

  if (bunny_base64_check(&data_encoded[0], len_encoded) == false)
    {
      printf("\nThe following:\n%s\nIs not a valid base64 encoded data.\n",
	     &data_encoded[0]);
      exit(EXIT_FAILURE);
    }

  if (bunny_base64_decode
      (&data_encoded[0], len_encoded, &ptr_restored, &len_restored) == false)
    {
      printf("\nTo decode: %s failed\n", &data_encoded[0]);
      exit(EXIT_FAILURE);
    }

  if (len_restored != len_to_encode)
    {
      printf("\nSize mismatch: %zu (restored) != %zu (original).\n"
	     "Original is %s.\nbase64 is %s.\nRestored is %s.\n",
	     len_restored, len_to_encode,
	     &data_to_encode[0],
	     &data_encoded[0],
	     &data_restored[0]);
      exit(EXIT_FAILURE);
    }

  for (i = 0; i < len_to_encode; ++i)
    if (data_to_encode[i] != data_restored[i])
      {
	printf("\nFailed to match %X with %X at position %zu on %zu.\n",
	       data_to_encode[i], data_restored[i], i, len_to_encode);
	exit(EXIT_FAILURE);
      }
}

int			main(int		argc,
			     char		**argv)
{
  t_bunny_time		bef, now;
  char			buffer[1024 * 1024];
  char			*ptr = &buffer[0];
  char			*out = NULL;
  size_t		len;
  size_t		i;

  (void)argv;
  srand(time(NULL));
  signal(SIGALRM, sighandler);
  if (argc == 2)
    alarm(2);

  if (argc == 3)
    {
      len = read(0, &buffer[0], sizeof(buffer));
      /*
	if (buffer[len - 1] == '\n')
	buffer[--len] = '\0';
	else
	buffer[len] = '\0';
      */
      if (*argv[1] == 'e')
	{
	  assert(bunny_base64_encode(ptr, len, &out, &len));
	  assert(bunny_base64_check(out, len));
	}
      else if (*argv[1] == 'd')
	{
	  assert(bunny_base64_check(&buffer[0], len));
	  bunny_base64_decode(ptr, len, (void**)&out, &len);
	}
      write(1, out, strlen(out));
      bunny_free(out);
    }
  else
    {
      bef = bunny_get_time();
      for (i = 0; i < 1000; ++i)
	{
	  printf("\rTest n=%zu", i);
	  fflush(stdout);
	  test(NULL);
	}
      printf("\r#### All random tests done! ####\n");
      now = bunny_get_time();
      printf("Nanoseconds per operation: %d.\n",
	     (int)(bunny_delta_time(bef, now) / 1e3)
	     );
    }
  return (EXIT_SUCCESS);
}

