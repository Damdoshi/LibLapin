// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2020
//
// TMX Loader

#ifndef				__LAPIN_PRIVATE_TILEMAP_HPP__
# define			__LAPIN_PRIVATE_TILEMAP_HPP__

// Il faut trouver un moyen d'exploiter les fichiers TMX et DABSIC.
// Pour: la compatibilité avec Tiled
// Pour: la possibilité de scripter en Dabsic les événements du jeu
// Il faut un programme capable de:
// - Manger un TMX et un DABSIC pour sortir un DABSIC TILEMAP.
// - Manger un DABSIC TILEMAP pour sortir un TMX et un DABSIC.
// De cette facon, tout probleme sera reglé.

// Tilemap doit gérer l'utilisation de normal map
// Tilemap doit être un objet issu de t_bunny_clipable coté public
// Tilemap doit gérer le maximum d'éléments issu de Tiled.
// Tilemap, comme l'ancien t_bunny_tilemap, doit pouvoir gérer le fait de recevoir des sprites
// dessinés dessus et gérer leur positionnement avec intelligence
// Il faut, contrairement a avant, faire la distinction entre la carte et les cameras, de manière
// a pouvoir avoir plusieurs cameras sur la meme map.
// La camera peut etre positionné, zoomer et tourner.

// Un systeme de lumiere doit également être inclu.
// En somme, il s'agit de faire le moteur Depth en entier...

// Should use public side struct to contain or transfert its fields
class				Tilemap
{
public:

  bool				Load(t_bunny_configuration	*cnf);
  bool				Load(const std::string		&str);
  bool				Save(t_bunny_configuration	*cnf);
  bool				Save(const std::string		&str);
};

#endif	//			__LAPIN_PRIVATE_TILEMAP_HPP__
