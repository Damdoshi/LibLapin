// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2016
//
// Bibliotheque Lapin

#include		<string.h>
#include		"lapin_private.h"

t_bunny_music		*bunny_load_music(const char		*file)
{
  struct bunny_music	*mus;

  if ((mus = new (std::nothrow) struct bunny_music) == NULL)
    goto Fail;
  if ((mus->music.openFromFile(file)) == false)
    goto FailStruct;

  mus->file = strdup(file);
  mus->type = MUSIC;
  mus->duration = mus->music.getDuration().asSeconds();

  BUNNY_LOG(fprintf(stderr, "%s: Returning %p.\n", __PRETTY_FUNCTION__, mus));
  
  return ((t_bunny_music*)mus);

 FailStruct:
  delete mus;
 Fail:
  return (NULL);
}
