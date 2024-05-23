// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2018
//
// Lapin library

#include		<string.h>
#include		"lapin_private.h"

SmallConf		&SmallConf::operator[](const std::string	&str)
{
  SmallConf		**slot;

  if (*(slot = &nodes[str]) == NULL)
    {
      if (create_mode)
	{
	  std::stringstream ss;

	  if (father)
	    ss << this->address << "." << str;
	  else
	    ss << this->address << str;
	  *slot = new SmallConf;
	  (*slot)->given_name = true;
	  (*slot)->name = str;
	  (*slot)->father = this;
	  (*slot)->address = ss.str();
	}
      else
	{
	  nodes.erase(str);
	  bunny_errno = BE_CANNOT_FIND_ELEMENT;
	  throw 0;
	}
    }
  return (**slot);
}

const SmallConf		&SmallConf::operator[](const std::string	&str) const
{
  return ((*const_cast<SmallConf*>(this))[str]);
}

SmallConf		&SmallConf::operator[](ssize_t			i)
{
  ssize_t		olsize;

  if (i == 0 && array.size() == 0 && create_mode == false && have_value)
    return (*this);

  while (i < 0)
    i += array.size();
  
  if ((olsize = array.size()) <= i)
    {
      if (!create_mode)
	{
	  bunny_errno = BE_CANNOT_FIND_ELEMENT;
	  throw 0;
	}
      array.resize(i + 1);
      while (olsize <= i)
	{
	  std::stringstream ss, sx;

	  sx << this->address << "[" << i << "]";
	  ss << this->name << "[" << i << "]";
	  array[olsize] = new SmallConf;
	  array[olsize]->father = this;
	  array[olsize]->given_name = false;
	  array[olsize]->name = ss.str();
	  array[olsize]->address = sx.str();
	  olsize += 1;
	}
    }
  return (*array[i]);
}

const SmallConf		&SmallConf::operator[](ssize_t			i) const
{
  return ((*const_cast<SmallConf*>(this))[i]);
}
