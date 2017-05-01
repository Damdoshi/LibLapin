# Change log

# [Tag]
# Section
## Subsection
- Entry

## 1.11
### Add & Edit
- bunny_text module, bringing a t_bunny_font structure derived from clipable that cna
  handle png fonts and ttf font the same way. bunny_load_font allow to create those.
  A t_bunny_font is a textbox like object with formating options.
- bunny_draw can handle t_bunny_font (and is **required**)
- bunny_blit can handle t_bunny_font as source and also as target
- bunny_set_* functions can draw on t_bunny_font

- bunny_configuration module, that can load and save in different formats (currently
  INI and DABSIC) and allow a deep exploration of all of those the same way.
- bunny_read_ini and bunny_write_ini to read and write ini from memory and not
  only from file.
- bunny_ini_field_count
- **bunny_ini module is deprecated**

- bunny_security module that can cipher data with different algorithms *only to
  prevent users from modifying file configuration, not for real security!*
- bunny_hash module to compute hash with different algorithms without having to
  install an external dependencie.
- bunny_load_file and bunny_save_file to load and save data from and to a file
- bunny_thread_push to add a single task into a bunny_threadpool.
- bunny_stack
- bunny_astack (stack on stack, fully alloca allocated)
- bunny_queue
- bunny_list
- bunny_vector
- bunny_map
- bunny_bitfield
- bunny_pool, array of fixed size with fast in/out operations
- bunny_evaluate that handle mathematical expression and operators +-*/%<><=>= == != () and ?:.
  *The bunny_evaluate functions takes an configuration as variable environment, but it is
  currently ignored.*
- bunny_circular_collision_dot, bunny_circular_collision, bunny_rectangular_collision_dot,
  bunny_rectangular_collision, bunny_triangle_collision_dot, bunny_quad_collision_dot
- network event in bunny_loop
- bunny_popen, bunny_pclose
- Skip the display step if the main loop was too slow
- ANTIALIASING flag for t_bunny_window_style
- LAPIN_ALLOCATOR_DEACTIVATED can now be used while compiling the bunny library.
- BUNNY_ALLOCATOR_* are alias on LAPIN_ALLOCATOR_* macros

### Fix
- Texture in bunny_geomtry now works

### Misc
- Unit test directory. All containers are tested, with an exception for their threaded foreach.
- Better organization from private headers
- Cleaner root directory
- Geosquare as misc example for collision module



## 1.10
### Add & Edit
- Remove basic.h, advanced.h & extra.h to organize functions around themes instead.

### Misc
- Fully documented
- New makefile
- Simple project template



## 1.9.1
### Add & Edit
- bunny_get_screen_resolution replace bunny_get_screen_size
- bunny_strnlen (for windows)

### Fix
- Threading library is not threaded on Window, but compile now.

### Misc
- Codeblock project for Windows



## 1.9
### Add & Edit
- lapin/extra.h and lapin/extra_type.h.
- bunny_server_* & bunny_client_* for network program in extra.h
- bunny_thread in extra.h to bring threadpool
- bunny_hardware in extra.h to control a pvm110n from velleman.
- bunny_move_window and bunny_resize_window
- bunny_get_screen_size

### Fix
- Check the malloc called for bunny allocator.

### Misc
- Additional demos for shader, window resize, network, thread pool and hardware.

## 1.8
### Add & Edit
- DEFAULT_SCOPE for INI module.
- A color field in t_bunny_clipable for masking color.
- The bunny_new_pixelarray can now identify when the program is started by the technocore and create
  a fake pixelarray instead of the classic one. (The technocore is an automatic evaluation system)
- When an altered memory chunk is discovered, it screams on stderr.
- bunny_set_circle
- bunny_ini_first_scope is an alias of bunny_ini_first which is deprecated.
- bunny_ini_next_scope is an alias of bunny_ini_next which is deprecated.
- bunny_ini_first_field, bunny_ini_field_name, bunny_ini_next_field, bunny_field_get_value,
  bunny_field_set_value, LAST_FIELD & t_bunny_ini_field.
- bunny_ini_get_scope
- bunny_self_test which test gl_bunny_my_* functions for cpu pictures again gpu pictures functions.
- t_bunny_size

### Fix
- Fix the bunny_save_pixelarray prototype that was wrong, making the function not available.
- Fix the segmentation fault in the INI error handling. *(Discovered by clients)*



## 1.7
### Add & Edit
- Split lapin.h into two files: lapin/basic.h and lapin/advanced.h
- t_bunny_sound, t_bunny_effect and t_bunny_music are now real types. **This breaks compatiblity**
- You can now generate sound from your program.
- bunny_set_display_function that will avoid multiple refresh when your program is late.
  Use this function to display, and not the function sent to bunny_set_loop_main_function anymore.
  The loop function is now made for inside mechanics only.
- bunny_resize_response to handle window resize event. bunny_loop_mw to handle multiple
  windows and bunny_get_window to get the current window.
