// Jason Brillante "Damdoshi"
// Pentacle Technologie 2009-2013
//
// Ini io system

#ifndef						__BPT_INI_IO_SYSTEM_HPP__
# define					__BPT_INI_IO_SYSTEM_HPP__
# include					<vector>
# include					<map>
# include					"ParsingTools.hpp"

namespace					bpt
{
  class						Ini : public bpt::ParsingTools
  {
  public:
    // private to public shitty fix for liblapin
    mutable bpt::string				errmsg;
    
  private:
    /// In Read.cpp
    bool					ReadArray(const bpt::string	&code,
							  unsigned int		&i,
							  std::vector<bpt::string> &val);

  public:
    typedef std::vector<bpt::string>		FieldValue;
    typedef std::map<bpt::string, FieldValue>	Scope;

    const bpt::string				&npos;

  protected:
    std::map<bpt::string, Scope>		datas;

  public:
    const bpt::string				&Access(const bpt::string	&scope,
							const bpt::string	&field,
							unsigned int		_case = 0) const;
    bpt::string					&Access(const bpt::string	&scope,
							const bpt::string	&field,
							unsigned int		_case = 0);
    int						AccessInt(const bpt::string	&scope,
							  const bpt::string	&field,
							  unsigned int		_case = 0) const;
    int						AccessInt(const bpt::string	&scope,
							  const bpt::string	&field,
							  unsigned int		_case = 0);
    double					AccessDbl(const bpt::string	&scope,
							  const bpt::string	&field,
							  unsigned int		_case = 0) const;
    double					AccessDbl(const bpt::string	&scope,
							  const bpt::string	&field,
							  unsigned int		_case = 0);

    std::map<bpt::string, Scope>		&GetData(void);
    const std::map<bpt::string, Scope>		&GetData(void) const;

    void					Clear(void);

    bool					Load(const bpt::string		&file);
    bool					Read(const bpt::string		&text);

    bool					Save(const bpt::string		&file) const;
    void					Save(bpt::ostream		&os) const;

    Ini(void);
    virtual ~Ini(void);
  };
}

#endif	//		__BPT_INI_IO_SYSTEM_HPP__
