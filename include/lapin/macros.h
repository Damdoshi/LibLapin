/*
** Jason Brillante "Damdoshi"
** Hanged Bunny Studio 2014-2016
**
** Bibliotheque Lapin
*/

/*!
** \file macros.h
** Contains shorter names for liblapin
*/

#ifndef			__LAPIN_MACROS_H__
# define		__LAPIN_MACROS_H__
# if			!defined(__LAPIN_H__)
#  error		You cannot include this file directly.
# endif

/*!
** For those who don't type fast.
*/

  /*                             */
 /*     BUNNY ALLOCATOR         */
/*                             */

# define bal_malloc(siz) bunny_malloc(siz)
# define bal_calloc(num, siz) bunny_calloc(num, siz)
# define bal_realloc(ptr, siz) bunny_realloc(ptr, siz)
# define bal_free(ptr) bunny_free(ptr)
# define bal_set_mem_check(chk) bunny_set_memory_check(chk)
# define bal_set_max_ram(byt) bunny_set_maximum_ram(byt)

  /*                             */
 /*     BUNNY ASYNCLOCK         */
/*                             */

# ifndef NO_TYPE_MACRO
#  define t_call_order t_bunny_call_order
#  define t_trap_function t_bunny_trap_function
#  define t_trap t_bunny_trap
# endif
# define bas_trap(func, order, stime, dur, par) bunny_new_trap(func, order, stime, dur, par)
# define bas_del_trap(trap) bunny_delete_trap(trap)
# define bas_asynclock(elap, order) bunny_assynclock(elap, order)
# define bas_reset_clock() bunny_reset_clock()
# define bas_current_time() bunny_get_current_time()

  /*                             */
 /*     BUNNY BUFFER            */
/*                             */

# ifndef NO_TYPE_MACRO
#  define t_buffer t_bunny_buffer
# endif

  /*                             */
 /*     BUNNY COLLIDE           */
/*                             */

# define bcol_circle_dot(elem, dot, rad) bunny_circle_collision_dot(elem, dot, rad)
# define bcol_circle(a, r1, b, r2) bunny_circle_collision
# define bcol_rect_dot(a, b) bunny_rectangular_collision_dot(a, b)
# define bcol_rect(a, b) bunny_rectangular_collision(a, b)
# define bcol_triangle_dot(a, b) bunny_triangle_collision_dot(a, b)
# define bcol_quad_dot(a, b) bunny_quad_collision_dot(a, b)

  /*                             */
 /*     BUNNY COLOR             */
/*                             */

# ifndef NO_TYPE_MACRO
#  define t_rgb t_bunny_rgb
#  define t_color t_bunny_color
# endif

  /*                             */
 /*     BUNNY CONFIGURATION     */
/*                             */

# ifndef NO_TYPE_MACRO
#  define t_configuration t_bunny_configuration
#  define t_read_confifugration t_bunny_my_read_configuration
#  define gl_read_configuration gl_bunny_my_read_configuration
#  define t_write_confifugration t_bunny_my_write_configuration
#  define gl_write_configuration gl_bunny_my_write_configuration
# endif

# define bc_conf() bunny_new_configuration()
# define bc_load_conf(t, f, c) bunny_load_configuration(t, f, c)
# define bc_save_conf(t, f, c) bunny_save_configuration(t, f, c)
# define bc_read_conf(t, cd, cn) bunny_read_configuration(t, cd, cd)
# define bc_write_conf(t, c) bunny_write_configuration(t, c)
# define bc_del_conf(c) bunny_delete_configuration(c)
# define bc_create_mode(b) bunny_configuration_create_mode(b)

