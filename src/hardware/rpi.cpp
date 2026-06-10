// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2022
//
// Bibliotheque Lapin

#include	<stdio.h>
#include	<stdlib.h>
#include	<fcntl.h>
#include	<sys/mman.h>
#include	<unistd.h>
#include	"lapin_private.h"


/**
 * @doc
 * @doc-symbol bunny_new_rpi
 * @doc-kind function
 * @doc-module hardware
 * @doc-order 220
 * @doc-since 0
 * @doc-until latest
 * @doc-level 50
 *
 * @doc-lang en
 * @brief Maps the Raspberry Pi GPIO memory area.
 * @return-success Returns the mapped GPIO memory area.
 * @return-failure Returns NULL if /dev/mem cannot be opened or mapped.
 * @see bunny_delete_rpi
 *
 * @doc-lang fr
 * @brief Mappe la zone mémoire GPIO du Raspberry Pi.
 * @return-success Renvoie la zone mémoire GPIO mappée.
 * @return-failure Renvoie NULL si /dev/mem ne peut pas être ouvert ou mappé.
 * @see bunny_delete_rpi
 */
t_bunny_rpi	*bunny_new_rpi(void)
{
  t_bunny_rpi	*rpi;
  int		fd;

  if ((fd = open("/dev/mem", O_RDWR | O_SYNC)) == -1)
    return (NULL);
  rpi = (t_bunny_rpi*)mmap(NULL, 4096, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0x7E200000);
  close(fd);
  return (rpi);
}


/**
 * @doc
 * @doc-symbol bunny_delete_rpi
 * @doc-kind function
 * @doc-module hardware
 * @doc-order 240
 * @doc-since 0
 * @doc-until latest
 * @doc-level 50
 *
 * @doc-lang en
 * @brief Unmaps a Raspberry Pi GPIO memory area.
 * @param rpi Mapping returned by bunny_new_rpi.
 * @see bunny_new_rpi
 *
 * @doc-lang fr
 * @brief Démappe une zone mémoire GPIO Raspberry Pi.
 * @param rpi Mapping renvoyé par bunny_new_rpi.
 * @see bunny_new_rpi
 */
void		bunny_delete_rpi(t_bunny_rpi	*rpi)
{
  munmap((void*)rpi, 4096);
}
