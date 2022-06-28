// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2018
//
// Lapin library

#include		"lapin_private.h"

void			shrink_single_element_array(SmallConf		&cnf)
{
  if (cnf.Size() != 1)
    return ;

  // cnf = cnf[0];

  cnf.have_value = cnf[0].have_value;
  cnf.original_value = cnf[0].original_value;
  cnf.converted = cnf[0].converted;
  cnf.converted_2 = cnf[0].converted_2;
  cnf.alias_on = cnf[0].alias_on;
  cnf.distant_string = cnf[0].distant_string;
  cnf.distant_double = cnf[0].distant_double;
  cnf.distant_int = cnf[0].distant_int;
  cnf.distant_char = cnf[0].distant_char;
  cnf.distant_bool = cnf[0].distant_bool;
  cnf.is_converted = cnf[0].is_converted;
  cnf.create_mode = cnf[0].create_mode;
  cnf.file_read = cnf[0].file_read;
  cnf.file_path = cnf[0].file_path;
  cnf.last_type = cnf[0].last_type;
  cnf.symbol = cnf[0].symbol;
  cnf.was_b64 = cnf[0].was_b64;
  cnf.line = cnf[0].line;
    
  cnf.expression = cnf[0].expression;
  cnf[0].expression = NULL;
  cnf.sequence = cnf[0].sequence;
  cnf[0].sequence = NULL;
  cnf.function = cnf[0].function;
  cnf[0].function = NULL;

  delete &cnf[0];
  cnf.array.clear();
}

