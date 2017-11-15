// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2016
//
// Lapin library

#include		<string.h>
#include		"lapin_private.h"

Decision		dabsic_read_inside_sequence(const char		*code,
						    ssize_t		&i,
						    SmallConf		&conf,
						    SmallConf		&root)
{
  if (conf.sequence == NULL)
    try
      {
	conf.sequence = new Sequence;
	conf.sequence->nbr_lines = 0;
      }
    catch (...)
      {
	scream_error_if
	  (return (BD_ERROR), ENOMEM,
	   "Memory exhausted while processing sequence on line %d",
	   whichline(code, i)
	   );
      }
  Sequence		&seq = *conf.sequence;
  std::string		label;
  
  while (code[i] != '\0' && code[i] != ']')
    {
      if (seq.nbr_lines >= seq.lines.size())
	seq.lines.resize(seq.lines.size() + 64);

      if (dabsic_read_sequence_label(code, i, label))
	{
	  if (seq.labels.find(seq.nbr_lines) != seq.labels.end())
	    scream_error_if
	      (return (BD_ERROR), BE_SYNTAX_ERROR,
	       "Address %d is already covered by a label so %s is excessive, "
	       "on line %d",
	       seq.nbr_lines, label, whichline(code, i)
	       );
	  seq.labels[seq.nbr_lines] = label;
	}
      dabsic_read_separator(code, i);

      if (code[i] == '@')
	{
	  if (_bunny_handle_directive
	      (code, i, &conf, &root, dabsic_read_separator) == false)
	    return (BD_ERROR);
	  dabsic_read_separator(code, i);
	}
      else
	{
	  if (dabsic_read_sequence_line(code, i, seq.lines[seq.nbr_lines], root) == BD_ERROR)
	    return (BD_ERROR);
	  dabsic_read_separator(code, i);
	  seq.nbr_lines += 1;
	}
    }
  return (BD_OK);
}

