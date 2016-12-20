// Jason Brillante "Damdoshi"
// Lisa Monpierre "Leeza"
// Pentacle Technologie 2009-2013
//
// DABSIC
// Developer's All-purpose Block Structured Instruction Code

#ifndef				__BPT_PARSINGTOOLS_HPP__
# define			__BPT_PARSINGTOOLS_HPP__
# include			<iostream>
# include			<fstream>
# include			<sstream>

namespace			bpt
{
  typedef std::string		string;
  typedef std::ostream		ostream;
  typedef std::istream		istream;
  typedef std::ofstream		ofstream;
  typedef std::ifstream		ifstream;
  typedef std::stringstream	stringstream;
  class				ParsingTools
  {
  public:
    enum		Decision
      {
	STOP,
	ALTERNATIVE,
	DONE
      };

    static const bpt::string	FieldNameFirstChar;
    static const bpt::string	FieldName;

    static const bpt::string	Teal;
    static const bpt::string	Blue;
    static const bpt::string	Red;
    static const bpt::string	Green;
    static const bpt::string	Purple;
    static const bpt::string	Yellow;
    static const bpt::string	White;
    static const bpt::string	Pink;
    static const bpt::string	Grey;
    static const bpt::string	BlackOnWhite;

    static const bpt::string	OpenSection;
    static const bpt::string	CloseSection;
    static const bpt::string	Assignation[4];
    static const bpt::string	Address;
    static const bpt::string	Pointer;

    static const bpt::string	Include[2];
    static const bpt::string	IncludeCipher[2];
    static const bpt::string	Message[1];
    static const bpt::string	Warning[2];
    static const bpt::string	ErrorD[2];

    static const bpt::string	Extern[1];
    static const bpt::string	Local[1];
    static const bpt::string	Private[2];
    static const bpt::string	Protected[2];
    static const bpt::string	Locked[2];
    static const bpt::string	Public[2];
    static const bpt::string	Limited[2];
    static const bpt::string	Strict[1];
    static const bpt::string	Restricted[2];

    static const bpt::string	Const[2];

    static const bpt::string	HexaPrefix;
    static const bpt::string	Hexadecimal;
    static const bpt::string	DecimalPrefix;
    static const bpt::string	Decimal;
    static const bpt::string	OctalPrefix;
    static const bpt::string	Octal;
    static const bpt::string	BinPrefix;
    static const bpt::string	Binary;

    static const bpt::string	Variant[3];
    static const bpt::string	Boolean[3];
    static const bpt::string	Integer[3];
    static const bpt::string	Real[3];
    static const bpt::string	Character[3];
    static const bpt::string	String[2];
    static const bpt::string	Descriptor[2];
    static const bpt::string	Type[1];
    static const bpt::string	Record[4];

    static const bpt::string	PreviousNode;
    static const bpt::string	DirectAccess;
    static const bpt::string	AddressAccess;
    static const bpt::string	RealComma;
    static const bpt::string	CharacterDelimiter;
    static const bpt::string	StringDelimiter;
    static const bpt::string	PointerPrefix;
    static const bpt::string	DabsicAddressPrefix;
    static const bpt::string	DescriptorPrefix;
    static const bpt::string	TypePrefix;
    static const bpt::string	NullPtr;
    static const bpt::string	NullAddr[2];
    static const bpt::string	Nothing[3];
    static const bpt::string	True[4];
    static const bpt::string	False[4];

    static const bpt::string	OpenScript;
    static const bpt::string	OpenSequence;
    static const bpt::string	OpenData;
    static const bpt::string	OpenXML;
    static const bpt::string	CloseScope;

    static const bpt::string	Field[2];
    static const bpt::string	Collection[1];
    static const bpt::string	Script[1];
    static const bpt::string	Sequence[1];
    static const bpt::string	XMLType[1];

    static const bpt::string	DabsicRoot;
    static const bpt::string	GetAddress;
    static const bpt::string	CurrentNode;

    static const int		DefaultOpenScript;
    static const int		DefaultCloseScript;
    static const int		DefaultOpenSequence;
    static const int		DefaultCloseSequence;
    static const int		DefaultOpenData;
    static const int		DefaultCloseData;
    static const int		DefaultOpenXML;
    static const int		DefaultCloseXML;

    static const bpt::string	OpenPriority;
    static const bpt::string	ClosePriority;
    static const bpt::string	DataLength[4];
    static const bpt::string	Separator;

  private:
    wchar_t		CaseConvert(wchar_t				c) const;
    wchar_t		Endian(wchar_t					c) const;

