// Jason Brillante "Damdoshi"
// Lisa Monpierre "Leeza"
// Pentacle Technologie 2009-2014
//
// DABSIC
// Developer's All-purpose Block Structured Instruction Code

#include		"ParsingTools.hpp"

const bpt::string	bpt::ParsingTools::FieldNameFirstChar =
  "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ_"
  ;

const bpt::string	bpt::ParsingTools::FieldName =
  "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789_"
  ;

const bpt::string	bpt::ParsingTools::Teal =
  "\033[1;36m"
 ;

const bpt::string	bpt::ParsingTools::Blue =
  "\033[1;34m"
  ;

const bpt::string	bpt::ParsingTools::Red =
  "\033[1;31m"
  ;

const bpt::string	bpt::ParsingTools::Green =
  "\033[1;32m"
  ;

const bpt::string	bpt::ParsingTools::Purple =
  "\033[0;35m"
  ;

const bpt::string	bpt::ParsingTools::Pink =
  "\033[1;35m"
  ;

const bpt::string	bpt::ParsingTools::Yellow =
  "\033[1;33m"
  ;

const bpt::string	bpt::ParsingTools::Grey =
  "\033[1;30m"
  ;

const bpt::string	bpt::ParsingTools::BlackOnWhite =
  "\033[0;30;47m"
  ;

const bpt::string	bpt::ParsingTools::White =
  "\033[00m"
  ;

const bpt::string	bpt::ParsingTools::OpenSection = "[";

const bpt::string	bpt::ParsingTools::CloseSection = "]";

const bpt::string	bpt::ParsingTools::Address = ":";

const bpt::string	bpt::ParsingTools::Pointer = "*";

const bpt::string	bpt::ParsingTools::PointerPrefix = "#";

const bpt::string	bpt::ParsingTools::DescriptorPrefix = "$";

const bpt::string	bpt::ParsingTools::TypePrefix = "?";

const bpt::string	bpt::ParsingTools::NullPtr = "NULL";

const bpt::string	bpt::ParsingTools::NullAddr[2] = 
  {
    "Nowhere",
    "Nullepart"
  };

const bpt::string	bpt::ParsingTools::Nothing[3] =
  {
    "Nothing",
    "Rien",
    "Vide"
  };

const bpt::string	bpt::ParsingTools::Assignation[4] =
  {
    "=",
    ":=",
    "<=",
    "<-"
  };

const bpt::string	bpt::ParsingTools::Include[2] =
  {
    "Include",
    "Inclure"
  };
const bpt::string	bpt::ParsingTools::IncludeCipher[2] =
  {
    "Includec",
    "Inclurec"
  };
const bpt::string	bpt::ParsingTools::Message[1] =
  {
    "Message"
  };
const bpt::string	bpt::ParsingTools::Warning[2] =
  {
    "Warning",
    "Attention"
  };
const bpt::string	bpt::ParsingTools::ErrorD[2] =
  {
    "Error",
    "Erreur"
  };

const bpt::string	bpt::ParsingTools::Extern[1] =
  {
    "extern"
  };

const bpt::string	bpt::ParsingTools::Local[1] =
  {
    "local"
  };

const bpt::string	bpt::ParsingTools::Private[2] =
  {
    "private",
    "privé"
  };

const bpt::string	bpt::ParsingTools::Protected[2] =
  {
    "protected",
    "protégé"
  };

const bpt::string	bpt::ParsingTools::Locked[2] =
  {
    "locked",
    "verrouillé"
  };

const bpt::string	bpt::ParsingTools::Public[2] =
  {
    "public",
    "publique"
  };

const bpt::string	bpt::ParsingTools::Limited[2] =
  {
    "limited",
    "limité"
  };

const bpt::string	bpt::ParsingTools::Strict[1] =
  {
    "strict"
  };

const bpt::string	bpt::ParsingTools::Restricted[2] =
  {
    "restricted",
    "restreint"
  };

