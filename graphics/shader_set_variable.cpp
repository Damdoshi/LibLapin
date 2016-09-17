// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2015
//
// Bibliothèque Lapin

#include		<stdarg.h>
#include		"lapin_private.h"

typedef void		(*__t_func)(sf::Shader				*shader,
				    const char				*varname,
				    size_t				n,
				    va_list				*lst);

static void		get_float(sf::Shader				*shader,
				  const char				*varname,
				  size_t				n,
				  va_list				*lst)
{
  float			f[3];
  size_t		i;

  for (i = 0; i < n; ++i)
    f[i] = va_arg(*lst, double);  
  if (n == 1)
    shader->setParameter(varname, f[0]);
  else if (n == 2)
    shader->setParameter(varname, f[0], f[1]);
  else
    shader->setParameter(varname, f[0], f[1], f[2]);
}

static void		get_component(sf::Shader			*shader,
				      const char			*varname,
				      size_t				n,
				      va_list				*lst)
{
  sf::Color		color;

  (void)n;
  color.r = (unsigned char)va_arg(*lst, int);
  color.g = (unsigned char)va_arg(*lst, int);
  color.b = (unsigned char)va_arg(*lst, int);
  color.a = (unsigned char)va_arg(*lst, int);
  shader->setParameter(varname, color);
}

static void		get_color(sf::Shader				*shader,
				  const char				*varname,
				  size_t				n,
				  va_list				*lst)
{
  sf::Color		color(va_arg(*lst, unsigned int));

  (void)n;
  shader->setParameter(varname, color);
}

static void		get_transform(sf::Shader			*shader,
				      const char			*varname,
				      size_t				n,
				      va_list				*lst)
{
  t_bunny_transform	*tra = va_arg(*lst, t_bunny_transform*);
  sf::Transform		sft;

  (void)n;
  sft.translate(tra->translation.x, tra->translation.y);
  sft.rotate(tra->rotation, tra->origin.x, tra->origin.y);
  sft.scale(tra->scale.x, tra->scale.y, tra->origin.x, tra->origin.y);
  shader->setParameter(varname, sft);
}

static void		get_picture(sf::Shader				*shader,
				    const char				*varname,
				    size_t				n,
				    va_list				*lst)
{
  struct bunny_picture	*pic = va_arg(*lst, struct bunny_picture*);

  (void)n;
  shader->setParameter(varname, *pic->tex);
}

static void		get_current(sf::Shader				*shader,
				    const char				*varname,
				    size_t				n,
				    va_list				*lst)
{
  (void)n;
  (void)lst;
  shader->setParameter(varname, sf::Shader::CurrentTexture);
}

void			bunny_shader_set_variable(t_bunny_shader	*_shader,
						  const char		*varname,
						  t_bunny_variable_type	type,
						  ...)
{
  static const __t_func	func[BVT_CURRENT_TEXTURE_TYPE - 1] =
    {
      get_float, get_component, get_color, get_transform, get_picture, get_current
    };
  sf::Shader		*shader = (sf::Shader*)_shader;
  va_list		va;
  
  va_start(va, type);
  if (type - 3 < 0)
    func[0](shader, varname, type + 1, &va);
  else
    func[type - 2](shader, varname, 1, &va);
  va_end(va);
}
