// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2026
//
// Bibliotheque Lapin

#include			<vector>
#include			<string>
#include			<algorithm>
#include			<cctype>
#include			<cstdint>
#include			<limits>
#include			"lapin_private.h"

namespace
{
  static const uint8_t		default_shift[4] =
    {
     [RED_CMP] = RED_CMP,
     [GREEN_CMP] = GREEN_CMP,
     [BLUE_CMP] = BLUE_CMP,
     [ALPHA_CMP] = ALPHA_CMP
    };

  struct			Reader
  {
    const uint8_t		*data;
    size_t			size;
    size_t			pos;
    bool			ok;

    Reader(const void		*buffer,
	   size_t		len)
      : data(reinterpret_cast<const uint8_t*>(buffer)),
	size(len),
	pos(0),
	ok(true)
    {}

    bool			canRead(size_t n) const
    {
      return (ok && pos <= size && n <= size - pos);
    }

    const uint8_t		*readBytes(size_t n)
    {
      const uint8_t		*ret;

      if (!canRead(n))
	{
	  ok = false;
	  return (NULL);
	}
      ret = &data[pos];
      pos += n;
      return (ret);
    }

    bool			skip(size_t n)
    {
      if (!canRead(n))
	{
	  ok = false;
	  return (false);
	}
      pos += n;
      return (true);
    }

    uint8_t			readU8(void)
    {
      const uint8_t		*ptr = readBytes(1);

      return (ptr ? ptr[0] : 0);
    }

    uint16_t			readU16(void)
    {
      const uint8_t		*ptr = readBytes(2);

      if (!ptr)
	return (0);
      return ((uint16_t(ptr[0]) << 8) | uint16_t(ptr[1]));
    }

    int16_t			readS16(void)
    {
      return ((int16_t)readU16());
    }

    uint32_t			readU32(void)
    {
      const uint8_t		*ptr = readBytes(4);

      if (!ptr)
	return (0);
      return ((uint32_t(ptr[0]) << 24) |
	      (uint32_t(ptr[1]) << 16) |
	      (uint32_t(ptr[2]) << 8) |
	      uint32_t(ptr[3]));
    }

    int32_t			readS32(void)
    {
      return ((int32_t)readU32());
    }

    std::string			readTag(void)
    {
      const uint8_t		*ptr = readBytes(4);

      if (!ptr)
	return (std::string());
      return (std::string(reinterpret_cast<const char*>(ptr), 4));
    }
  };

  struct			LayerChannel
  {
    int16_t			id;
    uint32_t		length;
    std::vector<uint8_t>	data;
  };

  struct			PsdLayer
  {
    int32_t			top;
    int32_t			left;
    int32_t			bottom;
    int32_t			right;
    uint8_t			opacity;
    uint8_t			flags;
    uint8_t			clipping;
    int				section_type;
    std::string		name;
    std::string		blend_key;
    int				parent;
    std::vector<LayerChannel>	channels;

    int				width(void) const
    {
      return (std::max(0, right - left));
    }

    int				height(void) const
    {
      return (std::max(0, bottom - top));
    }

    bool				visible(void) const
    {
      return ((flags & 0x02) == 0);
    }

    bool				isFolder(void) const
    {
      return (section_type == 1 || section_type == 2);
    }

    bool				isGroupEnd(void) const
    {
      return (section_type == 3);
    }
  };

  struct			DecodedPsd
  {
    uint32_t			width;
    uint32_t			height;
    uint16_t			depth;
    uint16_t			color_mode;
    std::vector<PsdLayer>	layers;
    std::vector<uint8_t>	color;
    std::vector<uint8_t>	normal;
    bool				has_color;
    bool				has_normal;

    DecodedPsd(void)
      : width(0), height(0), depth(0), color_mode(0), has_color(false), has_normal(false)
    {}
  };

  static std::string	ascii_lower(const std::string& str)
  {
    std::string		ret(str);

    for (size_t i = 0; i < ret.size(); ++i)
      ret[i] = (char)std::tolower((unsigned char)ret[i]);
    return (ret);
  }

