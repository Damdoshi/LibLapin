// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2016
//
// Bibliotheque Lapin

#include		<string.h>
#include		"lapin_private.h"

#define			PATTERN		"%s -> %p"

t_bunny_effect		*bunny_load_effect(const char		*file)
{
  struct bunny_effect	*eff;
  size_t		len;
  uint64_t		hash;
  
  hash = bunny_hash(BH_FNV, file, strlen(file));
  if ((eff = new (std::nothrow) struct bunny_effect) == NULL)
    goto Fail;
  if ((eff->effect = (sf::SoundBuffer*)RessourceManager.TryGet(ResManager::SF_SOUNDBUFFER, hash)) == NULL)
    {
      if ((eff->effect = new (std::nothrow) sf::SoundBuffer) == NULL)
	goto FailStruct;
      fprintf(stderr, "NEW EFFECT LOADING %p\n", eff->effect);
      if ((eff->effect->loadFromFile(file)) == false)
	goto FailEffect;
      len = eff->effect->getSampleCount();
      if ((eff->sample = (int16_t*)bunny_malloc(sizeof(*eff->sample) * len)) == NULL)
	goto FailEffect;
      memcpy(eff->sample, eff->effect->getSamples(), len * sizeof(*eff->sample));
    }
  else
    eff->sample = (int16_t*)RessourceManager.TryGet(ResManager::BUNNY_SAMPLE, hash);

  RessourceManager.AddToPool(ResManager::SF_SOUNDBUFFER, hash, eff, eff->effect);
  RessourceManager.AddToPool(ResManager::BUNNY_SAMPLE, hash, eff, eff->sample);

  eff->res_id = hash;

  eff->file = strdup(file);
  eff->sample_per_second = eff->effect->getSampleRate();
  eff->duration = (double)eff->effect->getSampleCount() / eff->sample_per_second;
  eff->sound.setBuffer(*eff->effect);
  eff->type = EFFECT;

  scream_log_if(PATTERN, file, eff);
  return ((t_bunny_effect*)eff);

 FailEffect:
  delete eff->effect;
 FailStruct:
  delete eff;
 Fail:
  scream_error_if(return (NULL), bunny_errno, PATTERN, file, (void*)NULL);
  return (NULL);
}
