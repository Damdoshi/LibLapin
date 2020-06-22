// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2016
//
// Bibliotheque Lapin

#ifndef				__LAPIN_CPP_IDSTRING_HPP__
# define			__LAPIN_CPP_IDSTRING_HPP__
# if				__cplusplus > 199711L
#  include			<string.h>
#  include			<stdint.h>

namespace			Bunny
{
  class				IdString
  {
  private:
    uint64_t			hash;
    const char			*string;

  public:
    inline operator		uint64_t (void) const
    {
      return (hash);
    }
    inline operator		std::string (void) const
    {
      return (std::string(string));
    }
    inline operator		const char * (void) const
    {
      return (string);
    }

    inline uint64_t		GetHash(void) const
    {
      return (hash);
    }
    inline std::string		GetString(void) const
    {
      static const std::string	empty("");

      if (string)
	return (string);
      return (empty);
    }

  private:
    constexpr static uint64_t	_Hash(const char			*s,
				      uint64_t				hs)
    {
      return (!*s ? hs : _Hash(&s[1], (hs << 5) + hs + *s));
    }

  public:

    constexpr static uint64_t	Hash(const char				*s)
    {
      return (s ? _Hash(s, 5381) : 5381);
    }

    inline bool			operator==(const IdString		&b) const
    {
      return (hash == b.hash);
    }
    inline bool			operator!=(const IdString		&b) const
    {
      return (hash != b.hash);
    }
    inline bool			operator<(const IdString		&b) const
    {
      return (strcmp(GetString().c_str(), b.GetString().c_str()) < 0);
    }

    inline bool			operator==(const std::string		&b) const
    {
      return (GetString() == b);
    }
    inline bool			operator!=(const std::string		&b) const
    {
      return (GetString() != b);
    }
    inline bool			operator<(const std::string		&b) const
    {
      return (strcmp(GetString().c_str(), b.c_str()) < 0);
    }

    inline bool			operator==(const char			*b) const
    {
      return (strcmp(GetString().c_str(), b) == 0);
    }
    inline bool			operator!=(const char			*b) const
    {
      return (strcmp(GetString().c_str(), b) != 0);
    }
    inline bool			operator<(const char			*b) const
    {
      return (strcmp(GetString().c_str(), b) < 0);
    }

    inline IdString		&operator=(const IdString		&a)
    {
      hash = a.hash;
      string = a.string;
      return (*this);
    }
    inline IdString		&operator=(const char			*a)
    {
      hash = ::Bunny::IdString::Hash(a);
      string = a;
      return (*this);
    }
    constexpr			IdString(const char			*str)
      : hash(::Bunny::IdString::Hash(str)),
	string(str)
    {}
    constexpr			IdString(const IdString			&str)
      : hash(str.hash),
	string(str.string)
    {}
    constexpr			IdString(void)
      : hash(::Bunny::IdString::Hash(NULL)),
	string(NULL)
    {}

    friend std::ostream		&operator<<(std::ostream		&os,
					    const Bunny::IdString	&str);
  };
  inline std::ostream		&operator<<(std::ostream		&os,
					    const Bunny::IdString	&str)
  {
    os << str.string;
    return (os);
  }

  constexpr IdString NoIdString{NULL};
}

constexpr Bunny::IdString	operator""_IS(const char		*s,
					      size_t)
{
  return (Bunny::IdString(s));
}

# endif
#endif	/*			__LAPIN_CPP_IDSTRING_HPP__		*/