  static bool		has_psd_extension(const char	*file)
  {
    std::string		lower;

    if (file == NULL)
      return (false);
    lower = ascii_lower(file);
    return (lower.size() >= 4 && lower.substr(lower.size() - 4) == ".psd");
  }

  static std::string	read_pascal_string_4(Reader& rd,
					     size_t	limit)
  {
    size_t			start = rd.pos;
    uint8_t		len;
    std::string		ret;

    if (start >= limit || !rd.canRead(1))
      {
	rd.ok = false;
	return (ret);
      }
    len = rd.readU8();
    if (!rd.ok)
      return (ret);
    if (rd.pos + len > limit)
      {
	rd.ok = false;
	return (ret);
      }
    ret.assign(reinterpret_cast<const char*>(rd.readBytes(len)), len);
    if (!rd.ok)
      return (std::string());
    while ((rd.pos - start) % 4 != 0)
      if (!rd.skip(1))
	return (std::string());
    return (ret);
  }

  static std::string	read_unicode_name(const uint8_t	*ptr,
					  size_t	len)
  {
    std::string		ret;
    size_t			off = 0;
    uint32_t		count;

    if (len < 4)
      return (ret);
    count = (uint32_t(ptr[0]) << 24) |
      (uint32_t(ptr[1]) << 16) |
      (uint32_t(ptr[2]) << 8) |
      uint32_t(ptr[3]);
    off = 4;
    for (uint32_t i = 0; i < count && off + 1 < len; ++i, off += 2)
      {
	uint16_t		cp = (uint16_t(ptr[off]) << 8) | uint16_t(ptr[off + 1]);

	if (cp < 0x80)
	  ret.push_back((char)cp);
	else if (cp < 0x800)
	  {
	    ret.push_back((char)(0xC0 | (cp >> 6)));
	    ret.push_back((char)(0x80 | (cp & 0x3F)));
	  }
	else if (cp >= 0xD800 && cp <= 0xDFFF)
	  ret.push_back('?');
	else
	  {
	    ret.push_back((char)(0xE0 | (cp >> 12)));
	    ret.push_back((char)(0x80 | ((cp >> 6) & 0x3F)));
	    ret.push_back((char)(0x80 | (cp & 0x3F)));
	  }
      }
    return (ret);
  }

  static bool		decode_packbits_row(const uint8_t	*&src,
					    const uint8_t	*row_end,
					    uint8_t	*dst,
					    size_t		width)
  {
    size_t			written = 0;

    while (src < row_end && written < width)
      {
	int8_t			code = (int8_t)*src++;

	if (code >= 0)
	  {
	    size_t		read_count = (size_t)code + 1;
	    size_t		copy_count = read_count;

	    if ((size_t)(row_end - src) < read_count)
	      return (false);
	    if (written + copy_count > width)
	      copy_count = width - written;
	    memcpy(&dst[written], src, copy_count);
	    src += read_count;
	    written += copy_count;
	  }
	else if (code >= -127)
	  {
	    size_t		count = (size_t)(1 - code);
	    uint8_t	value;

	    if (src >= row_end)
	      return (false);
	    value = *src++;
	    while (count-- > 0 && written < width)
	      dst[written++] = value;
	  }
      }
    while (written < width)
      dst[written++] = 0;
    return (true);
  }

  static bool		decode_channel_data(const uint8_t	*src,
					    size_t		len,
					    int		width,
					    int		height,
					    std::vector<uint8_t>&out)
  {
    Reader			rd(src, len);
    uint16_t		compression;

    out.clear();
    if (width <= 0 || height <= 0)
      return (true);
    out.resize((size_t)width * (size_t)height, 0);
    compression = rd.readU16();
    if (!rd.ok)
      return (false);
    if (compression == 0)
      {
	size_t		need = (size_t)width * (size_t)height;

	if (!rd.canRead(need))
	  return (false);
	memcpy(&out[0], rd.readBytes(need), need);
	return (rd.ok);
      }
    if (compression != 1)
      return (false);
    std::vector<uint16_t>	rowlen((size_t)height, 0);

    for (int y = 0; y < height; ++y)
      rowlen[(size_t)y] = rd.readU16();
    if (!rd.ok)
      return (false);
    for (int y = 0; y < height; ++y)
      {
	const uint8_t	*row_src = rd.data + rd.pos;
	const uint8_t	*row_end;

	if (!rd.canRead(rowlen[(size_t)y]))
	  return (false);
	row_end = row_src + rowlen[(size_t)y];
	if (decode_packbits_row(row_src, row_end, &out[(size_t)y * (size_t)width], (size_t)width) == false)
	  return (false);
	rd.pos += rowlen[(size_t)y];
      }
    return (true);
  }

