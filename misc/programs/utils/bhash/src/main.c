
#include	<ctype.h>
#include	<lapin.h>

#define		DBUFFER_SIZE		(1024 * 1024 * 512)

const char * const gl_algo[] =
  {
    "multiplier",
    "fnv",
    "fnva",
    "djb2",
    "sdbm",
    "checksum"
  };

int		usage(char	*name)
{
  fprintf(stderr, "Usage is:\n");
  fprintf(stderr, "\t%s algorithm size? files*\n", name);
  fprintf(stderr, "\n\talgos are:\n\n");
  for (size_t i = 0; i < NBRCELL(gl_algo); ++i)
    fprintf(stderr, "\t - %s\n", gl_algo[i]);
  fprintf(stderr, "\n\tdefault size is 8b. Available suffixes are b (bytes), k (kilos), m (mega)\n");
  fprintf(stderr, "\tif no name is precised, stdin is used\n");
  return (EXIT_FAILURE);
}

int		main(int	argc,
		     char	**argv)
{
  if (argc < 2)
    return (usage(*argv));
  int		i;

  for (i = 1; i < argc; ++i)
    if (!strcmp(argv[i], "-h"))
      return (usage(*argv));
  int		alg = -1;

  for (i = 0; i < (int)NBRCELL(gl_algo) && alg < 0; ++i)
    if (!bunny_strcasecmp(gl_algo[i], argv[1]))
      alg = i;
  if (alg == -1)
    {
      fprintf(stderr, "Unknown algorithm %s.\n", argv[1]);
      return (EXIT_FAILURE);
    }
  int		len = 0;
  ssize_t	idx = 0;

  i = 2;
  if (bunny_read_integer(argv[2], &idx, &len))
    {
      if (len <= 0)
	{
	  fprintf(stderr, "Insufficient length %d\n", len);
	  return (EXIT_FAILURE);
	}
      i = 3;
      if (tolower(argv[2][idx]) == 'b')
	len *= 1;
      else if (tolower(argv[2][idx]) == 'k')
	len *= 1024;
      else if (tolower(argv[2][idx]) == 'm')
	len *= 1024 * 1024;
      if (len > DBUFFER_SIZE)
	{
	  fprintf(stderr, "Too big length %d. Maximum is %d\n", len, DBUFFER_SIZE);
	  return (EXIT_FAILURE);
	}
    }
  else
    len = 8;
  char		fbuffer[4096];
  FILE		*pip;

  idx = snprintf(fbuffer, sizeof(fbuffer), "cat");
  for (; i < argc; ++i)
    idx += snprintf(&fbuffer[idx], sizeof(fbuffer) - idx, " %s", argv[i]);
  if (idx >= (ssize_t)sizeof(fbuffer))
    {
      fprintf(stderr, "List of files is too long.\n");
      return (EXIT_FAILURE);
    }
  if ((pip = popen(fbuffer, "r")) == NULL)
    {
      fprintf(stderr, "Cannot open file reader: %s.\n", strerror(errno));
      return (EXIT_FAILURE);
    }
  static char	dbuffer[DBUFFER_SIZE];
  size_t	total = 0;
  ssize_t	rd;

  do
    {
      if ((rd = fread(&dbuffer[total], 1, sizeof(dbuffer) - total, pip)) == 0)
	if (ferror(pip))
	  {
	    perror("");
	    return (EXIT_FAILURE);
	  }
      total += rd;
    }
  while (rd != 0);
  pclose(pip);
  char		*output;

  if ((output = malloc(len)) == NULL)
    {
      perror("");
      return (EXIT_FAILURE);
    }

  bunny_wide_hash(alg, dbuffer, total, output, len);
  for (total = 0; total < (size_t)len;)
    {
      if ((rd = write(1, &output[total], len - total)) < 0)
	{
	  perror("");
	  free(output);
	  return (EXIT_FAILURE);
	}
      total += rd;
    }
  free(output);
  return (EXIT_SUCCESS);
}
