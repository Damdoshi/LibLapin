/*
** Jason Brillante "Damdoshi"
** Hanged Bunny Studio 2014-2020
**
** Bibliothèque Lapin
*/

#ifndef			__LAPIN_BROWSE_BOX_H__
# define		__LAPIN_BROWSE_BOX_H__

/*
** "Browse" est une boite "parcourir".
** Elle permet pour l'instant un seul mode d'affichage (nom de fichier seul
** accompagné d'une case a cocher demeurant, même si on change de dossier)
** Elle permet de filtrer l'affichage par extension (via un fn_match, par ex)
** Elle permet de se deplacer dans le FS.
** Elle a un bouton ok, un bouton reset, un bouton haut et un bouton annuler.
** Il est possible de selectionner plusieurs fichiers.
** Il est possible de selectionner recursivement grace aux dossiers.
** Le bouton ok permet de recuperer la selection.
** Le bouton reset detruit la selection.
** Le bouton annuler reset et sort.
** Le bouton haut permet de remonter au dossier parent.
*/

typedef enum		s_bunny_gui_browse_display_mode
  {
   BBBDM_LIST_FILE,
   BBBDM_LAST
  }			t_bunny_gui_browse_display_mode;

typedef struct		s_bunny_gui_browse
{
  // Basic properties, function pointers and subboxes...
  t_bunny_gui_box	box;
  // Allow to select multiples files - or only select a single one.
  bool			multiple_select;
  // How is the file explorer displayed? Icon? List? etc.
  t_bunny_gui_browse_display_mode file_display_mode;
  // Is there a limit to the up button?
  const char		*max_top_directory;
  // What is the default directory?
  const char		*start_directory;
  // Selected files.
  const char		*selected_files[512];
  size_t		nbr_selected_files;
  // Only display files that pass filter
  const char		*file_filters[32];
  size_t		nbr_file_filters;
  // To write file text
  t_bunny_font		*file_font;
  t_bunny_gui_box	*buttons[4]; // Ok, Reset, Cancel, Up
}			t_bunny_gui_browse;

#endif	/*		__LAPIN_BROWSE_BOX_H__	*/