  static const std::vector<uint8_t>	*find_channel(const PsdLayer	&layer,
						      int	id)
  {
    for (size_t i = 0; i < layer.channels.size(); ++i)
      if (layer.channels[i].id == id)
	return (&layer.channels[i].data);
    return (NULL);
  }

  static void		blend_pixel(uint8_t	*dst,
				    uint8_t	sr,
				    uint8_t	sg,
				    uint8_t	sb,
				    uint8_t	sa)
  {
    unsigned int	da = dst[3];
    unsigned int	sa_u = sa;
    unsigned int	outa = sa_u + (da * (255 - sa_u) + 127) / 255;

    if (outa == 0)
      {
	dst[0] = 0;
	dst[1] = 0;
	dst[2] = 0;
	dst[3] = 0;
	return ;
      }
    unsigned int	drp = dst[0] * da;
    unsigned int	dgp = dst[1] * da;
    unsigned int	dbp = dst[2] * da;
    unsigned int	srp = sr * sa_u;
    unsigned int	sgp = sg * sa_u;
    unsigned int	sbp = sb * sa_u;
    unsigned int	out_rp = srp + (drp * (255 - sa_u) + 127) / 255;
    unsigned int	out_gp = sgp + (dgp * (255 - sa_u) + 127) / 255;
    unsigned int	out_bp = sbp + (dbp * (255 - sa_u) + 127) / 255;

    dst[0] = (uint8_t)((out_rp + outa / 2) / outa);
    dst[1] = (uint8_t)((out_gp + outa / 2) / outa);
    dst[2] = (uint8_t)((out_bp + outa / 2) / outa);
    dst[3] = (uint8_t)outa;
  }

  static void		blend_layer(std::vector<uint8_t>	&target,
				    const DecodedPsd	&psd,
				    const PsdLayer	&layer)
  {
    const std::vector<uint8_t>	*ch0 = find_channel(layer, 0);
    const std::vector<uint8_t>	*ch1 = find_channel(layer, 1);
    const std::vector<uint8_t>	*ch2 = find_channel(layer, 2);
    const std::vector<uint8_t>	*cha = find_channel(layer, -1);
    int				lw = layer.width();
    int				lh = layer.height();

    if (lw <= 0 || lh <= 0)
      return ;
    for (int y = 0; y < lh; ++y)
      {
	int			dy = layer.top + y;

	if (dy < 0 || dy >= (int)psd.height)
	  continue ;
	for (int x = 0; x < lw; ++x)
	  {
	    int			dx = layer.left + x;
	    size_t		src_id = (size_t)y * (size_t)lw + (size_t)x;
	    size_t		dst_id;
	    uint8_t		r, g, b, a = 255;

	    if (dx < 0 || dx >= (int)psd.width)
	      continue ;
	    if (psd.color_mode == 3)
	      {
		r = ch0 && src_id < ch0->size() ? (*ch0)[src_id] : 0;
		g = ch1 && src_id < ch1->size() ? (*ch1)[src_id] : 0;
		b = ch2 && src_id < ch2->size() ? (*ch2)[src_id] : 0;
	      }
	    else
	      {
		r = ch0 && src_id < ch0->size() ? (*ch0)[src_id] : 0;
		g = r;
		b = r;
	      }
	    if (cha && src_id < cha->size())
	      a = (*cha)[src_id];
	    a = (uint8_t)(((unsigned)a * (unsigned)layer.opacity + 127) / 255);
	    if (a == 0)
	      continue ;
	    dst_id = ((size_t)dy * (size_t)psd.width + (size_t)dx) * 4;
	    blend_pixel(&target[dst_id], r, g, b, a);
	  }
      }
  }

