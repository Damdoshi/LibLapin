// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2018
//
// Lapin library

#include		<stdint.h>
#include		"lapin_private.h"

static const char	*gl_dictionnary =
  "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/"
  ;
static unsigned char	gl_id[256];


/**
 * @doc
 * @doc-symbol bunny_base64_encode
 * @doc-kind function
 * @doc-module misc
 * @doc-order 190
 * @doc-since 11
 * @doc-until latest
 * @doc-level beginner
 *
 * @doc-lang en
 * @brief Encodes binary data as base64 text.
 * @param data Data to encode.
 * @param len Input size in bytes.
 * @param out Pointer to the output buffer pointer. If *out is NULL or too small, the function allocates a new buffer.
 * @param outlen Input capacity of *out and output size of the encoded text. It may be NULL.
 * @return-success Returns true and writes a zero-terminated base64 string.
 * @return-failure Returns false on allocation failure.
 * @see bunny_base64_decode, bunny_base64_check
 *
 * @doc-lang fr
 * @brief Encode des données binaires en texte base64.
 * @param data Données à encoder.
 * @param len Taille d'entrée en octets.
 * @param out Pointeur vers le pointeur de tampon de sortie. Si *out vaut NULL ou est trop petit, la fonction alloue un nouveau tampon.
 * @param outlen Capacité d'entrée de *out et taille de sortie du texte encodé. Peut valoir NULL.
 * @return-success Renvoie true et écrit une chaîne base64 terminée par zéro.
 * @return-failure Renvoie false en cas d'échec d'allocation.
 * @see bunny_base64_decode, bunny_base64_check
 */
bool			bunny_base64_encode(const void		*_data,
					    size_t		len,
					    char		**out,
					    size_t		*outlen)
{
  static const size_t	terminator[] = {0, 2, 1};
  const char		*data = (const char*)_data;
  size_t		outrep;
  size_t		i, j;
  uint32_t		a, b, c;
  uint32_t		merge;

  if (outlen == NULL)
    {
      outlen = &outrep;
      outrep = 0;
    }

  if (*out != NULL && *outlen >= 4 * ((len + 2) / 3) + 1)
    *outlen = 4 * ((len + 2) / 3);
  else if ((*out = (char*)bunny_malloc((merge = 4 * ((len + 2) / 3)) + 1)) == NULL)
    return (false);
  else
    *outlen = merge;

  for (i = 0, j = 0; i < len; )
    {
      a = i < len ? data[i] & 0xFF : 0;
      i += 1;
      b = i < len ? data[i] & 0xFF : 0;
      i += 1;
      c = i < len ? data[i] & 0xFF : 0;
      i += 1;

      // Generate a 24 bit integer
      merge = a << 16 | b << 8 | c;

      // 0x3F = 0011 1111
      (*out)[j++] = gl_dictionnary[(merge >> 18) & 0x3F];
      (*out)[j++] = gl_dictionnary[(merge >> 12) & 0x3F];
      (*out)[j++] = gl_dictionnary[(merge >>  6) & 0x3F];
      (*out)[j++] = gl_dictionnary[merge & 0x3F];
    }
  for (i = 0; i < terminator[len % 3]; i++)
    (*out)[*outlen - 1 - i] = '=';
  (*out)[*outlen] = '\0';
  return (true);
}


/**
 * @doc
 * @doc-symbol bunny_base64_decode
 * @doc-kind function
 * @doc-module misc
 * @doc-order 200
 * @doc-since 11
 * @doc-until latest
 * @doc-level beginner
 *
 * @doc-lang en
 * @brief Decodes base64 text into binary data.
 * @param data Base64 text to decode.
 * @param len Input length in bytes.
 * @param out Pointer to the output buffer pointer. If *out is NULL or too small, the function allocates a new buffer.
 * @param outlen Input capacity of *out and output size of decoded data. It may be NULL.
 * @return-success Returns true if the decoding completed.
 * @return-failure Returns false if the input is invalid or allocation fails.
 * @see bunny_base64_encode, bunny_base64_check
 *
 * @doc-lang fr
 * @brief Décode un texte base64 en données binaires.
 * @param data Texte base64 à décoder.
 * @param len Longueur d'entrée en octets.
 * @param out Pointeur vers le pointeur de tampon de sortie. Si *out vaut NULL ou est trop petit, la fonction alloue un nouveau tampon.
 * @param outlen Capacité d'entrée de *out et taille de sortie des données décodées. Peut valoir NULL.
 * @return-success Renvoie true si le décodage s'est terminé.
 * @return-failure Renvoie false si l'entrée est invalide ou si l'allocation échoue.
 * @see bunny_base64_encode, bunny_base64_check
 */
