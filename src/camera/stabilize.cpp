// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2018
//
// Lapin library

#include		"lapin_private.h"


/**
 * @doc
 * @doc-symbol bunny_stabilize_headtrack
 * @doc-kind function
 * @doc-module camera
 * @doc-order 340
 * @doc-since 12
 * @doc-until latest
 * @doc-level 40
 *
 * @doc-lang en
 * @brief Smooths a detected head area over time.
 * @description This helper moves current toward previous with bunny_smooth_move semantics, reducing abrupt head tracking jumps.
 * @param previous The previous head area.
 * @param current The current head area to modify.
 * @param speed Interpolation speed between 0 and 1.
 * @log This function writes logs in the "camera" domain.
 * @see bunny_camera_headtrack, bunny_smooth_move
 *
 * @doc-lang fr
 * @brief Lisse une zone de tête détectée au fil du temps.
 * @description Cet assistant déplace current vers previous avec la sémantique de bunny_smooth_move, afin de réduire les sauts brusques du suivi de tête.
 * @param previous La zone de tête précédente.
 * @param current La zone de tête courante à modifier.
 * @param speed La vitesse d'interpolation entre 0 et 1.
 * @log Cette fonction écrit des logs dans le domaine "camera".
 * @see bunny_camera_headtrack, bunny_smooth_move
 */

void			bunny_stabilize_headtrack(const t_bunny_area	*prev,
						  t_bunny_area		*cur,
						  double		speed)
{
  scream_log_if("%p prev, %p cur, %f speed", "camera", prev, cur, speed);
  bunny_smooth_move((const t_bunny_position*)prev, (t_bunny_position*)cur, speed);
}

