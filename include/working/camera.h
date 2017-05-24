/*
**
**
**
**
**
*/

#ifndef			__LAPIN_EYE_H__
# define		__LAPIN_EYE_H__
# include		<lapin.h>

typedef void		t_bunny_camera;
typedef void		t_bunny_capture;

t_bunny_camera		*bunny_new_camera(int					cam_id);
void			bunny_delete_camera(t_bunny_camera			*camera);

t_bunny_capture		*bunny_new_capture(t_bunny_camera			*camera);
void			bunny_delete_capture(t_bunny_capture			*capture);
void			bunny_capture_get_size(const t_bunny_capture		*capture,
					       t_bunny_position			*out);

t_bunny_pixelarray	*bunny_capture_new_pixelarray(const t_bunny_capture	*capture);
t_bunny_picture		*bunny_capture_new_picture(const t_bunny_capture	*capture);

bool			bunny_capture_to_pixelarray(t_bunny_camera		*camera,
						    t_bunny_pixelarray		*pix);
bool			bunny_capture_to_picture(t_bunny_camera			*camera,
						 t_bunny_picture		*pic);

bool			bunny_camera_headtrack(const t_bunny_capture		*capture,
					       t_bunny_area			*head);

#endif	/*		__LAPIN_EYE_H__	*/
