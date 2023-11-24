// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2018
//
// Lapin library

#include		<string.h>
#include		"lapin_private.h"

int			SmallConf::additionnal_path_to_pop = 0;

SmallConf::SmallConf(void)
  : construct(PLAIN),
    given_name(false),
    have_value(false),
    converted(0),
    converted_2(0),
    alias_on(NULL),
    distant_string(NULL),
    distant_double(NULL),
    distant_int(NULL),
    distant_char(NULL),
    distant_bool(NULL),
    is_converted(false),
    father(NULL),
    last_type(INTEGER),
    symbol(false),
    was_b64(false),
    sequence(NULL),
    function(NULL),
    expression(NULL),
    line(0)
{
  if (file_read.empty())
    file_read.push("");
  if (file_path.empty())
    file_path.push_back("");
}

SmallConf::~SmallConf(void)
{
  Clear();
}