# define bc_get_parent(c) bunny_configuration_get_parent(c)
# define bc_get_name(c) bunny_configuration_get_name(c)
# define bc_get_child(cnf, c) bunny_configuration_get_child(cnf, c)
# define bc_get_case(cnf, i) bunny_configuration_get_case(cnf, i)
# define bc_get_string(cnf, str) bunny_configuration_get_string(cnf, str)
# define bc_get_double(cnf, val) bunny_configuration_get_double(cnf, val)
# define bc_get_int(cnf, val) bunny_configuration_get_int(cnf, val)
# ifdef __STDC__
#   ifdef __STDC_VERSION__
#    if __STDC_VERSION__ >= 199901L
#     define bc_go_get_node_va(cnf, nbr, ...) bunny_configuration_get_node_va(cnf, nbr, __VA_ARGS__)
#     define bc_go_get_string_va(c, v, n, ...) bunny_configuration_go_get_string_va(c, v, n, __VA_ARGS__)
#     define bc_go_get_double_va(c, v, n, ...) bunny_configuration_go_get_double_va(c, v, n, __VA_ARGS__)
#     define bc_go_get_int_va(c, v, n, ...) bunny_configuration_go_get_int_va(c, v, n, __VA_ARGS__)
#    endif
#   endif
# endif

# define bc_set_string(cnf, str) bunny_configuration_set_string(cnf, str)
# define bc_set_double(cnf, val) bunny_configuration_set_double(cnf, val)
# define bc_set_int(cnf, val) bunny_configuration_set_int(cnf, val)
# ifdef __STDC__
#   ifdef __STDC_VERSION__
#    if __STDC_VERSION__ >= 199901L
#     define bc_go_set_string_va(c, v, n, ...) bunny_configuration_go_set_string_va(c, v, n, __VA_ARGS__)
#     define bc_go_set_double_va(c, v, n, ...) bunny_configuration_go_set_double_va(c, v, n, __VA_ARGS__)
#     define bc_go_set_int_va(c, v, n, ...) bunny_configuration_go_set_int_va(c, v, n, __VA_ARGS__)
#    endif
#   endif
# endif

# define bc_first(c) bunny_configuration_first(c)
# define bc_next(c) bunny_configuration_next(c)
# define bc_end(c) bunny_configuration_end(c)

  /*                             */
 /*     BUNNY DATABASE          */
/*                             */

  /*                             */
 /*     BUNNY ENUM              */
/*                             */

# ifndef NO_TYPE_MACRO
#  define LAST_BUTTON LAST_BUNNY_BUTTON
#  define LAST_JOYSTICK LAST_BUNNY_JOYSTICK
#  define t_axis t_bunny_axis
#  define t_mouse_button t_bunny_mouse_button
#  define t_keysym t_bunny_keysym
#  define t_letter_tab t_bunny_letter_tab
# endif

  /*                             */
 /*     BUNNY EVENTS            */
/*                             */

# ifndef NO_TYPE_MACRO
#  define t_response t_bunny_response
#  define t_event_state t_bunny_event_state
#  define t_key t_bunny_key
#  define t_type t_bunny_type
#  define t_click t_bunny_click
#  define t_move t_bunny_move
#  define t_wheel t_bunny_wheel
#  define t_joystick t_bunny_joystick
#  define t_joy_connect t_bunny_joy_connect
#  define t_joy_axis t_bunny_joy_axis
#  define t_joy_button t_bunny_joy_button
#  define t_get_focus t_bunny_get_focus
#  define t_lost_focus t_bunny_lost_focus
#  define t_resisze t_bunny_resize
#  define t_close t_bunny_close
#  define t_display t_bunny_display
#  define t_loop t_bunny_loop
#  define t_context t_bunny_context
#  define t_acontext t_bunny_anonymous_context
# endif
# define bev_key_handler(a) bunny_set_key_response(a)
# define bev_text_handler(a) bunny_set_text_response(a)
# define bev_click_handler(a) bunny_set_click_response(a)
# define bev_get_mouse_button() bunny_get_mouse_button()
# define bev_move_handler(a) bunny_set_move_response(a)
# define bev_get_mouse_position() bunny_get_mouse_position()
# define bev_wheel_handler(a) bunny_set_wheel_response(a)
# define bev_joy_connect_handler(a) bunny_set_joy_connect_response(a)
# define bev_get_joy_info(id) bunny_get_joy_info(id)
# define bev_joy_axis_handler(a) bunny_set_joy_axis_response(a)
# define bev_get_joy_axis() bunny_get_joy_axis()
# define bev_joy_button_handler(a) bunny_set_joy_button_response(a)
# define bev_get_joy_button() bunny_get_joy_button()
# define bev_get_focus_handler(a) bunny_set_get_focus_response(a)
# define bev_set_lost_focus_handler(a) bunny_set_lost_focus_response(a)
# define bev_resize_handler(a) bunny_set_resize_response(a)
# define bev_close_handler(a) bunny_set_close_response(a)
# define bev_get_window() bunny_get_window()
# define bev_display_handler(a) bunny_set_display_function(a)
# define bev_main_loop(a) bunny_set_loop_main_function(a)
# define bev_loop(a, b, c) bunny_loop(a, b, c)
# define bev_loop_mw(a, b, c, d) bunny_loop_mw(a, b, c, d)
# define bev_context(a) bunny_set_context(a)
# define bev_get_context(a) bunny_get_context(a)

  /*                             */
 /*     BUNNY GRAPHICS          */
