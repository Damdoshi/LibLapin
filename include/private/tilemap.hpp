/*
** Jason Brillante "Damdoshi"
** Hanged Bunny Studio 2014-2016
**
**
** Bibliotheque Lapin
*/

#ifndef				__LAPIN_PRIVATE_TILEMAP_HPP__
# define			__LAPIN_PRIVATE_TILEMAP_HPP__

struct				TileMap
{
public:
  struct			Animation
  {
    double			delay;
  };
  struct			Tile
  {
    std::map<int, Animation>	animations;
  }

  struct			Tileset
  {

  };

  std::vector<Tileset>		tilesets;
  std::map<uint64_t, SmallConf*>terrains;
};

#endif	/*			__LAPIN_PRIVATE_TILEMAP_HPP__	*/
