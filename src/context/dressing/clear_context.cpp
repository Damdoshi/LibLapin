// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2018
//
// Bibliothèque Lapin

#include		"lapin_private.h"

void			bunny_clear_dressing_context(t_bunny_dressing_screen *cnt)
{
  (void)cnt;
  /*
  t_bunny_dressing_character *dchar;
  int			i, j, k;

  if (cnt->characters == NULL)
    return ;
  for (i = 0; i < (int)cnt->nbr_characters; ++i)
    {
      dchar = &cnt->characters[i];

      if (dchar->character_name)
	bunny_delete_clipable(&dchar->character_name->clipable);

      if (dchar->background)
	bunny_delete_clipable(dchar->background);

      if (dchar->character)
	bunny_delete_clipable(&dchar->character->clipable);

      if (dchar->dressing)
	{
	  for (j = 0; j < (int)dchar->nbr_dressing; ++j)
	    {
	      bunny_delete_clipable(&dchar->dressing[j].dressing_name->clipable);
	      if (dchar->dressing[j].clothes)
		{
		  for (k = 0; k < (int)dchar->dressing[j].nbr_clothes; ++k)
		    bunny_delete_clipable(&dchar->dressing[j].clothes[k]->clipable);
		  bunny_free(dchar->dressing[j].clothes);
		}
	      if (dchar->dressing[j].on_character_clothes)
		{
		  for (k = 0; k < (int)dchar->dressing[j].nbr_clothes; ++k)
		    bunny_delete_clipable
		      (&dchar->dressing[j].on_character_clothes[k]->clipable);
		  bunny_free(dchar->dressing[j].on_character_clothes);
		}
	    }
	  bunny_free(dchar->dressing);
	}

      if (dchar->displayed_clothes)
	bunny_free(dchar->displayed_clothes);
    }
  bunny_free(cnt->characters);
  cnt->characters = NULL;
  */
}
