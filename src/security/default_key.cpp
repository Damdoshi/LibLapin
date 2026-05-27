// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2018
//
// Lapin library

#include				<string.h>
#include				<stdint.h>
#include				"lapin_private.h"

typedef struct				s_bunny_default_key
{
  int32_t				length;
  char					key[128];
}					t_bunny_default_key;

t_bunny_default_key			gl_bunny_default_key[2] =
  {
    {
      128,
      {
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
      }
    },
    {
      128,
      {
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
      }
    }
  };

static void				funk_shift(char			*b,
						   char			shift)
{
  uint32_t				c;

  c = ((uint32_t)*b) << 8;
  if (shift > 0)
    {
      c <<= shift;
      c &= 0x00FF0000;
      c >>= 16;
      *b = (((uint32_t)(*b << shift)) & 0xFF) | c;
    }
  else if (shift < 0)
    {
      c >>= -shift;
      c &= 0x000000FF;
      *b = (((uint32_t)(*b >> -shift)) & 0xFF) | c;
    }
}

static void				funk_swap(char			*a,
						  char			*b,
						  bool			z)
{
  char					c, d;

  if (z == false)
    {
      c = (*a & 0xF0) >> 4;
      *a &= 0x0F;

      d = (*b & 0x0F) << 4;
      *b &= 0xF0;

      *a |= d;
      *b |= c;
    }
  else
    funk_swap(b, a, false);
}

//
// Twist key generate the key that will be used by bunny_security,
// so the key used is not verbatim the one in the binary file.
//

static const t_bunny_default_key	*twist_key(t_bunny_default_key	*inkey,
						   t_bunny_default_key	*outkey)
{
  size_t				pass;
  int					i;

  if (gl_bunny_my_key_twist != NULL)
    return ((t_bunny_default_key*)gl_bunny_my_key_twist((t_bunny_cipher_key*)inkey, (t_bunny_cipher_key*)outkey));
  memcpy(&outkey->key[0], &inkey->key[0], outkey->length);
  for (pass = 2; pass < 6; ++pass)
    for (i = 0; i < inkey->length; ++i)
      {
	funk_swap(&outkey->key[i], &outkey->key[(i * pass) % outkey->length], i % 2);
	funk_shift(&outkey->key[i], i % 4);
      }
  return (outkey);
}

/**
 * @doc
 * @doc-symbol bunny_default_key
 * @doc-kind function
 * @doc-module security
 * @doc-order 180
 * @doc-since 11
 * @doc-until latest
 * @doc-level beginner
 *
 * @doc-lang en
 * @brief Returns the binary-embedded default ciphering key.
 * @description The default key is stored inside the program binary and can be replaced by bunny_fill_default_key. It is intended for resource obfuscation, not for real security.
 * @return-success A pointer to the embedded key. The returned pointer must not be freed.
 * @log This function may write a log entry in the "security" log domain when the key is transformed.
 * @see bunny_fill_default_key, t_bunny_cipher_key, gl_bunny_my_key_twist
 *
 * @doc-lang fr
 * @brief Renvoie la clé de chiffrement par défaut embarquée dans le binaire.
 * @description La clé par défaut est stockée dans le binaire du programme et peut être remplacée par bunny_fill_default_key. Elle est destinée à l'obfuscation des ressources, pas à une vraie sécurité.
 * @return-success Un pointeur vers la clé embarquée. Le pointeur renvoyé ne doit pas être libéré.
 * @log Cette fonction peut écrire une entrée de log dans le domaine "security" lorsque la clé est transformée.
 * @see bunny_fill_default_key, t_bunny_cipher_key, gl_bunny_my_key_twist
 */
const t_bunny_cipher_key		*bunny_default_key(void)
{
  t_bunny_cipher_key			*key;
  int					i;

  // Because key twist seems quite bad shaped. (how I am suppose to cipher?)
  key = ((t_bunny_cipher_key*)&gl_bunny_default_key[0]);
  return (key);

  for (i = 0; i < gl_bunny_default_key[0].length; ++i)
    if (gl_bunny_default_key[0].key[i] != 0)
      {
	key = ((t_bunny_cipher_key*)twist_key(&gl_bunny_default_key[0], &gl_bunny_default_key[1]));
	scream_log_if("-> %p", "security", key);
	return (key);
      }
  key = ((t_bunny_cipher_key*)&gl_bunny_default_key[0]);
  scream_log_if("-> %p", "security", key);
  return (key);
}