- bunny response for getting and losing focus.
- bunny response for window close, for program with multiple windows only.
- bunny_set_maximum_ram takes the maximum amount of bytes that bunny allocator can delivered.
  Must be called at the very beginning.
- bunny allocator is now aggressive with buffer overflow.
- bunny_set_geometry to draw shapes from coordinates.

### Removal
- Remove the automatic anti aliasing.
- No more vsync configuration.
- Remove of the C++ specific functions that was useless. The lapin headers are C++ proof.



## 1.6.3
### Fix
- Conflit between the clic and mouse event that turn into invalid values in associated
  callbacks.

## 1.6.2
### Add & Edit
- bunny_save_pixelarray to save a pixelarray into a file

### Fix
- bunny_set_mouse_position
- bunny_set_mouse_visiblity
- Better sleep delay in bunny_loop
- bunny_set_context

## 1.6
### Add & Edit
- bunny_set_mouse_position_window, bunny_set_mouse_position that allow to set the
  mouse position on window or on screen.
- bunny_set_mouse_visiblity to hide or display mouse cursor.
- bunny_request_focus that ask the focus on the given window to the system, that
  can refuse.
- t_bunny_transform become t_bunny_accurate_position. **This breaks compatibility!**
- The new t_bunny_transform is now a structure that contains transformation information
  for shaders.
- bunny_is_shader_available, bunny_blit_shader, bunny_new_shader, bunny_delete_shader,
  bunny_load_shader, bunny_shader_set_variable to use shaders in bunny library.
- bunny_set_key_repeat to activate/deactivate key repetition.

### Fix
- bunny_ini_scope_get_field now works
- bunny_blit from a gpu pictures to a pixelarray was not really fixed. Now it is.

### Misc
- Switch from distributed binary of SFML to 2.3.2 source to avoid the sf::String
  valgrind error that makes the program crash on some architectures.

## 1.5.1
### Fix
- Field t_bunny_window.name is now constant and pointed bytes are constant too.
- Field t_bunny_pixelarray.pixels is now constant but pointer pixels are not.

## 1.5
### Add & Edit
- bunny_set_context & bunny_get_context to load and save all events callback in one shot.
- bunny_ini_first, bunny_ini_scope_name, bunny_ini_next, bunny_ini_scope_get_field &
  buny_ini_scope_set_field to allow to browse scopes inside a INI file without having
  to know them before with a t_bunny_ini_scope.
- bunny_set_joy_axis_response, bunny_set_joy_button_response, bunny_set_joy_connect_response,
  bunny_get_joy_button, bunny_get_joy_axis. Those functions handle joystick events.
  The t_bunny_axis enum and the t_bunny_joystick structure were also added.
- bunny_set_wheel_response that handle the mouse wheel event
- CONNECTED & DISCONNECTED state added in t_bunny_event_state.
- gl_vector font and associated types that contains coordinates for creating a vector font.
- x_origin, y_origin, x_scale, y_scale and rotation added in t_bunny_clipable.
- The INI loader knows how to handle commentaries with '#'.

### Fix
- Add several const
- The main loop now sleeps instead of asking the time aggressively
- BKS_SUBSTRACT become BKS_SUBTRACT
- bunny_blit can now blit well gpu pictures on cpu pictures.

### Misc
- Add a font.png file, that contains a low res font.
- Add a joystick_panel program that is useful to test joysticks.



## 1.4
### Add & Edit
- Add a mod attribute in the t_color union, that is an array of signed char. Useful to
  create color offsets.



## 1.3
### Add & Edit
- bunny_start_style that allows window style definition.
- Use int instead of unsigned int in picture size and configuration.



## 1.2 -
### Add & Edit
- bunny_malloc, bunny_free_, bunny_calloc and bunny_realloc that provides a custom
  allocator that can be limited and monitored with specific tools.
- LAPIN_ALLOCATOR_DEACTIVATED delete all calls to bunny allocator.
- LAPIN_ALLOCATOR_OVERLOAD transform all calls to standard allocator to calls to
  bunny allocator
- Add an enum for keys



## 1.1 - 2016-06-17
### Add & Edit
- Function pointers that can be set to complete some bunny functions and make them
  work on t_bunny_pixelarray.
- New pictures are now pink by default

### Fix
- bunny_fill works now on gpu pictures
- Better color constant, to have the same effect on cpu and gpu pictures
- bunny_blit now blits well from cpu picture go gpu picture



## 1.0 - 2015-03-01
### The Bunny Library is a graphic library that brings the following things:
- Graphic programming pixel-per-pixel throught CPU
- Graphic programming block-per-block throught GPU
- Ways to mix both
- Time locked loop with events callback

### The Bunny Library objectives are:
- Being simple and nice to use by bringing directly useful tools, easy and quick to work with.
- Being easy to explain and prevent most needs to go see the doc
- Allowing beginners to progress in graphic programming, but also in C programming.

[Tag]: url
