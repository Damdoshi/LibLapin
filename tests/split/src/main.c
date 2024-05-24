/*
** Jason Brillante "Damdoshi"
** Hanged Bunny Studio 2014-2017
**
** LibLapin Test
*/

#include		<stdio.h>
#include		<signal.h>
#include		<stdlib.h>
#include		<time.h>
#include		<string.h>
#include		<assert.h>
#include		<lapin.h>

typedef struct		s_test
{
  const char		*string;
  const char		*toks[5];
  bool			agreg;
  const char		*out[20];

  const char		*implode_tok;
  bool			no_last;
  const char		*result;
}			t_test;

t_test			gl_test[] =
  {
    {
      "Les Lapins Noirs",
      {" ", NULL},
      false,
      {"Les", "Lapins", "Noirs", NULL},
      "_", true, "Les_Lapins_Noirs"
    },

    {
      "Les  Lapins  Noirs",
      {" ", NULL},
      false,
      {"Les", "", "Lapins", "", "Noirs", NULL},
      "_", false, "Les__Lapins__Noirs_"
    },

    {
      "Les  Lapins  Noirs",
      {" ", NULL},
      true,
      {"Les", "Lapins", "Noirs", NULL},
      "!", true, "Les!Lapins!Noirs"
    },

    {
      "   Les  Lapins  Noirs   ",
      {" ", NULL},
      true,
      {"Les", "Lapins", "Noirs", NULL},
      "!", true, "Les!Lapins!Noirs"
    },

    {
      "La   LibLapin est plus     qu' une bibliotheque graphique.",
      {" ", "'", ".", NULL},
      true,
      {"La", "LibLapin", "est", "plus", "qu", "une", "bibliotheque", "graphique", NULL},
      "", true, "LaLibLapinestplusquunebibliothequegraphique"
    },

    {
      "Ceci == Cela",
      {"==", " ", NULL},
      false,
      {"Ceci", "", "", "Cela", NULL},
      "", false, "CeciCela"
    },


    {
      "Ceci == Cela",
      {"==", " ", NULL},
      true,
      {"Ceci", "Cela", NULL},
      "=", true, "Ceci=Cela"
    },

    {
      "LeMegaTokenDeLaMortQuiTue UnAutre Token Tres Bizarre",
      {"LeMegaTokenDeLaMortQuiTue", "UnAutre Token Tres Bizarre", NULL},
      false,
      {"", " ", NULL}, // "" because it start with a token
      "", true, ""
    },

    {
      "LeMegaTokenDeLaMortQuiTue UnAutre Token Tres Bizarre",
      {"LeMegaTokenDeLaMortQuiTue", "UnAutre Token Tres Bizarre", NULL},
      true,
      {" ", NULL}, // "" because it start with a token
      "", false, ""
    },

    {NULL, {NULL}, false, {NULL}, NULL, false, NULL}
  };

static void		sighandler(int			sig)
{
  (void)sig;
  exit(EXIT_FAILURE);
}

static size_t		wordtablen(const char * const	*wt)
{
  size_t		i;

  for (i = 0; wt[i] != NULL; ++i);
  return (i);
}

static int		wordtabprint(const char * const	*wt)
{
  size_t		i, c;

  for (i = 0, c = 0; wt[i] != NULL; ++i)
    if (wt[i + 1])
      c += fprintf(stderr, "\"%s\", ", wt[i]);
    else
      c += fprintf(stderr, "\"%s\"", wt[i]);
  return (c);
}

static void		test(void)
{
  const char * const	*tab;
  char			*merge;
  size_t		i, j;

  for (i = 0; gl_test[i].string != NULL; ++i)
    {
      if ((tab = bunny_split(gl_test[i].string, &gl_test[i].toks[0], gl_test[i].agreg)) == NULL)
	{
	  fprintf(stderr, "Test %zu: Memory exhausted.\n", i);
	  exit(EXIT_FAILURE);
	}
      for (j = 0; gl_test[i].out[j] != NULL; ++j)
	{
	  if (tab[j] == NULL)
	    {
	      fprintf(stderr, "Test %zu: Wordtab is shorter than expected. Expected %zu, got %zu (",
		      i, wordtablen(&gl_test[i].out[0]), j);
	      wordtabprint(tab);
	      fprintf(stderr, ")\n");
	      exit(EXIT_FAILURE);
	    }
	  if (strcmp(gl_test[i].out[j], tab[j]) != 0)
	    {
	      fprintf(stderr, "Test %zu: Wordtab mismath at index %zu. Expected %s, got %s.\n",
		      i, j, gl_test[i].out[j], tab[j]);
	      exit(EXIT_FAILURE);
	    }

	  if ((merge = bunny_stick(tab, gl_test[i].implode_tok, gl_test[i].no_last)) == NULL)
	    {
	      fprintf(stderr, "Test %zu: Memory exhausted.\n", i);
	      exit(EXIT_FAILURE);
	    }
	  if (strcmp(merge, gl_test[i].result) != 0)
	    {
	      fprintf(stderr, "Test %zu: Merge mismath. Expected %s, got %s.\n",
		      i, gl_test[i].result, merge);
	      exit(EXIT_FAILURE);
	    }
	  bunny_free(merge);
	}
      bunny_delete_split(tab);
    }
}

int			main(int			argc,
			     char			**argv)
{
  (void)argv;
  srand(time(NULL));
  signal(SIGALRM, sighandler);
  if (argc == 2)
    alarm(2);
  test();
  return (EXIT_SUCCESS);
}
