// Jason Brillante "Damdoshi"
// Pentacle Technologie 2009-2014
//
// INI io system

#include		<fstream>
#include		"Ini.hpp"

bool			bpt::Ini::Save(const bpt::string	&file) const
{
  std::ofstream							fil;

  fil.open(file.c_str(), std::ostream::out);
  if (fil.is_open() == false)
    return (false);
  Save(fil);
  fil.close();
  return (true);
}

void			bpt::Ini::Save(bpt::ostream		&os) const
{
  std::map<bpt::string, Scope>::const_iterator			it;

  for (it = datas.begin(); it != datas.end(); ++it)
    {
      std::map<bpt::string, FieldValue>::const_iterator		itx;

      if (it->first != "")
	os << "[" << it->first << "]" << std::endl;
      for (itx = it->second.begin(); itx != it->second.end(); ++itx)
	{
	  std::vector<bpt::string>::const_iterator		ity;
	  int							ipl;	// info per line

	  ipl = 0;
	  os << itx->first << "=";
	  ity = itx->second.begin();
	  while (ity != itx->second.end())
	    {
	      os << '"' << BuildString(*ity) << '"';
	      if (++ity != itx->second.end())
		{
		  os << ",";
		  if (++ipl % 10 == 0)
		    os << std::endl;
		}
	    }
	  os << std::endl;
	}
    }
}
