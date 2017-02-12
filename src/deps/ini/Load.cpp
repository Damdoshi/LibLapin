// Jason Brillante "Damdoshi"
// Pentacle Technologie 2009-2014
//
// INI io system

#include		<fstream>
#include		"Ini.hpp"

bool			bpt::Ini::Load(const bpt::string	&file)
{
  bpt::ifstream		ss((char*)file.c_str(), std::ios::in | std::ios::binary);

  if (!ss)
    {
      errmsg = "ini: cannot open file";
      return (false);
    }
  bpt::string		code;
  bool			erase;
  size_t		i;
  int			tmp;

  ss.seekg(0, std::ios::end);
  code.resize(ss.tellg());
  ss.seekg(0, std::ios::beg);
  ss.read(&code[0], code.size());
  for (i = 0, erase = false; i < code.size(); ++i)
    if (code[i] == '#')
      {
	erase = true;
	code[i] = '\n';
	for (tmp = i; tmp > 0 && (tmp == ' ' || tmp == '\t'); --tmp)
	  code[tmp] = '\n';
      }
    else if (erase == true)
      {
	if (code[i] == '\n')
	  erase = false;
	else
	  code[i] = '\n';
      }
  ss.close();
  return (Read(code));
}

