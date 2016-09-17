/*
** Jason Brillante "Damdoshi"
** Hanged Bunny Studio 2014-2016
**
** Bibliotheque Lapin
*/

/*!
** \file self_test.h
** This header contains the bunny_self_test function that is useful to test your drawing functions.
*/

#ifndef				__LAPIN_SELF_TEST_H__
# define			__LAPIN_SELF_TEST_H__
# if				!defined(__LAPIN_H__)
#  error			You cannot include this file directly.
# endif

/*!
** Test if functions set to gl_bunny_my_* function pointers are valid as
** perfect equivalent for t_bunny_pixelarray to bunny_set_* functions for
** t_bunny_picture.
*/
void				bunny_self_test(void);

#endif	/*			__LAPIN_SELF_TEST_H__				*/