  static bool		is_effectively_visible(const std::vector<PsdLayer>	&layers,
					       int			idx)
  {
    while (idx >= 0 && idx < (int)layers.size())
      {
	if (layers[(size_t)idx].visible() == false)
	  return (false);
	idx = layers[(size_t)idx].parent;
      }
    return (true);
  }

  static bool		is_descendant_of(const std::vector<PsdLayer>	&layers,
					 int			idx,
					 int			ancestor)
  {
    idx = layers[(size_t)idx].parent;
    while (idx >= 0 && idx < (int)layers.size())
      {
	if (idx == ancestor)
	  return (true);
	idx = layers[(size_t)idx].parent;
      }
    return (false);
  }

  static void		build_parent_links(std::vector<PsdLayer>& layers)
  {
    std::vector<int>	stack;

    for (int i = (int)layers.size() - 1; i >= 0; --i)
      {
	layers[(size_t)i].parent = stack.empty() ? -1 : stack.back();
	if (layers[(size_t)i].isFolder())
	  stack.push_back(i);
	else if (layers[(size_t)i].isGroupEnd() && !stack.empty())
	  stack.pop_back();
      }
  }

  static int		find_named_layer(const std::vector<PsdLayer>	&layers,
					 const std::string		&target)
  {
    for (int i = (int)layers.size() - 1; i >= 0; --i)
      if (!layers[(size_t)i].isGroupEnd() && layers[(size_t)i].name == target)
	return (i);
    std::string		lower = ascii_lower(target);

    for (int i = (int)layers.size() - 1; i >= 0; --i)
      if (!layers[(size_t)i].isGroupEnd() && ascii_lower(layers[(size_t)i].name) == lower)
	return (i);
    return (-1);
  }

  static bool		compose_named_target(DecodedPsd	&psd,
					     int		idx,
					     std::vector<uint8_t>	&out)
  {
    if (idx < 0 || idx >= (int)psd.layers.size())
      return (false);
    out.assign((size_t)psd.width * (size_t)psd.height * 4, 0);
    if (psd.layers[(size_t)idx].isFolder())
      {
	for (size_t i = 0; i < psd.layers.size(); ++i)
	  if (!psd.layers[i].isFolder() && !psd.layers[i].isGroupEnd() &&
	      is_descendant_of(psd.layers, (int)i, idx) &&
	      is_effectively_visible(psd.layers, (int)i))
	    blend_layer(out, psd, psd.layers[i]);
	return (true);
      }
    if (psd.layers[(size_t)idx].isGroupEnd())
      return (false);
    if (is_effectively_visible(psd.layers, idx) == false)
      return (true);
    blend_layer(out, psd, psd.layers[(size_t)idx]);
    return (true);
  }

