// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2018
//
// Bibliotheque Lapin

#include		<string.h>
#include		"lapin_private.h"

#define			PATTERN		"%s -> %p"

/**
 * @doc-symbol bunny_read_music
 * @doc-module sound
 * @doc-kind function
 * @doc-order 162
 * @doc-since 13
 * @doc-until latest
 * @doc-level advanced
 *
 * @doc-lang en
 * @brief Creates a music from an already loaded configuration node.
 * @param cnf Configuration node to read.
 * @return-success A valid t_bunny_music pointer.
 * @return-failure NULL if the configuration cannot be used or the music cannot be loaded.
 * @error ENOMEM Out of memory.
 * @error EINVAL Invalid or incomplete sound configuration.
 * @error ENOENT The referenced file was not found.
 * @error BE_SYNTAX_ERROR The configuration contains a syntax error.
 * @log May log in the "ressource", "configuration", "syntax" and "sound" domains through bunny_set_sound_attribute.
 * @see bunny_load_music, bunny_set_sound_attribute, bunny_delete_sound
 *
 * @doc-lang fr
 * @brief Crée une musique depuis un nœud de configuration déjà chargé.
 * @param cnf Nœud de configuration à lire.
 * @return-success Un pointeur t_bunny_music valide.
 * @return-failure NULL si la configuration ne peut pas être utilisée ou si la musique ne peut pas être chargée.
 * @error ENOMEM Mémoire insuffisante.
 * @error EINVAL Configuration sonore invalide ou incomplète.
 * @error ENOENT Le fichier référencé est introuvable.
 * @error BE_SYNTAX_ERROR La configuration contient une erreur de syntaxe.
 * @log Peut écrire dans les domaines "ressource", "configuration", "syntax" et "sound" via bunny_set_sound_attribute.
 * @see bunny_load_music, bunny_set_sound_attribute, bunny_delete_sound
 */
t_bunny_music		*bunny_read_music(t_bunny_configuration	*cnf)
{
  t_bunny_sound		*pc = NULL;

  if (bunny_set_sound_attribute(NULL, &pc, &cnf, true) == false)
    return (NULL);
  return ((t_bunny_music*)pc);
}

/**
 * @doc-symbol bunny_load_music
 * @doc-module sound
 * @doc-kind function
 * @doc-order 160
 * @doc-since 0
 * @doc-until latest
 * @doc-level beginner
 *
 * @doc-lang en
 * @brief Opens a music file or a music configuration file.
 * @description Music is streamed from disk when played. Delete it with bunny_delete_sound when it is no longer needed.
 * @param file Music file or configuration file to open. Supported sound formats are wav and ogg.
 * @return-success A valid t_bunny_music pointer.
 * @return-failure NULL if the music cannot be loaded.
 * @error ENOMEM Out of memory.
 * @error EINVAL Invalid file format.
 * @error ENOENT The file was not found.
 * @error BE_SYNTAX_ERROR The configuration file contains a syntax error.
 * @log May log in the "ressource", "configuration", "syntax" and "sound" domains.
 * @see bunny_read_music, bunny_delete_sound, t_bunny_music
 *
 * @doc-lang fr
 * @brief Ouvre un fichier musical ou un fichier de configuration musical.
 * @description La musique est lue en streaming depuis le disque. Détruisez-la avec bunny_delete_sound lorsqu'elle n'est plus nécessaire.
 * @param file Fichier musical ou fichier de configuration à ouvrir. Les formats sonores supportés sont wav et ogg.
 * @return-success Un pointeur t_bunny_music valide.
 * @return-failure NULL si la musique ne peut pas être chargée.
 * @error ENOMEM Mémoire insuffisante.
 * @error EINVAL Format de fichier invalide.
 * @error ENOENT Le fichier est introuvable.
 * @error BE_SYNTAX_ERROR Le fichier de configuration contient une erreur de syntaxe.
 * @log Peut écrire dans les domaines "ressource", "configuration", "syntax" et "sound".
 * @see bunny_read_music, bunny_delete_sound, t_bunny_music
 */
t_bunny_music		*bunny_load_music(const char		*file)
{
  struct bunny_music	*mus;

  if (bunny_which_format(file) != BC_CUSTOM)
    {
      t_bunny_configuration *cnf;

      if ((cnf = bunny_open_configuration(file, NULL)) == NULL)
	return (NULL);
      mus = (struct bunny_music*)bunny_read_music(cnf);
      bunny_delete_configuration(cnf);
      return ((t_bunny_music*)mus);
    }

  if ((mus = new (std::nothrow) struct bunny_music) == NULL)
    goto Fail;
  if ((mus->music.openFromFile(file)) == false)
    goto FailStruct;

  mus->file = bunny_strdup(file);
  mus->type = MUSIC;
  mus->duration = mus->music.getDuration().asSeconds();

  mus->volume = 50;
  mus->pitch = 1;
  mus->loop = true;
  mus->position[0] = 0;
  mus->position[1] = 0;
  mus->position[2] = 0;
  mus->attenuation = 5;
  mus->playing = false;
  mus->pause = false;
  mus->sound_manager = NULL;
  mus->sound_areas = NULL;
  mus->trap = NULL;

  scream_log_if(PATTERN, "ressource,sound", file, mus);
  return ((t_bunny_music*)mus);

 FailStruct:
  delete mus;
 Fail:
  scream_error_if(return (NULL), bunny_errno, PATTERN, "ressource,sound", file, (void*)NULL);
  return (NULL);
}