const bpt::string	bpt::ParsingTools::Const[2] =
  {
    "const",
    "solid"
  };

const bpt::string	bpt::ParsingTools::HexaPrefix = "0x";
const bpt::string	bpt::ParsingTools::Hexadecimal = "0123456789abcdef";

const bpt::string	bpt::ParsingTools::DecimalPrefix = "";
const bpt::string	bpt::ParsingTools::Decimal = "0123456789";

const bpt::string	bpt::ParsingTools::OctalPrefix = "0";
const bpt::string	bpt::ParsingTools::Octal = "01234567";

const bpt::string	bpt::ParsingTools::BinPrefix = "0b";
const bpt::string	bpt::ParsingTools::Binary = "01";

const bpt::string	bpt::ParsingTools::DabsicRoot = "[]";
const bpt::string	bpt::ParsingTools::CurrentNode = "{}";
const bpt::string	bpt::ParsingTools::GetAddress = "&";

const bpt::string	bpt::ParsingTools::Variant[3] =
  {
    "variant",
    "void",
    "variable"
  };

const bpt::string	bpt::ParsingTools::Boolean[3] =
  {
    "boolean",
    "booléen",
    "bool"
  };

const bpt::string	bpt::ParsingTools::Integer[3] =
  {
    "integer",
    "int",
    "entier"
  };

const bpt::string	bpt::ParsingTools::Real[3] =
  {
    "double",
    "real",
    "réel"
  };

const bpt::string	bpt::ParsingTools::Character[3] =
  {
    "character",
    "char",
    "charactère"
  };

const bpt::string	bpt::ParsingTools::String[2] =
  {
    "string",
    "chaine"
  };

const bpt::string	bpt::ParsingTools::Descriptor[2] =
  {
    "descriptor",
    "index"
  };

const bpt::string	bpt::ParsingTools::Type[1] =
  {
    "type"
  };

const bpt::string	bpt::ParsingTools::Record[4] =
  {
    "record",
    "structure",
    "struct",
    "enregistrement"
  };

const bpt::string	bpt::ParsingTools::True[4] =
  {
    "True",
    "Yes",
    "Vrai",
    "Oui"
  };

const bpt::string	bpt::ParsingTools::False[4] =
  {
    "False",
    "Non",
    "Faux",
    "No"
  };

const bpt::string	bpt::ParsingTools::PreviousNode = "_";
const bpt::string	bpt::ParsingTools::DirectAccess = ".";
const bpt::string	bpt::ParsingTools::AddressAccess = "->";

const bpt::string	bpt::ParsingTools::RealComma = ".";
const bpt::string	bpt::ParsingTools::CharacterDelimiter = "'";
const bpt::string	bpt::ParsingTools::StringDelimiter = "\"";

const bpt::string	bpt::ParsingTools::OpenScript = "[Script";
const bpt::string	bpt::ParsingTools::OpenSequence = "[Sequence";
const bpt::string	bpt::ParsingTools::OpenData = "[Collection";
const bpt::string	bpt::ParsingTools::OpenXML = "[XML";
const bpt::string	bpt::ParsingTools::CloseScope = "]";

const bpt::string	bpt::ParsingTools::Field[2] = {
  "Field",
  "Champ"
};
const bpt::string	bpt::ParsingTools::Collection[1] = {
  "Collection"
};
const bpt::string	bpt::ParsingTools::Script[1] = {
  "Script"
};
const bpt::string	bpt::ParsingTools::Sequence[1] = {
  "Sequence"
};
const bpt::string	bpt::ParsingTools::XMLType[1] = {
  "XML"
};

const bpt::string	bpt::ParsingTools::OpenPriority = "(";
const bpt::string	bpt::ParsingTools::ClosePriority = ")";
const bpt::string	bpt::ParsingTools::DataLength[4] =
  {
    "Byte",
    "Short",
    "Word",
    "Long"
  };

const bpt::string	bpt::ParsingTools::Separator = ",";
