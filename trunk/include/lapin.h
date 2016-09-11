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

