/*
**
**
**
**
**
*/

#include			<list>
#include			<map>
#include			<vector>
#include			<lapin.h>

#define				BYTE_MERGE

int				population = 100;
double				trash_percent = 0.3;

t_bunny_window			*win;
t_bunny_pixelarray		*pix;

typedef struct			s_gened
{
  unsigned int			x;
  unsigned int			y;
}				t_gened;

typedef union			s_gene
{
  t_gened			gened;
  char				data[sizeof(t_gened)];
}				t_gene;

typedef struct			s_people
{
  int				life;
  t_gene			gene;
  struct s_people		*best_fit;
  double			best_fit_score;
  unsigned int			color;

  s_people(void)
    : life(2),
      best_fit(NULL),
      best_fit_score(0.0)
  {
    color = rand() | BLACK;
    gene.gened.x = rand() % pix->clipable.buffer.width;
    gene.gened.y = rand() % pix->clipable.buffer.height;
  }
}				t_people;

std::vector<t_people>		people;

double				heuristic(t_gened	*a,
					  t_gened	*b)
{
  return (1.0 / sqrt(pow(a->x - b->y, 2) + pow(a->y - b->y, 2)));
}

void				new_people(t_gene	*a,
					   t_gene	*b)
{
  t_people			pep;

#ifndef			BYTE_MERGE
  if (rand() % 2)
    pep.gene.gened.x = a->gened.x;
  else
    pep.gene.gened.x = b->gened.x;
  if (rand() % 2)
    pep.gene.gened.y = a->gened.y;
  else
    pep.gene.gened.y = b->gened.y;
#else
  for (size_t i = 0; i < sizeof(a->data); ++i)
    if (rand() % 2)
      pep.gene.data[i] = a->data[i];
    else
      pep.gene.data[i] = b->data[i];
#endif

  people.push_back(pep);
}

void				cycle(void)
{
  std::vector<t_people>::iterator it;
  std::vector<t_people>::iterator jt;
  double			h;

  for (it = people.begin(); it != people.end(); ++it)
    {
      for (jt = it; jt != people.end(); ++jt)
	{
	  h = heuristic(&it->gene.gened, &jt->gene.gened);
	  if (h > it->best_fit_score)
	    {
	      it->best_fit_score = h;
	      jt->best_fit_score = h;
	      it->best_fit = &*jt;
	      jt->best_fit = &*it;
	    }
	}
    }
  std::map<double, std::list<t_people*> > order;
  size_t			cnt, olpeople;

  for (it = people.begin(); it != people.end(); ++it)
    order[it->best_fit_score].push_back(&*it);
  auto				kt = order.begin();

  olpeople = people.size();
  for (cnt = 0; cnt < olpeople && kt != order.end(); ++kt)
    {
      if (cnt >= olpeople * trash_percent)
	{
	  std::list<t_people*>::iterator lt;

	  for (lt = kt->second.begin(); lt != kt->second.end(); ++lt)
	    {
	      new_people(&(*lt)->gene, &(*lt)->best_fit->gene);
	      cnt += 1;
	    }
	}
      else
	cnt += 1;
    }
}

void				generation(void)
{
  std::vector<t_people>::iterator it;

  it = people.begin();
  while (it != people.end())
    if ((it->life -= 1) <= 0)
      it = people.erase(it);
    else
      ++it;
  people.resize(people.size() + population - people.size());
}

t_bunny_response		display(void		*)
{
  std::vector<t_people>::iterator it;

  memset(pix->pixels, 0, pix->clipable.buffer.width * pix->clipable.buffer.height * sizeof(t_bunny_color));
  for (it = people.begin(); it != people.end(); ++it)
    {
      t_bunny_position	pos = {(int)it->gene.gened.x, (int)it->gene.gened.y};

      pos.x += rand() % 6 - 3;
      pos.y += rand() % 6 - 3;
      
      if (pos.x >= 0 && pos.x < pix->clipable.buffer.width &&
	  pos.y >= 0 && pos.y < pix->clipable.buffer.height)
	{
	  if (it->life >= 2)
	    ((unsigned int*)pix->pixels)[pos.x + pos.y * pix->clipable.buffer.width] = WHITE;
	  else
	    ((unsigned int*)pix->pixels)[pos.x + pos.y * pix->clipable.buffer.width] = it->color;
	}
    }
  bunny_blit(&win->buffer, &pix->clipable, NULL);
  bunny_display(win);
  return (GO_ON);
}

t_bunny_response		key(t_bunny_event_state	state,
				    t_bunny_keysym	sym,
				    void		*)
{
  if (state == GO_UP)
    return (GO_ON);
  if (sym == BKS_ESCAPE)
    return (EXIT_ON_SUCCESS);
  if (sym == BKS_SPACE)
    {
      cycle();
      generation();
    }
  return (GO_ON);
}

t_bunny_context			gl_context =
  {
   .key = key,
   .display = display
  };

int				main(void)
{
  win = bunny_start(800, 600, false, "Genetics");
  pix = bunny_new_pixelarray(win->buffer.width, win->buffer.height);
  memset(pix->pixels, 0, pix->clipable.buffer.width * pix->clipable.buffer.height * sizeof(t_bunny_color));

  generation();
	
  bunny_set_context(&gl_context);
  bunny_loop(win, 20, NULL);

  bunny_delete_clipable(&pix->clipable);
  bunny_stop(win);
  return (EXIT_SUCCESS);
}