  static bool		parse_layer_record(Reader		&rd,
					   PsdLayer	&layer)
  {
    uint16_t		channel_count;
    uint32_t		extra_len;
    size_t			extra_end;
    uint32_t		tmp_len;

    layer.top = rd.readS32();
    layer.left = rd.readS32();
    layer.bottom = rd.readS32();
    layer.right = rd.readS32();
    channel_count = rd.readU16();
    if (!rd.ok)
      return (false);
    layer.channels.resize(channel_count);
    for (uint16_t i = 0; i < channel_count; ++i)
      {
	layer.channels[(size_t)i].id = rd.readS16();
	layer.channels[(size_t)i].length = rd.readU32();
      }
    if (!rd.ok || rd.readTag() != "8BIM")
      return (false);
    layer.blend_key = rd.readTag();
    layer.opacity = rd.readU8();
    layer.clipping = rd.readU8();
    layer.flags = rd.readU8();
    rd.readU8();
    extra_len = rd.readU32();
    if (!rd.ok)
      return (false);
    extra_end = rd.pos + extra_len;
    if (extra_end > rd.size)
      return (false);
    tmp_len = rd.readU32();
    if (!rd.ok || rd.pos + tmp_len > extra_end || !rd.skip(tmp_len))
      return (false);
    tmp_len = rd.readU32();
    if (!rd.ok || rd.pos + tmp_len > extra_end || !rd.skip(tmp_len))
      return (false);
    layer.name = read_pascal_string_4(rd, extra_end);
    if (!rd.ok)
      return (false);
    layer.section_type = 0;
    while (rd.ok && rd.pos + 12 <= extra_end)
      {
	std::string	sig = rd.readTag();
	std::string	key = rd.readTag();
	uint32_t	alen = rd.readU32();
	size_t		data_pos = rd.pos;
	size_t		data_end = data_pos + alen;

	if (!rd.ok || data_end > extra_end)
	  return (false);
	if ((sig == "8BIM" || sig == "8B64") && key == "luni")
	  {
	    std::string	uname = read_unicode_name(&rd.data[data_pos], alen);

	    if (!uname.empty())
	      layer.name = uname;
	  }
	else if ((sig == "8BIM" || sig == "8B64") && key == "lsct" && alen >= 4)
	  layer.section_type = (int)((uint32_t(rd.data[data_pos]) << 24) |
				     (uint32_t(rd.data[data_pos + 1]) << 16) |
				     (uint32_t(rd.data[data_pos + 2]) << 8) |
				     uint32_t(rd.data[data_pos + 3]));
	rd.pos = data_end;
	if (rd.pos % 2 != 0)
	  ++rd.pos;
      }
    rd.pos = extra_end;
    return (rd.ok);
  }

  static bool		parse_layer_channels(Reader		&rd,
					     std::vector<PsdLayer>& layers,
					     size_t		layer_info_end)
  {
    for (size_t i = 0; i < layers.size(); ++i)
      for (size_t j = 0; j < layers[i].channels.size(); ++j)
	{
	  LayerChannel		&chan = layers[i].channels[j];
	  size_t			start = rd.pos;

	  if (start + chan.length > layer_info_end)
	    return (false);
	  if ((chan.id >= 0 && chan.id <= 2) || chan.id == -1)
	    {
	      if (decode_channel_data(&rd.data[start], chan.length, layers[i].width(), layers[i].height(), chan.data) == false)
		return (false);
	    }
	  rd.pos = start + chan.length;
	}
    return (rd.ok);
  }

  static bool		decode_psd(const void		*buffer,
				   size_t		len,
				   DecodedPsd		&psd)
  {
    Reader			rd(buffer, len);
    uint16_t		version;
    uint16_t		channels;
    uint32_t		section_len;
    uint32_t		layer_mask_len;
    uint32_t		layer_info_len;
    int16_t		layer_count;
    size_t			layer_mask_end;
    size_t			layer_info_end;

    if (rd.readTag() != "8BPS")
      return (false);
    version = rd.readU16();
    if (version != 1 || !rd.skip(6))
      return (false);
    channels = rd.readU16();
    (void)channels;
    psd.height = rd.readU32();
    psd.width = rd.readU32();
    psd.depth = rd.readU16();
    psd.color_mode = rd.readU16();
    if (!rd.ok)
      return (false);
    if (psd.width == 0 || psd.height == 0)
      return (false);
    if (psd.depth != 8)
      return (false);
    if (psd.color_mode != 1 && psd.color_mode != 3)
      return (false);
    section_len = rd.readU32();
    if (!rd.ok || !rd.skip(section_len))
      return (false);
    section_len = rd.readU32();
    if (!rd.ok || !rd.skip(section_len))
      return (false);
    layer_mask_len = rd.readU32();
    if (!rd.ok)
      return (false);
    if (layer_mask_len == 0)
      return (true);
    layer_mask_end = rd.pos + layer_mask_len;
    if (layer_mask_end > rd.size)
      return (false);
    layer_info_len = rd.readU32();
    if (!rd.ok)
      return (false);
    if (layer_info_len == 0)
      {
	rd.pos = layer_mask_end;
	return (true);
      }
    layer_info_end = rd.pos + layer_info_len;
    if (layer_info_end > layer_mask_end)
      return (false);
    layer_count = rd.readS16();
    if (!rd.ok)
      return (false);
    if (layer_count < 0)
      layer_count = (int16_t)-layer_count;
    psd.layers.resize((size_t)layer_count);
    for (int i = 0; i < layer_count; ++i)
      if (parse_layer_record(rd, psd.layers[(size_t)i]) == false)
	return (false);
    if (parse_layer_channels(rd, psd.layers, layer_info_end) == false)
      return (false);
    build_parent_links(psd.layers);
    {
      int		color = find_named_layer(psd.layers, "Color");
      int	normal = find_named_layer(psd.layers, "Normal");

      if (color >= 0)
	psd.has_color = compose_named_target(psd, color, psd.color);
      if (normal >= 0)
	psd.has_normal = compose_named_target(psd, normal, psd.normal);
    }
    return (true);
  }

