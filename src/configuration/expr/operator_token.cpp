// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2018
//
// Lapin library

#include		<string.h>
#include		"lapin_private.h"

const std::string	Expression::OperatorToken[Expression::LAST_OPERATOR_FAMILY][21][8] =
  {
    { // ASSIGNATION
      {"=", "<-", ":="},
      {"[=]", "[<-]", "[:=]"},
      {"[Array=]", "[Array<-]", "[Array:=]"},
      {"[Hash=]", "[Hash<-]", "[Hash:=]"},
      {"||="},
      {"^^="},
      {"&&="},
      {"|="},
      {"^="},
      {"&="},
      {"<<="},
      {">>="},
      {"+="},
      {"-="},
      {"*="},
      {"/="},
      {"%="},
      {"**="},
      {"#="}
    },
    { // TERNARY
      {"?"},
      {":"}
    },
    { // LOW LOGIC
      {"||", "or", "ou"},
      {"^^", "xor", "oux"}
    },
    { // HIGH LOGIC
      {"&&", "and", "et"}
    },
    { // TEST
      {"==",   "is",    ".eq.", "-eq"},
      {"[==]", "[is]"},
      {"!=",   "<>",    ".ne.", "-ne"},
      {"[!=]", "[<>]"},
      {"<=",   ".le.",  "-le"},
      {">=",   ".ge.",  "-ge"},
      {"<",    ".lt.",  "-lt"},
      {">",    ".gt.",  "-gt"}
    },
    { // LOW BINARY
      {"|"},
      {"^"}
    },
    { // HIGH BINARY
      {"&"}
    },
    { // SHIFT
      {"<<"},
      {">>"},
      //
    },
    { // LOW MATH
      {"+"},
      {"-"}
    },
    { // HIGH MATH
      {"*"},
      {"/"},
      {"%"},
    },
    { // POW
      {"**"},
    },
    { // CAT
      {"#"}
    }
  };