/*                             */

# ifndef NO_TYPE_MACRO
#  define t_clipable t_bunny_clipable
#  define t_pixelray t_bunny_pixelarray
#  define t_load_pixelarray t_bunny_my_load_pixelarray
#  define t_read_pixelarray t_bunny_my_read_pixelarray
#  define gl_load_pixelarray gl_bunny_my_load_pixelarray
#  define gl_read_pixelarray gl_bunny_my_read_pixelarray
#  define t_picture t_bunny_picture
#  define t_blit t_bunny_my_blit
#  define gl_blit gl_bunny_my_blit
#  define t_set_pixel t_bunny_my_set_pixel
#  define gl_set_pixel gl_bunny_my_set_pixel
#  define t_set_circle t_bunny_my_set_circle
#  define gl_set_circle gl_bunny_my_set_circle
#  define t_set_line t_bunny_my_set_line
#  define gl_set_line gl_bunny_my_set_line
#  define t_set_polygon t_bunny_my_set_polygon
#  define gl_set_poylgon gl_bunny_my_set_polygon
#  define t_fill t_bunny_my_fill
#  define gl_fill gl_bunny_my_fill
#  define t_clear t_bunny_my_clear
#  define gl_clear gl_bunny_my_clear
#  define t_geometry t_bunny_geometry
#  define t_vertex t_bunny_vertex
#  define t_vertex_array t_bunny_vertex_array
#  define t_set_geometry t_bunny_my_geometry
#  define gl_geomtry gl_bunny_my_geometry
#  define t_vfont_line_coord t_bunny_vector_font_line_coord
#  define t_letter t_bunny_letter
#  define gl_vfont gl_vector_font
#  define t_shader t_bunny_shader
#  define t_vartype t_bunny_variable_type
#  define t_transform t_bunny_transform
# endif
# define bg_pixelarray(w, h) bunny_new_pixelarray(w, h)
# define bg_load_pixelarray(f) bunny_load_pixelarray(f)
# define bg_read_pixelarray(v) bunny_read_pixelarray(v)
# define bg_save_pixelarray(b, f) bunny_save_pixelarray(b, f)
# define bg_picture(w, h) bunny_new_picture(w, h)
# define bg_load_pic(f) bunny_load_picture(f)
# define bg_read_pic(p, l) bunny_read_picture(p, l)
# define bg_del_pic(c) bunny_delete_clipable(c)
# define bg_blit(a, b, c) bunny_blit(a, b, c)
# define bg_draw(a) bunny_draw(a)
# define bg_pixel(a, b, c) bunny_set_pixel(a, b, c)
# define bg_circle(a, b, c, d) bunny_set_circle(a, b, c, d)
# define bg_line(a, b, c) bunny_set_line(a, b, c)
# define bg_polygon(a, b, c) bunny_set_polygon(a, b, c)
# define bg_fill(a, b) bunny_fill(a, b)
# define bg_clear(a, b) bunny_clear(a, b)
# define bg_geometry(a, b, c, d) bunny_set_geometry(a, b, c, d)
# define bg_shader_available() bunny_is_shader_available()
# define bg_shader() bunny_new_shader()
# define bg_load_shader(a, b, c) bunny_load_shader(a, b, c)
# ifdef __STDC__
#   ifdef __STDC_VERSION__
#    if __STDC_VERSION__ >= 199901L
#     define bg_var_shader(a, b, c, ...) bunny_shader_set_variable(a, b, c, __VA_ARGS__)
#    endif
#   endif
# endif
# define bg_blit_shader(a, b, c, d) bunny_blit_shader(a, b, c, d)
# define bg_del_shader(a) bunny_delete_shader(a)
# define bg_full_blit(a) bunny_enable_full_blit(a)
# define bg_gl_reset(a) bunny_GL_reset_states(a)
# define bg_gl_push(a) bunny_GL_push_states(a)
# define bg_gl_pop(a) bunny_GL_pop_states(a)

  /*                             */
 /*     BUNNY HARDWARE          */