  static sf::RenderTexture	*build_render_texture(const uint8_t	*rgba,
						      uint32_t	width,
						      uint32_t	height)
  {
    sf::Image			img({width, height}, rgba);
    sf::Texture		txt;
    sf::RenderTexture	*rtex;

    if (img.getSize() != sf::Vector2u(width, height))
      return (NULL);
    if (txt.loadFromImage(img) == false)
      return (NULL);
    if ((rtex = new (std::nothrow) sf::RenderTexture({width, height})) == NULL)
      return (NULL);
    rtex->clear(sf::Color(0, 0, 0, 0));
    rtex->draw(sf::Sprite(txt));
    rtex->display();
    return (rtex);
  }

  static void		init_picture_fields(struct bunny_picture	*pic,
					    uint64_t		hash)
  {
    pic->res_id = hash;
    pic->tex = &pic->texture->getTexture();
    pic->ntex = pic->ntexture ? &pic->ntexture->getTexture() : NULL;
    pic->type = GRAPHIC_RAM;
    pic->width = pic->tex->getSize().x;
    pic->height = pic->tex->getSize().y;
    pic->rect.x = 0;
    pic->rect.y = 0;
    pic->rect.w = pic->width;
    pic->rect.h = pic->height;
    pic->position.x = 0;
    pic->position.y = 0;
    pic->origin.x = 0;
    pic->origin.y = 0;
    pic->scale.x = 1;
    pic->scale.y = 1;
    pic->rotation = 0;
    pic->color_mask.full = WHITE;
    pic->smooth = false;
    pic->mosaic = false;
    pic->glactive = false;
  }

  static void		init_pixelarray_fields(struct bunny_pixelarray	*pa,
					       uint64_t		     hash)
  {
    pa->type = SYSTEM_RAM;
    pa->unused = 0;
    pa->width = pa->tex->getSize().x;
    pa->height = pa->tex->getSize().y;
    pa->rect.x = 0;
    pa->rect.y = 0;
    pa->rect.w = pa->width;
    pa->rect.h = pa->height;
    pa->position.x = 0;
    pa->position.y = 0;
    pa->origin.x = 0;
    pa->origin.y = 0;
    pa->scale.x = 1;
    pa->scale.y = 1;
    pa->rotation = 0;
    pa->color_mask.full = WHITE;
    pa->smooth = false;
    pa->mosaic = false;
    pa->bitplane = false;
    pa->palette_size = 0;
    memset(pa->palette, 0, sizeof(pa->palette));
    pa->bits_per_pixels = BBW_ARGB_COLORS;
    memcpy(pa->color_shifts, default_shift, sizeof(pa->color_shifts));
    pa->glactive = false;
    pa->res_id = hash;
  }
}

bool			_bunny_is_psd_filename(const char	*file)
{
  return (has_psd_extension(file));
}

bool			_bunny_is_psd_buffer(const void	*buffer,
					     size_t	len)
{
  return (buffer != NULL && len >= 4 && memcmp(buffer, "8BPS", 4) == 0);
}

