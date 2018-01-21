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

/*!
** t_bunny_camera represent a video device linked with your computer.
*/
typedef void		t_bunny_camera;

/*!
** A t_bunny_capture is a frame retrieved from a t_bunny_camera.
*/
typedef void		t_bunny_capture;

/*!
** Switch on the video device associated on your computer with the sent cam_id.
** In most case, 0 is your built-in webcam if your computer have one.
** \param cam_id The id of the video device you want to switch on
** \return A t_bunny_camera pointer that represent the opened device or NULL
**         on error.
*/
t_bunny_camera		*bunny_new_camera(int				cam_id);

/*!
** Close the sent video device.
** \param camera The opened video device.
*/
void			bunny_delete_camera(t_bunny_camera		*camera);

/*!
** Create and capture a video frame from the sent opened camera.
** \param camera The camera you want to capture a frame from
** \return A frame that can be transformed in pixelarray, picture or informations
**         about any face capture. NULL on error.
*/
t_bunny_capture		*bunny_new_capture(t_bunny_camera		*camera);

/*!
** Delete a capture.
** \param capture The capture to delete
*/
void			bunny_delete_capture(t_bunny_capture		*capture);

/*!
** Get the size in pixel of the sent capture.
** \param capture A frame from the video device
** \param out An t_bunny_position in which the function will store the size
**            of the capture.
*/
void			bunny_capture_get_size(const t_bunny_capture	*capture,
					       t_bunny_size		*out);

/*!
** Capture a video frame from the sent device and store it in the sent capture.
** \param camera The camera that will be used to capture a frame.
** \param capture The capture where the frame will be stored.
*/
void			bunny_capture(t_bunny_camera			*camera,
				      t_bunny_capture			*capture);

/*!
** Create a pixelarray with the same size of the sent capture and return it.
** \param capture A capture.
** \return A pixelarray that contains the same graphics as the capture. NULL on error.
*/
t_bunny_pixelarray	*bunny_capture_new_pixelarray(const t_bunny_capture *capture);

/*!
** Create a picture with the same size of the sent capture and return it.
** This function create a pixelarray as intermediate state, so it is slower than
** bunny_capture_new_pixelarray.
** \param capture A capture.
** \return A picture that contains the same graphics as the capture. NULL on error.
*/
t_bunny_picture		*bunny_capture_new_picture(const t_bunny_capture *capture);

/*!
** Store inside the sent pixelarray graphics from the sent capture.
** The picture will be stretched to fit the pixelarray size.
** \param cap A capture
** \param pix The pixelarray where to store the graphics from the capture
** \return True if the operation was successful
*/
bool			bunny_capture_to_pixelarray(t_bunny_capture	*cap,
						    t_bunny_pixelarray	*pix);

/*!
** Store inside the sent picture graphics from the sent capture.
** The picture will be stretched to fit the picture size.
** This function create a pixelarray as intermediate state, so it is slower than
** bunny_capture_to_pixelarray.
** \param cap A capture
** \param pic The picture where to store the graphics from the capture
** \return True if the operation was successful
*/
bool			bunny_capture_to_picture(t_bunny_capture	*cap,
						 t_bunny_picture	*pic);

/*!
** Analyse the capture to find a face.
** \param capture A capture from a video device
** \param head An area in which the fade coordinates will be stored
** \return True if the operation was successful
*/
bool			bunny_camera_headtrack(const t_bunny_capture	*capture,
					       t_bunny_area		*head);


/*!
** Smooth the movement of the detected face in case of the watcher is shaking his
** head or move it too quickly to have a decent headtrack.
** This function is based on bunny_smoth_move in the misc module.
** \param previous The previous position of the face. After calling this function,
** you should consider current as previous for the next call.
** \param current The current position of the face, just retrieved from bunny_camera
** headttrack.
** \param speed The speed, between 0 and 1, in percentage of distance between the
** previous and the current position of the face.
*/
void			bunny_stabilize_headtrack(const t_bunny_area	*previous,
						  t_bunny_area		*current,
						  double		speed);

#endif	/*		__LAPIN_EYE_H__	*/

