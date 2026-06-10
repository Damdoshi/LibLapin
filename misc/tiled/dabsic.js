/*
** Jason Brillante "Damdoshi"
** Hanged Bunny Studio / LibLapin helper
**
** Tiled custom export format: LibLapin Dabsic tilemap
** Install this file in a Tiled extensions directory, then export maps as .dab.
*/

(function() {
  "use strict";

  var TMX_FLIPPED_HORIZONTALLY = 0x80000000;
  var TMX_FLIPPED_VERTICALLY = 0x40000000;
  var TMX_FLIPPED_ANTI_DIAGONALLY = 0x20000000;
  var TMX_ROTATED_HEXAGONAL_120 = 0x10000000;

  function asNumber(value, fallback) {
    var n = Number(value);

    return isFinite(n) ? n : fallback;
  }

  function asInteger(value, fallback) {
    return Math.floor(asNumber(value, fallback));
  }

  function dabsicString(value) {
    var text = value === undefined || value === null ? "" : String(value);
    var out = "\"";

    for (var i = 0; i < text.length; ++i) {
      var c = text.charAt(i);

      if (c === "\\")
        out += "\\\\";
      else if (c === "\"")
        out += "\\\"";
      else if (c === "\n")
        out += "\\n";
      else if (c === "\r")
        out += "\\r";
      else if (c === "\t")
        out += "\\t";
      else if (c === "\b")
        out += "\\b";
      else if (c === "\f")
        out += "\\f";
      else
        out += c;
    }

    return out + "\"";
  }

  function propertyValueAsString(value) {
    if (value === undefined || value === null)
      return "";
    if (typeof value === "boolean")
      return value ? "true" : "false";
    if (typeof value === "number")
      return String(value);
    if (typeof value === "string")
      return value;
    if (typeof value === "object") {
      if ("fileName" in value)
        return String(value.fileName);
      if ("id" in value)
        return String(value.id);
      if ("value" in value && "type" in value)
        return JSON.stringify(value.value);
    }
    return String(value);
  }

  function sortedProperties(object) {
    var entries = [];

    if (!object || typeof object.properties !== "function")
      return entries;

    var props = object.properties();

    for (var key in props) {
      if (Object.prototype.hasOwnProperty.call(props, key))
        entries.push({name: key, value: propertyValueAsString(props[key])});
    }
    entries.sort(function(a, b) { return a.name < b.name ? -1 : a.name > b.name ? 1 : 0; });
    return entries;
  }

  function writeProperties(out, object, indent) {
    var entries = sortedProperties(object);

    if (entries.length === 0)
      return;

    out.push(indent + "[Properties");
    for (var i = 0; i < entries.length; ++i)
      out.push(indent + "  " + entries[i].name + " = " + dabsicString(entries[i].value));
    out.push(indent + "]");
  }

  function writePropertiesInline(out, object, indent) {
    var entries = sortedProperties(object);

    for (var i = 0; i < entries.length; ++i)
      out.push(indent + entries[i].name + " = " + dabsicString(entries[i].value));
  }

  function writeVec2(out, indent, name, point, fallbackX, fallbackY) {
    var x = point && point.x !== undefined ? asNumber(point.x, fallbackX) : fallbackX;
    var y = point && point.y !== undefined ? asNumber(point.y, fallbackY) : fallbackY;

    out.push(indent + name + " = " + x + ", " + y);
  }

  function colorToRgba(color, opacity) {
    var text = color === undefined || color === null ? "#ffffff" : String(color);
    var r = 255;
    var g = 255;
    var b = 255;
    var a = 255;

    if (text.length === 9 && text.charAt(0) === "#") {
      a = parseInt(text.substr(1, 2), 16);
      r = parseInt(text.substr(3, 2), 16);
      g = parseInt(text.substr(5, 2), 16);
      b = parseInt(text.substr(7, 2), 16);
    } else if (text.length === 7 && text.charAt(0) === "#") {
      r = parseInt(text.substr(1, 2), 16);
      g = parseInt(text.substr(3, 2), 16);
      b = parseInt(text.substr(5, 2), 16);
    }

    if (isNaN(r) || isNaN(g) || isNaN(b) || isNaN(a)) {
      r = 255;
      g = 255;
      b = 255;
      a = 255;
    }

    if (opacity !== undefined && opacity !== null)
      a = Math.max(0, Math.min(255, Math.round(a * asNumber(opacity, 1))));

    return [r, g, b, a];
  }

  function writeColorMask(out, indent, color, opacity) {
    var rgba = colorToRgba(color, opacity);

    out.push(indent + "ColorMask = " + rgba[0] + ", " + rgba[1] + ", " + rgba[2] + ", " + rgba[3]);
  }

  function safeName(value, fallback) {
    var text = value === undefined || value === null ? "" : String(value);

    return text.length === 0 ? fallback : text;
  }

  function relativePath(fromFile, toFile) {
    if (!toFile)
      return "";
    if (typeof FileInfo !== "undefined" && FileInfo.path && FileInfo.relativePath) {
      var base = FileInfo.path(fromFile);
      return FileInfo.relativePath(base, toFile);
    }
    return String(toFile);
  }

  function exportedTileCount(tileset) {
    var count = asInteger(tileset.tileCount, 0);
    var next = asInteger(tileset.nextTileId, count);

    return Math.max(count, next, 0);
  }

  function collectLayersFrom(container, path, output) {
    var count = container.layerCount !== undefined ? container.layerCount :
      (container.layers ? container.layers.length : 0);

    for (var i = 0; i < count; ++i) {
      var layer = typeof container.layerAt === "function" ? container.layerAt(i) : container.layers[i];
      var fallback = "Layer" + i;
      var currentPath = path.length ? path + "/" + safeName(layer.name, fallback) : safeName(layer.name, fallback);

      if (layer.isGroupLayer) {
        output.groups.push({layer: layer, path: currentPath});
        collectLayersFrom(layer, currentPath, output);
      } else if (layer.isTileLayer) {
        output.tileLayers.push({layer: layer, path: currentPath});
      } else if (layer.isObjectLayer) {
        output.objectLayers.push({layer: layer, path: currentPath});
      } else if (layer.isImageLayer) {
        output.imageLayers.push({layer: layer, path: currentPath});
      }
    }
  }

  function collectLayers(map) {
    var output = {
      tileLayers: [],
      objectLayers: [],
      imageLayers: [],
      groups: []
    };

    collectLayersFrom(map, "", output);
    return output;
  }

  function tileSetsWithFirstGid(map) {
    var ret = [];
    var firstGid = 1;

    for (var i = 0; i < map.tilesets.length; ++i) {
      var tileset = map.tilesets[i];

      ret.push({tileset: tileset, firstGid: firstGid});
      firstGid += exportedTileCount(tileset);
    }
    return ret;
  }

  function firstGidForTile(tile, tilesets) {
    if (!tile)
      return 0;
    for (var i = 0; i < tilesets.length; ++i)
      if (tilesets[i].tileset === tile.tileset)
        return tilesets[i].firstGid;
    return 0;
  }

  function cellFlags(cell) {
    var flags = 0;

    if (!cell || cell.empty)
      return flags;
    if (cell.flippedHorizontally)
      flags += TMX_FLIPPED_HORIZONTALLY;
    if (cell.flippedVertically)
      flags += TMX_FLIPPED_VERTICALLY;
    if (cell.flippedAntiDiagonally)
      flags += TMX_FLIPPED_ANTI_DIAGONALLY;
    if (cell.rotatedHexagonal120)
      flags += TMX_ROTATED_HEXAGONAL_120;
    return flags;
  }

  function writeNumberArray(out, indent, name, values, width) {
    var w = Math.max(1, asInteger(width, values.length || 1));

    out.push(indent + "{" + name);
    for (var y = 0; y < values.length; y += w) {
      var row = [];
      var end = Math.min(y + w, values.length);

      for (var x = y; x < end; ++x)
        row.push(values[x]);
      out.push(indent + "  " + row.join(", ") + (end < values.length ? "," : ""));
    }
    out.push(indent + "}");
  }

  function writeCommonLayerFields(out, indent, layerInfo) {
    var layer = layerInfo.layer;

    out.push(indent + "Name = " + dabsicString(safeName(layer.name, layerInfo.path)));
    out.push(indent + "Id = " + asInteger(layer.id, 0));
    out.push(indent + "Path = " + dabsicString(layerInfo.path));
    if (layer.className)
      out.push(indent + "Class = " + dabsicString(layer.className));
    out.push(indent + "Visible = " + (layer.visible ? "true" : "false"));
    out.push(indent + "Locked = " + (layer.locked ? "true" : "false"));
    out.push(indent + "Opacity = " + asNumber(layer.opacity, 1));
    writeVec2(out, indent, "Offset", layer.offset, 0, 0);
    writeVec2(out, indent, "ParallaxFactor", layer.parallaxFactor, 1, 1);
    writeColorMask(out, indent, layer.tintColor, layer.opacity);
    writeProperties(out, layer, indent);
  }

  function cellAt(layer, x, y) {
    if (x < 0 || y < 0 || x >= asInteger(layer.width, 0) || y >= asInteger(layer.height, 0))
      return null;
    return layer.cellAt(x, y);
  }

  function writeTileLayers(out, layers, tilesets, map) {
    var mapWidth = asInteger(map.width, 0);
    var mapHeight = asInteger(map.height, 0);

    out.push("  {Layers");
    for (var i = 0; i < layers.length; ++i) {
      var info = layers[i];
      var layer = info.layer;
      var tiles = [];
      var flags = [];
      var hasFlags = false;

      out.push("    [");
      writeCommonLayerFields(out, "      ", info);
      out.push("      LayerSize = " + asInteger(layer.width, mapWidth) + ", " + asInteger(layer.height, mapHeight));

      for (var y = 0; y < mapHeight; ++y) {
        for (var x = 0; x < mapWidth; ++x) {
          var cell = cellAt(layer, x, y);
          var tile = cell && !cell.empty ? layer.tileAt(x, y) : null;
          var gid = tile ? firstGidForTile(tile, tilesets) + asInteger(tile.id, 0) : 0;
          var f = cellFlags(cell);

          if (f !== 0)
            hasFlags = true;
          tiles.push(gid);
          flags.push(f);
        }
      }

      writeNumberArray(out, "      ", "Tiles", tiles, mapWidth);
      if (hasFlags)
        writeNumberArray(out, "      ", "TileFlags", flags, mapWidth);
      out.push("    ]" + (i + 1 < layers.length ? "," : ""));
    }
    out.push("  }");
  }

  function writeTileProperties(out, tileset, indent) {
    var entries = [];

    for (var i = 0; i < tileset.tiles.length; ++i) {
      var tile = tileset.tiles[i];

      if (sortedProperties(tile).length !== 0 || tile.className)
        entries.push(tile);
    }
    if (entries.length === 0)
      return;

    out.push(indent + "{TileProperties");
    for (var j = 0; j < entries.length; ++j) {
      var t = entries[j];

      out.push(indent + "  [");
      out.push(indent + "    Id = " + asInteger(t.id, 0));
      if (t.className)
        out.push(indent + "    Class = " + dabsicString(t.className));
      writePropertiesInline(out, t, indent + "    ");
      out.push(indent + "  ]" + (j + 1 < entries.length ? "," : ""));
    }
    out.push(indent + "}");
  }

  function writeAnimation(out, tileset, tile, indent) {
    var frames = tile.frames;

    if (!frames || frames.length === 0)
      return false;
    if (asInteger(tile.id, 0) <= 0) {
      tiled.warn("LibLapin Dabsic export: animated tile local id 0 is skipped because the current Dabsic tilemap loader rejects LocalId <= 0.");
      return false;
    }

    out.push(indent + "[");
    out.push(indent + "  LocalId = " + asInteger(tile.id, 0));
    out.push(indent + "  InitialAnimation = " + dabsicString("A0"));
    out.push(indent + "  Frequency = 1000");
    out.push(indent + "  [Clip");
    out.push(indent + "    Size = " + asInteger(tileset.tileWidth, 0) + ", " + asInteger(tileset.tileHeight, 0));
    out.push(indent + "    Selected = 0");
    out.push(indent + "  ]");
    out.push(indent + "  [Animations");
    for (var i = 0; i < frames.length; ++i) {
      var frame = frames[i];
      var next = i + 1 < frames.length ? "A" + (i + 1) : "A0";
      var columnCount = asInteger(tileset.columnCount, 0);
      var col = columnCount > 0 ? columnCount : Math.max(1, Math.floor(asInteger(tileset.imageWidth, 0) / Math.max(1, asInteger(tileset.tileWidth, 1))));
      var x = (asInteger(frame.tileId, 0) % col) * (asInteger(tileset.tileWidth, 0) + asInteger(tileset.tileSpacing, 0)) + asInteger(tileset.margin, 0);
      var y = Math.floor(asInteger(frame.tileId, 0) / col) * (asInteger(tileset.tileHeight, 0) + asInteger(tileset.tileSpacing, 0)) + asInteger(tileset.margin, 0);

      out.push(indent + "    [A" + i);
      out.push(indent + "      Frame = 1");
      out.push(indent + "      Position = " + x + ", " + y);
      out.push(indent + "      NextAnimation = " + dabsicString(next));
      out.push(indent + "      {FramePlay");
      out.push(indent + "        " + asInteger(frame.duration, 0));
      out.push(indent + "      }");
      out.push(indent + "    ]");
    }
    out.push(indent + "  ]");
    out.push(indent + "]");
    return true;
  }

  function writeAnimatedTiles(out, tileset, indent) {
    var emitted = 0;
    var start = out.length;

    out.push(indent + "{AnimatedTiles");
    for (var i = 0; i < tileset.tiles.length; ++i) {
      if (tileset.tiles[i].animated) {
        if (emitted > 0)
          out[out.length - 1] += ",";
        if (writeAnimation(out, tileset, tileset.tiles[i], indent + "  "))
          ++emitted;
      }
    }
    if (emitted === 0) {
      out.splice(start, out.length - start);
      return;
    }
    out.push(indent + "}");
  }

  function writeTilesets(out, map, fileName, tilesets) {
    out.push("  {Tilesets");
    for (var i = 0; i < tilesets.length; ++i) {
      var entry = tilesets[i];
      var tileset = entry.tileset;
      var image = tileset.imageFileName || tileset.image || "";
      var rel = relativePath(fileName, image);
      var count = exportedTileCount(tileset);

      if (!image)
        tiled.warn("LibLapin Dabsic export: tileset " + safeName(tileset.name, "Tileset" + i) + " has no image; current LibLapin tilemaps expect image-based tilesets.");

      out.push("    [");
      out.push("      Name = " + dabsicString(safeName(tileset.name, "Tileset" + i)));
      if (tileset.className)
        out.push("      Class = " + dabsicString(tileset.className));
      out.push("      RessourceFile = " + dabsicString(rel));
      out.push("      TileSize = " + asInteger(tileset.tileWidth, 0) + ", " + asInteger(tileset.tileHeight, 0));
      out.push("      Margin = " + asInteger(tileset.margin, 0) + ", " + asInteger(tileset.margin, 0));
      out.push("      Position = " + asInteger(tileset.margin, 0) + ", " + asInteger(tileset.margin, 0));
      out.push("      Intertile = " + asInteger(tileset.tileSpacing, 0) + ", " + asInteger(tileset.tileSpacing, 0));
      out.push("      FirstTileId = " + entry.firstGid);
      out.push("      TileCount = " + count);
      out.push("      Columns = " + asInteger(tileset.columnCount, 0));
      out.push("      ImageSize = " + asInteger(tileset.imageWidth, 0) + ", " + asInteger(tileset.imageHeight, 0));
      if (tileset.tileOffset)
        writeVec2(out, "      ", "TileOffset", tileset.tileOffset, 0, 0);
      writeProperties(out, tileset, "      ");
      writeTileProperties(out, tileset, "      ");
      writeAnimatedTiles(out, tileset, "      ");
      out.push("    ]" + (i + 1 < tilesets.length ? "," : ""));
    }
    out.push("  }");
  }

  function shapeName(shape) {
    if (typeof MapObject !== "undefined") {
      if (shape === MapObject.Rectangle)
        return "Rectangle";
      if (shape === MapObject.Polygon)
        return "Polygon";
      if (shape === MapObject.Polyline)
        return "Polyline";
      if (shape === MapObject.Ellipse)
        return "Ellipse";
      if (shape === MapObject.Point)
        return "Point";
      if (shape === MapObject.Text)
        return "Text";
    }
    return String(shape);
  }

  function writePointArray(out, indent, name, points) {
    if (!points || points.length === 0)
      return;
    out.push(indent + "{" + name);
    for (var i = 0; i < points.length; ++i)
      out.push(indent + "  " + asNumber(points[i].x, 0) + ", " + asNumber(points[i].y, 0) + (i + 1 < points.length ? "," : ""));
    out.push(indent + "}");
  }

  function writeObjectLayers(out, objectLayers, tilesets) {
    if (objectLayers.length === 0)
      return;

    out.push("  {ObjectLayers");
    for (var i = 0; i < objectLayers.length; ++i) {
      var info = objectLayers[i];
      var layer = info.layer;
      var objects = layer.objects || [];

      out.push("    [");
      writeCommonLayerFields(out, "      ", info);
      out.push("      ObjectCount = " + asInteger(layer.objectCount !== undefined ? layer.objectCount : objects.length, objects.length));
      out.push("      {Objects");
      for (var j = 0; j < objects.length; ++j) {
        var obj = objects[j];
        var tile = obj.tile;
        var gid = tile ? firstGidForTile(tile, tilesets) + asInteger(tile.id, 0) : 0;

        out.push("        [");
        out.push("          Id = " + asInteger(obj.id, 0));
        out.push("          Name = " + dabsicString(safeName(obj.name, "Object" + asInteger(obj.id, j))));
        if (obj.className)
          out.push("          Class = " + dabsicString(obj.className));
        out.push("          Shape = " + dabsicString(shapeName(obj.shape)));
        out.push("          Position = " + asNumber(obj.x, 0) + ", " + asNumber(obj.y, 0));
        out.push("          Size = " + asNumber(obj.width, 0) + ", " + asNumber(obj.height, 0));
        out.push("          Rotation = " + asNumber(obj.rotation, 0));
        out.push("          Visible = " + (obj.visible ? "true" : "false"));
        if (gid !== 0) {
          out.push("          Tile = " + gid);
          out.push("          TileFlippedHorizontally = " + (obj.tileFlippedHorizontally ? "true" : "false"));
          out.push("          TileFlippedVertically = " + (obj.tileFlippedVertically ? "true" : "false"));
        }
        if (obj.text)
          out.push("          Text = " + dabsicString(obj.text));
        writePointArray(out, "          ", "Polygon", obj.polygon);
        writeProperties(out, obj, "          ");
        out.push("        ]" + (j + 1 < objects.length ? "," : ""));
      }
      out.push("      }");
      out.push("    ]" + (i + 1 < objectLayers.length ? "," : ""));
    }
    out.push("  }");
  }

  function writeImageLayers(out, imageLayers, fileName) {
    if (imageLayers.length === 0)
      return;

    out.push("  {ImageLayers");
    for (var i = 0; i < imageLayers.length; ++i) {
      var info = imageLayers[i];
      var layer = info.layer;
      var image = layer.imageFileName || "";

      out.push("    [");
      writeCommonLayerFields(out, "      ", info);
      out.push("      RessourceFile = " + dabsicString(relativePath(fileName, image)));
      out.push("      Repeat = " + (layer.repeatX ? "true" : "false") + ", " + (layer.repeatY ? "true" : "false"));
      out.push("    ]" + (i + 1 < imageLayers.length ? "," : ""));
    }
    out.push("  }");
  }

  function writeGroups(out, groups) {
    if (groups.length === 0)
      return;

    out.push("  {Groups");
    for (var i = 0; i < groups.length; ++i) {
      out.push("    [");
      writeCommonLayerFields(out, "      ", groups[i]);
      out.push("    ]" + (i + 1 < groups.length ? "," : ""));
    }
    out.push("  }");
  }

  function orientationName(map) {
    if (typeof TileMap !== "undefined") {
      if (map.orientation === TileMap.Orthogonal)
        return "Orthogonal";
      if (map.orientation === TileMap.Isometric)
        return "Isometric";
      if (map.orientation === TileMap.Staggered)
        return "Staggered";
      if (map.orientation === TileMap.Hexagonal)
        return "Hexagonal";
    }
    return String(map.orientation);
  }

  function renderOrderName(map) {
    if (typeof TileMap !== "undefined") {
      if (map.renderOrder === TileMap.RightDown)
        return "RightDown";
      if (map.renderOrder === TileMap.RightUp)
        return "RightUp";
      if (map.renderOrder === TileMap.LeftDown)
        return "LeftDown";
      if (map.renderOrder === TileMap.LeftUp)
        return "LeftUp";
    }
    return String(map.renderOrder);
  }

  function writeMap(map, fileName) {
    var layers = collectLayers(map);
    var tilesets = tileSetsWithFirstGid(map);
    var pixelWidth = asInteger(map.width, 0) * asInteger(map.tileWidth, 0);
    var pixelHeight = asInteger(map.height, 0) * asInteger(map.tileHeight, 0);
    var out = [];

    if (typeof TileMap !== "undefined" && map.orientation !== TileMap.Orthogonal)
      tiled.warn("LibLapin Dabsic export: non-orthogonal maps are exported but the current tilemap loader is mainly orthogonal.");
    if (map.infinite)
      tiled.warn("LibLapin Dabsic export: infinite maps are flattened to the fixed exported rectangle only.");
    if (tilesets.length > 1)
      tiled.warn("LibLapin Dabsic export: several tilesets are exported, but the current Dabsic loader should be checked with several FirstTileId ranges.");

    out.push("' Generated by Tiled LibLapin/Dabsic exporter.");
    out.push("Size = " + pixelWidth + ", " + pixelHeight);
    out.push("Position = 0, 0");
    out.push("Scale = 1, 1");
    out.push("Origin = 0, 0");
    out.push("Rotation = 0");
    out.push("ColorMask = 255, 255, 255, 255");
    out.push("");
    out.push("[Tilemap");
    out.push("  LayerClip = 0, " + Math.max(0, layers.tileLayers.length - 1));
    out.push("  Camera = " + Math.floor(pixelWidth / 2) + ", " + Math.floor(pixelHeight / 2));
    out.push("  Zoom = 1, 1");
    out.push("  Rotation = 0");
    out.push("  LockBorders = false");
    out.push("  Loop = false, false");
    out.push("");
    out.push("  MapSize = " + asInteger(map.width, 0) + ", " + asInteger(map.height, 0));
    out.push("  TileSize = " + asInteger(map.tileWidth, 0) + ", " + asInteger(map.tileHeight, 0));
    out.push("  Orientation = " + dabsicString(orientationName(map)));
    out.push("  RenderOrder = " + dabsicString(renderOrderName(map)));
    out.push("  Infinite = " + (map.infinite ? "true" : "false"));
    out.push("  NextLayerId = " + asInteger(map.nextLayerId, 0));
    out.push("  NextObjectId = " + asInteger(map.nextObjectId, 0));
    out.push("");
    writeProperties(out, map, "  ");
    if (layers.tileLayers.length > 0) {
      writeTileLayers(out, layers.tileLayers, tilesets, map);
      out.push("");
    } else {
      out.push("  {Layers");
      out.push("  }");
      out.push("");
    }
    writeTilesets(out, map, fileName, tilesets);
    if (layers.objectLayers.length > 0) {
      out.push("");
      writeObjectLayers(out, layers.objectLayers, tilesets);
    }
    if (layers.imageLayers.length > 0) {
      out.push("");
      writeImageLayers(out, layers.imageLayers, fileName);
    }
    if (layers.groups.length > 0) {
      out.push("");
      writeGroups(out, layers.groups);
    }
    out.push("]");
    out.push("");

    var file = new TextFile(fileName, TextFile.WriteOnly);
    file.codec = "UTF-8";
    file.write(out.join("\n"));
    file.commit();
  }

  tiled.registerMapFormat("dabsic", {
    name: "LibLapin Dabsic tilemap",
    extension: "dab",
    write: writeMap
  });
})();