t_bunny_picture		*_bunny_load_psd_picture_from_memory(const void	*buffer,
							     size_t	len,
							     const char	*file)
{
  struct bunny_picture	*pic = NULL;
  uint64_t		hash = file ? bunny_hash(BH_FNV, file, strlen(file)) : 0;
  DecodedPsd		psd;
  sf::Texture		flat;
  sf::RenderTexture	*newtex = NULL;

  if (buffer == NULL || len == 0)
    return (NULL);
  if ((pic = new (std::nothrow) struct bunny_picture) == NULL)
    return (NULL);
  pic->texture = NULL;
  pic->ntexture = NULL;
  pic->tex = NULL;
  pic->ntex = NULL;
  pic->sprite = NULL;
  if (decode_psd(buffer, len, psd) && psd.has_color)
    {
      if (RessourceManager.disable_manager || file == NULL ||
	  (pic->texture = (sf::RenderTexture*)RessourceManager.TryGet(ResManager::SF_RENDERTEXTURE, hash)) == NULL)
	{
	  if ((newtex = build_render_texture(&psd.color[0], psd.width, psd.height)) == NULL)
	    goto Fail;
	  pic->texture = newtex;
	}
      if (psd.has_normal)
	if ((pic->ntexture = build_render_texture(&psd.normal[0], psd.width, psd.height)) == NULL)
	  goto Fail;
    }
  else
    {
      if (RessourceManager.disable_manager || file == NULL ||
	  (pic->texture = (sf::RenderTexture*)RessourceManager.TryGet(ResManager::SF_RENDERTEXTURE, hash)) == NULL)
	{
	  if (flat.loadFromMemory(buffer, len) == false)
	    goto Fail;
	  if ((pic->texture = new (std::nothrow) sf::RenderTexture({flat.getSize().x, flat.getSize().y})) == NULL)
	    goto Fail;
	  pic->texture->clear(sf::Color(0, 0, 0, 0));
	  pic->texture->draw(sf::Sprite(flat));
	  pic->texture->display();
	  newtex = pic->texture;
	}
      if (decode_psd(buffer, len, psd) && psd.has_normal)
	if ((pic->ntexture = build_render_texture(&psd.normal[0], psd.width, psd.height)) == NULL)
	  goto Fail;
    }
  init_picture_fields(pic, hash);
  if ((pic->sprite = new (std::nothrow) sf::Sprite(*pic->tex)) == NULL)
    goto Fail;
  if (RessourceManager.disable_manager == false && file != NULL && newtex != NULL)
    RessourceManager.AddToPool(ResManager::SF_RENDERTEXTURE, file, hash, pic, pic->texture);
  return ((t_bunny_picture*)pic);
 Fail:
  if (pic)
    {
      if (newtex == pic->texture)
	delete pic->texture;
      if (pic->ntexture)
	delete pic->ntexture;
      delete pic;
    }
  return (NULL);
}