/*                             */

# ifndef NO_TYPE_MACRO
#  define t_hardware t_bunny_hardware
# endif
# define bh_hardware(id) bunny_new_hardware(id)
# define bh_del_hardware(hrd) bunny_delete_hardware(hrd)
# define bh_read(hrd) bunny_hardware_read(hrd)
# define bh_write(hrd) bunny_hardware_write(hrd)

  /*                             */
 /*     BUNNY HARDWARE          */
/*                             */

# ifndef NO_TYPE_MACRO
#  define t_hash t_bunny_hash
#  define t_my_hash t_bunny_hash
#  define gl_my_hash gl_bunny_my_hash
# endif
# define bh_hash(a, b, c) bunny_hash(a, b, c)

  /*                             */
 /*     BUNNY MISC              */
/*                             */

# define bm_printl(str) bunny_printl(str)
# define bm_printlerr(str) bunny_printlerr(str)
# define bm_errno bunny_errno
# define bm_strerror(e) bunny_strerror(e)
# define bm_perror(s) bunny_perror(s)
# define bm_load_file(f, d, s) bunny_load_file(f, d, s)
# define bm_save_file(f, d, l) bunny_save_file(f, d, l)
# define bm_eval(a, b) bunny_evaluate(a, b)

  /*                             */
 /*     BUNNY NETWORK           */
/*                             */

# ifndef NO_TYPE_MACRO
#  define t_comtype t_bunny_comtype
#  define t_comerror t_bunny_comerror
#  define t_error t_bunny_error
#  define t_comexpire t_bunny_expired
#  define t_comconnect t_bunny_connected
#  define t_comdisconnect t_bunny_disconnected
#  define t_message t_bunny_message
#  define t_communication t_bunny_communication
#  define t_server t_bunny_server
#  define t_client t_bunny_client
# endif
# define bn_server(p) bunny_new_server(p)
# define bn_del_server(p) bunny_delete_server(p)
# define bn_srv_poll(a, b) bunny_server_poll(a, b)
# define bn_srv_write(a, b, c, d) bunny_server_write(a, b, c, d)
# define bn_srv_packetok(a) bunny_server_packed_ready(a)
# define bn_srv_doom(a, b) bunny_server_doom_client(a, b)
# define bn_client(a, b) bunny_new_client(a, b)
# define bn_del_client(a) bunny_delete_client(a)
# define bn_clt_poll(a, b) bunny_client_poll(a, b)
# define bn_clt_write(a, b, c) bunny_client_write(a, b, c)

  /*                             */
 /*     BUNNY PLACEMENT         */
/*                             */

# ifndef NO_TYPE_MACRO
#  define t_position t_bunny_position
#  define t_2d t_bunny_position
#  define t_size t_bunny_size
#  define t_fposition t_bunny_accurate_position
#  define t_2df t_bunny_accurate_position
#  define t_fsize t_bunny_accurate_size
#  define t_area t_bunny_area
#  define t_farea t_bunny_accurate_area
# endif

  /*                             */
 /*     BUNNY PLUGIN            */
