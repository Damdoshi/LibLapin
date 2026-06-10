// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2025
//
// Bibliotheque Lapin

// Tout ca pour empecher l'optimisation de memset...

#define			__STDC_WANT_LIB_EXT1__			1
#include		"lapin_private.h"
#include		<strings.h>

#if defined(__GLIBC__) && (__GLIBC__ >= 2) && (__GLIBC_MINOR__ >= 25)
# define		HAVE_EXPLICIT_BZERO
#endif

#if defined(__STDC_LIB_EXT1__) || (defined(__STDC_WANT_LIB_EXT1__) && __STDC_WANT_LIB_EXT1__ == 1)
# define		HAVE_MEMSET_S
#endif


/**
 * @doc
 * @doc-symbol bunny_erase_and_free
 * @doc-kind function
 * @doc-module misc
 * @doc-order 460
 * @doc-since 12
 * @doc-until latest
 * @doc-level advanced
 *
 * @doc-lang en
 * @brief Erases a memory block before freeing it.
 * @param ptr Memory block to erase and release.
 * @param len Number of bytes to clear before free.
 * @description The implementation uses an explicit clearing strategy to avoid the compiler removing the wipe before free.
 * @see bunny_zero, bunny_erase
 *
 * @doc-lang fr
 * @brief Efface un bloc mémoire avant de le libérer.
 * @param ptr Bloc mémoire à effacer puis libérer.
 * @param len Nombre d'octets à remettre à zéro avant free.
 * @description L'implémentation utilise une stratégie d'effacement explicite pour éviter que le compilateur retire la remise à zéro avant free.
 * @see bunny_zero, bunny_erase
 */
void			bunny_erase_and_free(void		*ptr,
					     size_t		len)
{
#ifdef			HAVE_EXPLICIT_BZERO
  explicit_bzero(ptr, len);
#elif			defined(HAVE_MEMSET_S)
  memset_s(ptr, len, 0, len);
#elif			defined(__GNUC__) || defined(__clang__)
  memset(ptr, 0, len);
  __asm__ __volatile__ ("" : : "r"(ptr) : "memory");
#else
  volatile unsigned char *p = (volatile unsigned char *)ptr;
  while (len--)
    *p++ = 0;
#endif
  free(ptr);
}

