// Jason Brillante "Damdoshi"
// Pentacle Technologie 2009-2014
//
// INI io system

#include		"Ini.hpp"

bool			bpt::Ini::ReadArray(const bpt::string	&code,
					    unsigned int	&i,
					    std::vector<bpt::string> &val)
{
  bpt::string		buffer;
  unsigned int		j;

  do
    {
      ReadSeparator(code, i);
      j = i;
      if (CheckChar(code, j, "\""))
	{
	  if (ReadString(code, j, buffer) != 0)
	    {
	      errmsg = "ini: error while reading a complex string.";
	      return (false);
	    }
	}
      else
	{
	  int		k;

	  for (; code[j] != ',' && code[j] != '\n' && code[j] != '\0'; ++j);
	  buffer = code.substr(i, j - i);
	  for (k = 0; buffer[k] != '\0'; ++k)
	    if (buffer[k] == '\r')
	      buffer[k] = '\0';
	}
      ReadSeparator(code, j);
      val.push_back(buffer);
      i = j;
    }
  while (ReadText(code, i, ","));
  return (true);
}

bool			bpt::Ini::Read(const bpt::string	&code)
{
  bpt::string		current = "";
  std::stringstream	ss;
  unsigned int		i;

  i = 0;
  ReadSeparator(code, i);
  while (code[i] != '\0')
    {
      unsigned int	j;

      j = i;
      if (ReadText(code, j, "["))
	{
	  i = j;
	  if (ReadChar(code, j, FieldName) == false)
	    {
	      errmsg = "ini: expected scope name after '['.";
	      return (false);
	    }
	  current = code.substr(i, j - i);

	  /// if there is several scope with the same name
	  if (datas.find(current) != datas.end())
	    {
	      std::string	test;
	      int		num;

	      num = 0;
	      do
		{
		  std::stringstream	ss;

		  ss << current << num;
		  test = ss.str();
		  num += 1;
		}
	      while (datas.find(test) != datas.end());
	      current = test;
	    }

	  if (ReadText(code, j, "]") == false)
	    {
	      errmsg = "ini: expected ']' after scope name.";
	      return (false);
	    }
	}
      else
	{
	  bpt::string	field;

	  if (ReadChar(code, j, FieldName) == false)
	    {
	      errmsg = "ini: expected field name.";
	      return (false);
	    }
	  field = code.substr(i, j - i);

	  /// if there is several field with the same name
	  if (datas[current].find(field) != datas[current].end())
	    {
	      std::map<bpt::string, std::vector<bpt::string> > &nod = datas[current];
	      std::string	test;
	      int		num;

	      num = 0;
	      do
		{
		  std::stringstream	ss;

		  ss << field << num;
		  test = ss.str();
		  num += 1;
		}
	      while (nod.find(test) != nod.end());
	      field = test;
	    }

	  ReadWhitespace(code, j);
	  if (ReadText(code, j, "=") == false)
	    {
	      errmsg = "ini: expected '=' after field name.";
	      return (false);
	    }
	  ReadWhitespace(code, j);
	  if (ReadArray(code, j, datas[current][field]) == false)
	    return (false);
	}
      i = j;
      ReadSeparator(code, i);
    }
  return (true);
}
