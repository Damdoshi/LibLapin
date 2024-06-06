// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2018
//
// Lapin library

#include		<string.h>
#include		"lapin_private.h"

const std::string	Expression::OperatorToken[Expression::LAST_OPERATOR_FAMILY][64][8] =
  {
    { // ASSIGNATION

      // Révisions futures: l'assignation devrait probablement tout copier
      // plutot que seulement des morceaux...
      // Et il faudrait peut etre des fonctions pour extraires les parties des champs
      {"(=)", "(:=)"}, // N'assigne que la valeur
      {"=", ":="}, // Assigne tout
      {"{=}"},
      {"[=]"},
      {"||="},
      {"^^="},
      {"&&="},
      {"|="},
      {"^="},
      {"&="},
      {"!|="},
      {"!^="},
      {"!&="},
      {"<<="},
      {">>="},
      {"!<<="},
      {"!>>="},
      {"+="},
      {"{+=}"},
      {"[+=]"},
      {"-="},
      {"{-=}"},
      {"[-=]"},
      {"*="},
      {"/="},
      {"%="},
      {"!%="},
      {"**="},
      {"#="},
      {"u=", "union=", "∪="},
      {"{u=}", "{union=}", "{∪=}"},
      {"[u=]", "[union=]", "[∪=]"},
      {"n=", "inter=", "∩="},
      {"{n=}", "{inter=}", "{∩=}"},
      {"[n=]", "[inter=]", "[∩=]"},
      {"|<|="},
      {"|>|="},
      {"!|<|=", "!<|="},
      {"!|>|=", "!>|="},
    },
    { // TERNARY
      {"?", "alors"},
      {":", "sinon"}
    },
    { // LOW LOGIC
      {"||", "or", "ou"},
      {"^^", "xor", "oux"}
    },
    { // HIGH LOGIC
      {"&&", "and", "et"}
    },
    { // TEST
      {"(==)",	"(vaut)"},
      {"==",	"vaut"},
      {"(!=)",	"(<>)"},
      {"!=",	"<>"},
      {"<="},
      {">="},
      {"<"},
      {">"},
      {"~="}, // Opérateur seulement surchargeable
    },
    { // Test d'ensembles
      {"in", "∈", "dans"},
      {"{in}", "{∈}", "{dans}"},
      {"[in]", "[∈]", "[dans]"},
      {"out", "dehors", "∉", "!∈"},
      {"{out}", "{dehors}", "{∉}", "{!∈}"},
      {"[out]", "[dehors]", "[∉]", "[!∈]"},
    },
    { // LOW BINARY
      {"|"},
      {"^"},
      {"!|"}, // NOR
      {"!^"}, // NXOR
    },
    { // HIGH BINARY
      {"&"},
      {"!&"}, // NAND
    },
    { // SHIFT
      {"<<"},
      {">>"},
      {"!<<"}, // ROTATION
      {"!>>"}, // ROTATION
    },
    { // LOW MATH
      {"+"},
      {"{+}", "+#"},
      {"[+]"},
      {"-"},
      {"{-}", "-#"},
      {"[-]"},
    },
    { // HIGH MATH
      {"*"},
      {"/"},
      {"*#"}, // Produit matriciel
      {"/#"}, // Division matricielle
      {"%"},
      {"!%"}, // Ce qu'il manque pour avoir modulo 0
      {"%#"}, // Modulo matriciel
    },
    { // POW - (call pow(x, y)
      {"**"},
    },
    { // CAT
      {"#"}, // Concaténation de string
      {"|<|"}, // Ajout de l'élément de droite au début du tableau de gauche
      {"|>|"}, // Ajout de l'élément de droite à la fin du tableau de gauche
      {"!|<|", "!<|"}, // Retrait de n elements au début du tableau de gauche
      {"!|>|", "!<|"}, // Retrait de n elements à la fin du tableau de gauche
      {"u", "union", "∪"}, // Mélange de tableau et noeuds
      {"{u}", "{union}", "{∪}"}, // Mélange de tableau
      {"[u]", "[union]", "[∪]"}, // Mélange de noeuds
      {"n", "inter", "∩"}, // Intersection de tableau et noeuds
      {"{n}", "{inter}", "{∩}"}, // Intersection de tableau
      {"[n]", "[inter]", "[∩]"}, // Intersection de noeuds
      {"o", "∘"}, // Composition de fonction
    }
  };

