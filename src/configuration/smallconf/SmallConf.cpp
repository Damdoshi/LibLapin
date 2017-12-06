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
    expression(NULL),
    line(0)
{}

SmallConf::~SmallConf(void)
{
  Clear();
}
