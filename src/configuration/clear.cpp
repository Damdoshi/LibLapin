// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2020
//
// Lapin library

#include	"lapin_private.h"

void		bunny_clear_configuration(t_bunny_configuration	*cnf)
{
  SmallConf	*c = (SmallConf*)cnf;
  std::map<std::string, SmallConf*>::iterator	it;
  std::map<std::string, SmallConf*> dup = c->nodes;
  std::vector<SmallConf*> dupx = c->array;
  std::vector<SmallConf*>::iterator itx;

  delete c->sequence;
  c->sequence = NULL;
  delete c->expression;
  c->expression = NULL;
  delete c->function;
  c->function = NULL;

  for (it = dup.begin(); it != dup.end(); ++it)
    {
      it->second->father = NULL; // Isolate the node from its tree so it does not destroy it
      delete it->second;
    }
  c->nodes.clear();

  for (itx = dupx.begin(); itx != dupx.end(); ++itx)
    delete *itx;
  dupx.clear();
}
