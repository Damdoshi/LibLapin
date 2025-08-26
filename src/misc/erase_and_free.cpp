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

