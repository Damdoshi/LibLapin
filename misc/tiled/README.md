# Tiled -> LibLapin Dabsic exporter

This directory contains a Tiled JavaScript extension registering a `dabsic` map
format. It exports `.tmx`/Tiled maps to LibLapin-style `.dab` tilemap files.

## Installation

Copy `dabsic.js` to one of Tiled's extension directories:

- a project extension directory, usually `extensions/` next to the
  `.tiled-project` file;
- or the global scripted extensions directory opened from Tiled preferences.

Tiled loads JavaScript extensions automatically. After loading the script, use
`File -> Export As...` and choose `LibLapin Dabsic tilemap (*.dab)`.

The short format name is `dabsic`, so command-line export can use:

```sh
tiled --export-map dabsic map.tmx map.dab
```

## Exported schema

The exporter follows the current LibLapin Dabsic tilemap loader where possible:

- top-level clipable fields: `Size`, `Position`, `Scale`, `Origin`, `Rotation`,
  `ColorMask`;
- `[Tilemap]` fields: `LayerClip`, `Camera`, `Zoom`, `Rotation`, `LockBorders`,
  `Loop`, `MapSize`, `TileSize`;
- `{Layers}` with one flattened entry per Tiled tile layer and a plain integer
  `{Tiles}` array, never Base64;
- `{Tilesets}` with `RessourceFile`, `TileSize`, `Margin`, `Position`,
  `Intertile`, `FirstTileId`, `TileCount`, `Name`;
- `{AnimatedTiles}` generated from Tiled tile animations as LibLapin sprite
  animations;
- `Properties` nodes for map, layer, tileset, tile and object custom
  properties. Property values are stringified because the current tilemap loader
  stores them in a string map.

The exporter also preserves Tiled data not currently consumed by the LibLapin
loader, using PascalCase fields: layer IDs, paths, offsets, parallax factors,
object layers, image layers and groups.

Tile flipping/rotation is exported separately in `{TileFlags}` when used. The
plain `{Tiles}` array keeps current LibLapin compatibility by storing bare GIDs.
`TileFlags` uses Tiled/TMX unsigned flag bits for future renderer support.

## Current limitations

- Image-collection tilesets are not a good target for the current LibLapin
  tilemap loader. Image-based tilesets are expected.
- Infinite maps are exported only over the fixed `map.width` x `map.height`
  rectangle seen through the scripting API.
- Non-orthogonal maps are exported with metadata, but the current LibLapin
  tilemap rendering path is mainly orthogonal.
- Animated tiles whose local id is `0` are skipped for now because the current
  Dabsic tilemap loader rejects `LocalId <= 0`.
- Several tilesets are exported, but the current Dabsic loader should be tested
  or adjusted for several `FirstTileId` ranges.
