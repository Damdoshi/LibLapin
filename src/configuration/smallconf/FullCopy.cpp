// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2025
//
// Lapin library

#include		"lapin_private.h"

void			SmallConf::FullCopy(const SmallConf		&a)
{
  given_name = a.given_name;
  name = a.name;
  address = a.address;
  have_value = a.have_value;
  original_value = a.original_value;
  converted = a.converted;
  converted_2 = a.converted_2;
  alias_on = a.alias_on;
  distant_string = a.distant_string;
  distant_double = a.distant_double;
  distant_int = a.distant_int;
  distant_char = a.distant_char;
  distant_bool = a.distant_bool;
  is_converted = a.is_converted;
  create_mode = a.create_mode;
  file_read = a.file_read;
  file_path = a.file_path;
  additionnal_path_to_pop = a.additionnal_path_to_pop;
  just_pushed = a.just_pushed;
  father = a.father;
  last_type = a.last_type;
  symbol = a.symbol;
  was_b46 = a.was_b64;
  was_text_lock = a.was_text_lock;
  local_root = a.local_root;
  is_const = a.is_const;
  is_solid = a.is_solid;
  is_eternal = a.is_eternal;
  sequence = a.sequence;
  function = a.function;
  expression = a.expression;
  line = a.line;
  array.resize(a.array.length());
  for (int i = 0; i < (int)a.array.length(); ++i)
    (*this)[i].FullCopy(a[i]);
  for (auto it = a.nodes.begin(); it != a.nodes.end(); ++it)
    (*this)[it->first].FullCopy(*it->second);
  iterator = a.iterator;
}