  protected:
    bool		CheckChar(const bpt::string			&str,
				  unsigned int				index,
				  const bpt::string			&token) const;
    bool		CheckCharCase(const bpt::string			&str,
				      unsigned int			index,
				      const bpt::string			&token) const;

    bool		CheckText(const bpt::string			&str,
				  unsigned int				index,
				  const bpt::string			&token) const;
    bool		CheckTextCase(const bpt::string			&str,
				      unsigned int			index,
				      const bpt::string			&token) const;
    bool		CheckTextCase(const bpt::string			&str,
				      unsigned int			index,
				      const bpt::string			*token,
				      unsigned int			len) const;

    bool		ReadChar(const bpt::string			&str,
				 unsigned int				&index,
				 const bpt::string			&token) const;
    bool		ReadCharCase(const bpt::string			&str,
				     unsigned int			&index,
				     const bpt::string			&token) const;

    bool		ReadText(const bpt::string			&str,
				 unsigned int				&index,
				 const bpt::string			&token) const;
    bool		ReadText(const bpt::string			&str,
				 unsigned int				&index,
				 const bpt::string			*token,
				 unsigned int				len) const;
    bool		ReadTextCase(const bpt::string			&str,
				     unsigned int			&index,
				     const bpt::string			&token) const;
    bool		ReadTextCase(const bpt::string			&str,
				     unsigned int			&index,
				     const bpt::string			*token,
				     unsigned int			len) const;
    bool		ReadTextCaseStop(const bpt::string		&str,
					 unsigned int			&index,
					 const bpt::string		&token,
					 const bpt::string		&stop) const;
    bool		ReadTextCaseStop(const bpt::string		&str,
					 unsigned int			&index,
					 const bpt::string		*token,
					 unsigned int			len,
					 const bpt::string		&stop) const;

    bool		ReadUntil(const bpt::string			&str,
				  unsigned int				&index,
				  const bpt::string			&token) const;
    bool		ReadUntilCase(const bpt::string			&str,
				      unsigned int			&index,
				      const bpt::string			&token) const;
    bool		ReadUntilIgnoreString(const bpt::string		&str,
					      unsigned int		&index,
					      const bpt::string		&token) const;
    bool		ReadUntilIgnoreStringCase(const bpt::string	&str,
						  unsigned int		&index,
						  const bpt::string	&token) const;
    bool		ReadUntilTextIgnoreString(const bpt::string	&str,
						  unsigned int		&index,
						  const bpt::string	&token) const;
    bool		ReadUntilTextIgnoreStringCase(const bpt::string&str,
						      unsigned int	&index,
						      const bpt::string&token) const;

    /// ReadSeparator just read plain whitespace
    /// ReadWhitespace read whitespace and ignore newline with previous '\\' character
    bool		ReadWhitespace(const bpt::string		&str,
				       unsigned int			&index) const;
    bool		ReadSeparator(const bpt::string			&str,
				      unsigned int			&index) const;

    /// Read typed litteral value
    int			ReadCharacter(const bpt::string			&str,
				      unsigned int			&index,
				      wchar_t				&out) const;	// Read 'c'
    bool		ReadInsideChar(const bpt::string		&str,
				       unsigned int			&index,
				       wchar_t				&out) const;	// Read what is inside '' in 'c'
    int			ReadString(const bpt::string			&str,
				   unsigned int				&index,
				   bpt::string				&out) const;	// Read "blob"
    bool		ReadInsideString(const bpt::string		&str,
					 unsigned int			&index,
					 bpt::string			&out) const;	// Read what is inside "" in "blob"

    /// Regenerate string
    bpt::string		BuildCharacter(wchar_t				c,
				       bool				in_string = false,
				       int				*len = NULL) const;	// char vers 'c'
    bpt::string		BuildString(const bpt::string			&str) const;	// str vers "blob\n"

    /// Language specific
    void		FindEndOfCommand(const bpt::string		&str,
					 unsigned int			&index) const;
    void		FindNextCommand(const bpt::string		&str,
					unsigned int			&index) const;

    int			ReadFieldName(const bpt::string			&str,
				      unsigned int			&index,
				      bpt::string			&out) const;
    int			ReadDabsicAddress(const bpt::string		&str,
					  unsigned int			&index,
					  bpt::string			&out) const;
    void		RemoveCommentaries(bpt::string			&str) const;

    void		Where(const bpt::string				&str,
			      unsigned int				index,
			      unsigned int				&line,
			      unsigned int				&col) const;

    ParsingTools(void) {}
    ~ParsingTools(void) {}
  };
}

#endif	//		__BPT_PARSINGTOOLS_HPP__

