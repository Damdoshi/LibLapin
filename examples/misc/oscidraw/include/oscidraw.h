/*
** *****************************************************************************
** damdoshi <damdoshi@eliminator>
** EFRITS - 30/03/2024 10:57:26
**
** -  -
**
** *****************************************************************************
*/

#ifndef				__OSCIDRAW_H__
# define			__OSCIDRAW_H__
# include			<lapin.h>

# define			BOARDWIDTH			200
# define			BOARDHEIGHT			200
# define			RWIDTH				5
# define			RHEIGHT				30

typedef struct			s_ball
{
  t_bunny_accurate_position	pos;
  t_bunny_accurate_position	spe;
}				t_ball;

typedef struct			s_racket
{
  t_bunny_accurate_position	pos;
  double			height;
}				t_racket;

typedef struct			s_player
{
  t_racket			racket[4];
  size_t			nbr_racket;
}				t_player;

typedef struct			s_program
{
  t_bunny_window		*window;
  t_bunny_picture		*screen;
  t_bunny_vm110n		*card;
  t_bunny_position		pencil;
  t_ball			ball[10];
  size_t			nbr_ball;
  t_player      		player[2];
  bool				lifted;
  int				exchange;
}				t_program;



#endif	/*			__OSCIDRAW_H__	*/