t_bunny_pixelarray		*_bunny_load_psd_pixelarray_from_memory(const void	*buffer,
									size_t		len,
									const char	*file)
{
  struct bunny_pixelarray	*pa = NULL;
  uint64_t			hash = file ? bunny_hash(BH_FNV, file, strlen(file)) : 0;
  DecodedPsd			psd;
  sf::Image			flat_img;
  sf::Image			*newimg = NULL;
  sf::Texture			*newtex = NULL;
  unsigned int			*newpixels = NULL;

  if (buffer == NULL || len == 0)
    return (NULL);
  if ((pa = new (std::nothrow) struct bunny_pixelarray) == NULL)
    return (NULL);
  pa->ntexture = NULL;
  pa->ntex = NULL;
  pa->image = NULL;
  pa->tex = NULL;
  pa->sprite = NULL;
  pa->rawpixels = NULL;
  if (decode_psd(buffer, len, psd) && psd.has_color)
    {
      if (RessourceManager.disable_manager || file == NULL ||
	  (pa->tex = (sf::Texture*)RessourceManager.TryGet(ResManager::SF_TEXTURE, hash)) == NULL)
	{
	  if ((newimg = new (std::nothrow) sf::Image({psd.width, psd.height}, &psd.color[0])) == NULL)
	    goto Fail;
	  if (newimg->getSize() != sf::Vector2u(psd.width, psd.height))
	    goto Fail;
	  if ((newtex = new (std::nothrow) sf::Texture) == NULL)
	    goto Fail;
	  if (newtex->loadFromImage(*newimg) == false)
	    goto Fail;
	  if ((newpixels = (unsigned int*)bunny_malloc(psd.color.size())) == NULL)
	    goto Fail;
	  memcpy(newpixels, &psd.color[0], psd.color.size());
	  pa->image = newimg;
	  pa->tex = newtex;
	  pa->rawpixels = newpixels;
	}
      else
	{
	  pa->image = (sf::Image*)RessourceManager.TryGet(ResManager::SF_IMAGE, hash);
	  pa->tex = (sf::Texture*)RessourceManager.TryGet(ResManager::SF_TEXTURE, hash);
	  pa->rawpixels = (unsigned int*)RessourceManager.TryGet(ResManager::BUNNY_PIXELS, hash);
	}
      if (psd.has_normal)
	if ((pa->ntexture = build_render_texture(&psd.normal[0], psd.width, psd.height)) == NULL)
	  goto Fail;
    }
  else
    {
      if (RessourceManager.disable_manager || file == NULL ||
	  (pa->tex = (sf::Texture*)RessourceManager.TryGet(ResManager::SF_TEXTURE, hash)) == NULL)
	{
	  flat_img.loadFromMemory(buffer, len);
	  if (flat_img.getSize().x == 0 || flat_img.getSize().y == 0)
	    goto Fail;
	  if ((newimg = new (std::nothrow) sf::Image(flat_img)) == NULL)
	    goto Fail;
	  if ((newtex = new (std::nothrow) sf::Texture) == NULL)
	    goto Fail;
	  if (newtex->loadFromImage(*newimg) == false)
	    goto Fail;
	  if ((newpixels = (unsigned int*)bunny_malloc((size_t)newimg->getSize().x * (size_t)newimg->getSize().y * 4)) == NULL)
	    goto Fail;
	  memcpy(newpixels, newimg->getPixelsPtr(), (size_t)newimg->getSize().x * (size_t)newimg->getSize().y * 4);
	  pa->image = newimg;
	  pa->tex = newtex;
	  pa->rawpixels = newpixels;
	}
      else
	{
	  pa->image = (sf::Image*)RessourceManager.TryGet(ResManager::SF_IMAGE, hash);
	  pa->tex = (sf::Texture*)RessourceManager.TryGet(ResManager::SF_TEXTURE, hash);
	  pa->rawpixels = (unsigned int*)RessourceManager.TryGet(ResManager::BUNNY_PIXELS, hash);
	}
      if (decode_psd(buffer, len, psd) && psd.has_normal)
	if ((pa->ntexture = build_render_texture(&psd.normal[0], psd.width, psd.height)) == NULL)
	  goto Fail;
    }
  init_pixelarray_fields(pa, hash);
  if ((pa->sprite = new (std::nothrow) sf::Sprite(*pa->tex)) == NULL)
    goto Fail;
  if (RessourceManager.disable_manager == false && file != NULL && newimg != NULL)
    {
      RessourceManager.AddToPool(ResManager::SF_IMAGE, file, hash, pa, pa->image);
      RessourceManager.AddToPool(ResManager::SF_TEXTURE, file, hash, pa, pa->tex);
      RessourceManager.AddToPool(ResManager::BUNNY_PIXELS, file, hash, pa, pa->rawpixels);
    }
  return ((t_bunny_pixelarray*)pa);
 Fail:
  if (pa)
    {
      if (pa->ntexture)
	delete pa->ntexture;
      if (newtex)
	delete newtex;
      if (newimg)
	delete newimg;
      if (newpixels)
	bunny_free(newpixels);
      delete pa;
    }
  return (NULL);
}
