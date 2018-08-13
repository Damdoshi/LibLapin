// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2016
//
// Lapin library

#include	"steam_api.h"
#include	"lapin_private.h"

void		bunny_steam::OnGameOverlayActivated(GameOverlayActivated_t *d)
{
  if (this->overlay)
    this->overlay(d->m_bActive ? GO_UP : GO_DOWN, gl_loop_data);
}