bool			bunny_base64_decode(const char		*data,
					    size_t		len,
					    void		**_out,
					    size_t		*outlen)
{
  static bool		id_ok = 0;
  char			**out = (char**)_out;
  size_t		outrep;
  size_t		i, j;
  uint32_t		a, b, c, d;
  uint32_t		merge;

  // Generate reverse dictionnary map
  if (id_ok == 0)
    {
      id_ok = 1;
      for (i = 0, j = strlen(gl_dictionnary); i < j; ++i)
	gl_id[(int)gl_dictionnary[i]] = i;
    }

  if (outlen == NULL)
    {
      outlen = &outrep;
      outrep = 0;
    }

  if (*out != NULL && *outlen >= len / 4 * 3 + 1)
    *outlen = len / 4 * 3;
  else if ((*out = (char*)bunny_malloc((merge = len / 4 * 3) + 1)) == NULL)
    return (false);
  else
    *outlen = merge;

  for (i = 0, j = 0; i < len && j < *outlen && data[i] && data[i] != '='; )
    if (data[i] != '\n' && data[i] != '\r')
      {
	a = data[i] != '=' ? gl_id[(int)data[i]] : 0;
	i += 1;

	b = data[i] != '=' ? gl_id[(int)data[i]] : 0;
	i += 1;

	c = data[i] != '=' ? gl_id[(int)data[i]] : 0;
	i += 1;

	d = data[i] != '=' ? gl_id[(int)data[i]] : 0;
	i += 1;

	// Generate a 24 bit integer
	merge = a << 18 | b << 12 | c << 6 | d;

	if (j < *outlen)
	  (*out)[j++] = (merge >> 16) & 0xFF;
	if (j < *outlen)
	  (*out)[j++] = (merge >>  8) & 0xFF;
	if (j < *outlen)
	  (*out)[j++] = (merge      ) & 0xFF;
      }
    else
      i += 1;
  (*out)[j] = '\0';
  a = 0;
  while (data[len - a - 1] == '=')
    a += 1;
  *outlen = j - a;
  return (true);
}


/**
 * @doc
 * @doc-symbol bunny_base64_check
 * @doc-kind function
 * @doc-module misc
 * @doc-order 210
 * @doc-since 11
 * @doc-until latest
 * @doc-level beginner
 *
 * @doc-lang en
 * @brief Checks whether a buffer is valid base64 text.
 * @param data Text to check.
 * @param len Text length in bytes.
 * @return-success Returns true if the text has a valid base64 shape.
 * @return-failure Returns false otherwise.
 * @see bunny_base64_encode, bunny_base64_decode
 *
 * @doc-lang fr
 * @brief Vérifie si un tampon contient un texte base64 valide.
 * @param data Texte à vérifier.
 * @param len Longueur du texte en octets.
 * @return-success Renvoie true si le texte a une forme base64 valide.
 * @return-failure Renvoie false sinon.
 * @see bunny_base64_encode, bunny_base64_decode
 */
bool			bunny_base64_check(const char		*data,
					   size_t		len)
{
  size_t		i, j;

  for (i = 0, j = 0; data[i] && i < len && data[i] != '='; ++i)
    if (
	(data[i] >= 'A' && data[i] <= 'Z')
	||
	(data[i] >= 'a' && data[i] <= 'z')
	||
	(data[i] >= '0' && data[i] <= '9')
	||
	data[i] == '+'
	||
	data[i] == '/'
	)
      j += 1;
    else if (data[i] != '\n' && data[i] != '\r')
      return (false);
  while (j % 4 != 0)
    if (data[i++] != '=')
      return (false);
    else
      j += 1;
  return (true);
}


/**
 * @doc
 * @doc-symbol bunny_read_base64
 * @doc-kind function
 * @doc-module misc
 * @doc-order 215
 * @doc-since 12
 * @doc-until latest
 * @doc-level advanced
 *
 * @doc-lang en
 * @brief Reads and decodes a base64 sequence from a larger string.
 * @param data Source string.
 * @param i Current read index. It is advanced past the decoded sequence on success.
 * @param out Output buffer pointer, following bunny_base64_decode allocation rules.
 * @param outlen Output length pointer, following bunny_base64_decode rules.
 * @return-success Returns true if a base64 block was decoded.
 * @return-failure Returns false on invalid input or allocation failure.
 * @see bunny_base64_decode
 *
 * @doc-lang fr
 * @brief Lit et décode une séquence base64 depuis une chaîne plus grande.
 * @param data Chaîne source.
 * @param i Index courant de lecture. Il est avancé après la séquence décodée en cas de succès.
 * @param out Pointeur de tampon de sortie, selon les règles d'allocation de bunny_base64_decode.
 * @param outlen Pointeur de taille de sortie, selon les règles de bunny_base64_decode.
 * @return-success Renvoie true si un bloc base64 a été décodé.
 * @return-failure Renvoie false en cas d'entrée invalide ou d'échec d'allocation.
 * @see bunny_base64_decode
 */
bool				bunny_read_base64(const char		*data,
						  ssize_t		*i,
						  void			**out,
						  size_t		*outlen)
{
  ssize_t			j = *i;
  ssize_t			k;

  if (bunny_check_text(data, &j, "b64_") == false)
    return (false);
  k = j;
  if (readchar(data, j, gl_dictionnary) == false)
    return (false);
  if (readchar(data, j, "\"") == false)
    return (false);
  bool				ret;

  if ((ret = bunny_base64_decode(data, j - k, out, outlen)) != false)
    *i = k;
  return (ret);
}