/*                             */

  /*                             */
 /*     BUNNY SECURITY          */
/*                             */

# ifndef NO_TYPE_MACRO
#  define t_ciphering t_bunny_ciphering
#  define gl_ciphering gl_bunny_ciphering_table
#  define t_cipher_key t_bunny_cipher_key
#  define t_key_twist t_bunny_key_twist
#  define gl_key_twist gl_bunny_my_key_twist
#  define t_cipher t_bunny_my_cipher
#  define gl_cipher gl_bunny_my_cipher
#  define t_uncipher t_bunny_my_uncipher
#  define gl_uncipher gl_bunny_my_uncipher
# endif
# define bs_get_cipher_name(a) bunny_get_ciphering(a)
# define bs_fill_defkey(a, b) bunny_fill_default_key(a, b)
# define bs_key(a) bunny_new_key(a)
# define bs_del_key(a) bunny_delete_key(a)
# define bs_cipher_file(a, b, c) bunny_cipher_file(a, b, c)
# define bs_uncipher_file(a, b, c) bunny_uncipher_file(a, b, c)
# define bs_cipher_data(a, b, c, d) bunny_cipher_data(a, b, c, d)
# define bs_uncipher_data(a, b, c, d) bunny_uncipher_data(a, b, c, d)

  /*                             */
 /*     BUNNY SOUND             */
/*                             */

# ifndef NO_TYPE_MACRO
#  define t_sound t_bunny_sound
#  define t_music t_bunny_music
#  define t_sfx t_bunny_effect
# endif
# define bs_load_music(a) bunny_load_music(a)
# define bs_sfx(a) bunny_new_effect(a)
# define bs_load_sfx(a) bunny_load_effect(a)
# define bs_save_sfx(a, b) bunny_save_effect(a, b)
# define bs_compute_sfx(a) bunny_compute_effect(a)
# define bs_sound_vol(a, b) bunny_sound_volume(a, b)
# define bs_sound_pitch(a, b) bunny_sound_pitch(a, b)
# define bs_sound_loop(a, b) bunny_sound_loop(a, b)
# define bs_sound_pos(a, b, c, d) bunny_sound_position(a, b, c, d)
# define bs_play(a) bunny_sound_play(a)
# define bs_stop(a) bunny_sound_stop(a)
# define bs_get_cursor(a) bunny_music_get_cursor(a)
# define bs_del_sound(a) bunny_delete_sound(a)

  /*                             */
 /*     BUNNY SOUND             */
/*                             */

# ifndef NO_TYPE_MACRO
#  define t_threadpool t_bunny_threadpool
#  define t_function t_bunny_function
# endif
# define bt_threadpool(nbr) bunny_new_thredapool(nbr)
# define bt_del_threadpool(p) bunny_delete_threadpool(p)
# define bt_foreach(a, b, c, d, e, f) bunny_thread_foreach(a, b, c, d, e)
# define bt_wait(p) bunny_thread_wait_completion(p)

  /*                             */
 /*     BUNNY WINDOW            */
/*                             */

# ifndef NO_TYPE_MACRO
#  define t_window t_bunny_window
#  define t_win_style t_bunny_window_style
# endif
# define bw_start(a, b, c, d) bunny_start(a, b, c, d)
# define bw_stop(a) bunny_stop(a)
# define bw_display(a) bunny_display(a)
# define bw_resolution() bunny_get_screen_resolution()
# define bw_start_style(a, b, c, d) bunny_start_style(a, b, c, d)
# define bw_key_repeat(a, b) bunny_set_key_repeat(a, b)
# define bw_mouse_hide(a, b) bunny_set_mouse_visibility(a, !b)
# define bw_mouse_winpos(a, b, c) bunny_set_mouse_position_window(a, b, c)
# define bw_mouse_pos(a, b) bunny_set_mouse_position(a, b)
# define bw_focus(a) bunny_request_focus(a)
# define bw_move(a, b) bunny_move_window(a, b)
# define bw_resize(a, b) bunny_resize_window(a, b)

#endif /*		__LAPIN_MACROS_H__			*/

