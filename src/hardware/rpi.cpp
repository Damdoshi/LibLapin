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

void		bunny_delete_rpi(t_bunny_rpi	*rpi)
{
  munmap((void*)rpi, 4096);
}
