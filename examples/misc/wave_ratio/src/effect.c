

#include	<lapin.h>

t_bunny_effect	*soften(t_bunny_effect	*eff,
			int		durcaz)
{
  t_bunny_effect *n = bunny_new_effect(eff->duration);
  double	sum;
  int		cnt;

  for (int i = 0; i < eff->duration * eff->sample_per_second; ++i)
    {
      int	j = i - durcaz;

      if (j < 0)
	j = 0;
      sum = 0;
      cnt = 0;
      while (j < i + durcaz && j < eff->duration * eff->sample_per_second)
	{
	  sum += eff->sample[j];
	  cnt += 1;
	  j += 1;
	}
      if (cnt)
	sum /= cnt;
      n->sample[i] = sum;
    }
  bunny_delete_sound(&eff->sound);
  return (n);
}

int		main(int	argc,
		     char	**argv)
{
  t_bunny_effect *eff;
  double	ref;
  int		smooth;

  if (argc == 1)
    smooth = 1;
  else
    smooth = atoi(argv[1]);
  eff = bunny_new_effect(10);

  double	la = 220.0;
  double	dur = 1.0 / la;
  int		caz = dur * eff->sample_per_second;
  int		idx = 0;
  bool		up = true;

  while (idx < eff->duration * eff->sample_per_second)
    {
      for (int i = 0; i < caz; ++i)
	{
	  if (i < caz * ref)
	    eff->sample[idx] = -20000;
	  else
	    eff->sample[idx] = 20000;
	  // eff->sample[idx] += rand() % 20000 - 10000;
	  idx += 1;
	}
      if (up)
	{
	  if ((ref += 0.001) >= 1.0)
	    {
	      ref = 1.0;
	      up = false;
	    }
	}
      else
	{
	  if ((ref += -0.001) <= 0.0)
	    {
	      ref = 0.0;
	      up = true;
	    }
	}
    }
  eff = soften(eff, smooth);
  bunny_compute_effect(eff);
  bunny_sound_play(&eff->sound);
  bunny_usleep(1e7);
  bunny_sound_stop(&eff->sound);
  return (0);
}
