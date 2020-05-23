// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2020
//
// Depth Engine
// Originaly designed for Allan & Macroboy Y

#ifndef			LAPIN_PRIVATE_DEPTH_HPP
# define		LAPIN_PRIVATE_DEPTH_HPP

// Depth can load TMX files from Tiled and also have its own format based on Dabsic.
// Depth come with two contextes: one to play, one to edit.
// All depth-built engines will have easily a built-in editor.
// Rendering can be configured:
// - The full map can be rendered into a single sfml picture so no tile blit is
//   achieved after, whith an exception for animated tiles. This method cannot have
//   maps greater than a graphic card cluster.
// - The rendering can be done in the camera view only, so really great maps can be
//   achieved.
//
// - Depth supports background parralax (For Macroboy Y) thanks to bunny_parralax
// - Depth supports normal maps (For Allan and Macroboy Y)
// - Depth supports raytraced shadows (For Allan)
// - Depth supports extruded 3D (For Allan)
// - Depth brings liquid simulation handling (For Allan)
// - Depth support any operation t_bunny_tilemap would support, as it is supposed to replace it
//
// - Event support and scripting language bind with Dabsic: TMX format does not
//   allow to use Dabsic inside it *but* Dabsic can be loaded asided and referenced
//   by it.
// - Support use of HistoricObject.

namespace		bunny
{
  class			Depth
  {
    
  };
}

#endif	//		LAPIN_PRIVATE_DEPTH_HPP
