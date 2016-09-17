/*
** Jason Brillante "Damdoshi"
** Hanged Bunny Studio 2014-2016
**
** Bibliotheque Lapin
*/

/*
**
**             XXX                                                  XX
**             XXX                                                  XX
**           XX                                                       XXX
**        XXX                                                            XX
**        XXX                                                            XX
**      XX                                                                 XXX
**      XX                                                                 XXX
**      XX                                                                 XXX
**    XX                                                                      XX
**    XX                                                                      XX
**    XX                                                                      XX
**    XX                                                                      XX
**    XX                                                                      XX
** XX                                                                           XXX
** XX                                                                           XXX
** XX                                                                           XXX
** XX                            :|               |:|                           XXX
** XX                            :|               |::                           XXX
**    XX                  XX  |::::::|          |:::::|   XX                  XX
**                        XX     :|               |:|     XX
**                        XX     :|               |::     XX
**                        XX                              XX
**                        XX                              XX
**                        XX                              XX
**                          XX                         XXX
**                          XX                         XXX
**
**                            XXXXXXXXXXXXXXXXXXXXXXXXX
**                            XXXXXXXXXXXXXXXXXXXXXXXXX
**                          XXXXXXXXXXXXXXXXXXXXXXXXXXXXXX
**      XX               XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX               XX
**      XX                XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX               XXX
**      XX   ||     |||   XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX   ||     |||  XXX
**      XX   ||     |||  XX XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX    ||     |||  XXX
**      XX   ||     |||     XXXXXXXXXXXXXXXXXXXXXXXXXXXXXX     ||     |||  XXX
**      XX   |||||  |||       XXXXXXXXXXXXXXXXXXXXXXXXX        ||   |||||  XXX
**      XX   |||||  |||       XXXXXXXXXXXXXXXXXXXXXXXXX        ||   |||||  XXX
**      XX          |||       XXXXXXXXXXXXXXXXXXXXXXXXX        ||          XXX
**      XX|||||                  XXXXXXXXXXXXXXXXXXXX                 |||||XXX
**      XX|||||                  XXXXXXXXXXXXXXXXXXXX                 |||||XXX
**      XX   ||                  XXXXXXXXXXXXXXXXXXXX                 |||  XXX
**      XX   ||                  XXXXXXXXXXXXXXXXXXXX                 ||X  XXX
**      XX                       XXXXXXXXXXXXXXXXXXXX                      XXX
**        XXX                    XXXXXXXXXXXXXXXXXXXX                    XX
**        XXX                    XXXXXXXXXXXXXXXXXXXX                    XX
**        XXX               ||        XXXXXXXXXX       |||               XX
**           XX                                                       XXX
**           XX                                                       XXX
**             XXXXXXXXXX                                   XXXXXXXXXX
**             XXXXXXXXXX                                   XXXXXXXXXX
*/

/*!
** \mainpage
** Welcome on the Bunny Library (LibLapin) home page.
**
** This library is designed to be fast to deploy and use: using callbacks and
** easy usage graphical and sound elements, the LibLapin is efficient
** when you wish to create a prototype of a game or any graphic application.
**
** CPU and GPU computation are supported thanks to two types (t_bunny_pixelarray and t_bunny_picture)
** and allow you to choose whatever you need.
**
** The LibLapin is designed with holes that are supposed to
** be filled by users through programming exercises on the website
** called "La Caverne Aux Lapins Noirs" which is currently unavailable.
**
** Today, the LibLapin is used by Hanged Bunny Studio to
** participate to game jam like Ludum Dare.
**
** Join our forum on: http://hangedbunny.forumactif.org/
*/

#ifndef				__LAPIN_H__
# define			__LAPIN_H__
# include			<math.h>
# include			<stdbool.h>
# include			<stdint.h>
# include			<stdlib.h>

/*!
** LAPIN_MAJOR_VERSION expands into an integer that contains the current version of the library
*/
# define			LAPIN_MAJOR_VERSION	1
/*!
** LAPIN_MINOR_VERSION expands into an integer that contains the current revision of the library
*/
# define			LAPIN_MINOR_VERSION	10

# ifdef				__cplusplus
#  include			"lapin/cpp_guard.hpp"
# endif

# include			"lapin/enum.h"
# include			"lapin/self_test.h"
# include			"lapin/color.h"
# include			"lapin/allocator.h"
# include			"lapin/placement.h"
# include			"lapin/buffer.h"
# include			"lapin/window.h"
# include			"lapin/graphics.h"
# include			"lapin/events.h"
# include			"lapin/configuration.h"
# include			"lapin/sound.h"
# include			"lapin/network.h"
# include			"lapin/threads.h"
# include			"lapin/hardware.h"
# include			"lapin/self_test.h"
# include			"lapin/misc.h"

# include			"lapin/compat.h"

# ifdef				__cplusplus
#  include			"lapin/cpp_guard_end.hpp"
# endif
#endif	/*			__LAPIN_H__					*/

