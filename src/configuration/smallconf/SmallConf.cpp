// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2016
//
// Lapin library

#include		<string.h>
#include		"lapin_private.h"

SmallConf::SmallConf(void)
  : construct(PLAIN),
    given_name(false),
    have_value(false),
    converted(0),
    converted_2(0),
    is_converted(false),
    father(NULL),
    last_type(INTEGER),
    sequence(NULL),
    function(NULL),
    expression(NULL)
{}

SmallConf::~SmallConf(void)
{
  std::map<std::string, SmallConf*>::iterator	it;
  std::map<std::string, SmallConf*> dup = nodes;
  std::vector<SmallConf*> dupx = array;
  std::vector<SmallConf*>::iterator itx;

  if (sequence)
    delete sequence;
  if (expression)
    delete expression;
  if (function)
    delete function;
  if (father != NULL && father->nodes.find(name) != father->nodes.end())
    father->nodes.erase(name);
  for (it = dup.begin(); it != dup.end(); ++it)
    delete it->second;
  for (itx = dupx.begin(); itx != dupx.end(); ++itx)
    delete *itx;
}
