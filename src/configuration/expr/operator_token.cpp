// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2018
//
// Lapin library

#include		<string.h>
#include		"lapin_private.h"

const std::string	Expression::OperatorToken[Expression::LAST_OPERATOR_FAMILY][21][8] =
  {
    { // ASSIGNATION

      // Révisions futures: l'assignation devrait probablement tout copier
      // plutot que seulement des morceaux...
      // Et il faudrait peut etre des fonctions pour extraires les parties des champs
      {"=", "<-", ":="}, // Devrait tout copier
      {"[=]", "[<-]", "[:=]"}, // (=) pourrait etre un symbole pour prendre que la valeur (voir si gramamticalement, c'est jouable)
      {"[Array=]", "[Array<-]", "[Array:=]"}, // {=} serait judicieux, ne copie que les tableaux
      {"[Map=]", "[Map<-]", "[Map:=]"}, // [=] serait judicieux, ne copie que les tables
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
      {"#="},
      {"[]="}
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
      {"#"},
    },
    { // Test d'ensembles
      {"in", "∈"},
      {"out", "∉", "!∈"}
    }
  };

