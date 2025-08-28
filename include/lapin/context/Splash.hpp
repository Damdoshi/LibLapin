/*
** Jason Brillante "Damdoshi"
** Hanged Bunny Studio 2014-2025
** EFRITS SAS 2022-2025
** Pentacle Technologie 2008-2025
**
** Bibliotheque Lapin
*/

#ifndef				__LAPIN_SPLASH_HPP__
# define			__LAPIN_SPLASH_HPP__
# if				!defined(__LAPIN_H__)
#  error			You cannot include this file directly.
# endif

namespace			hbs
{
  class				HangedBunnyStudioSplashScreen : public s_bunny_splash_screen, public hbs::ContextBridge<HangedBunnyStudioSplashScreen>
  {
    bool			man_alloc = false;

    char			*stringdup(const std::string	&str)
    {
      return (bunny_strdup(str.c_str()));
    }

  public:
    void			Load(t_bunny_buffer		**buffer,
				     const std::string		&dir)
    {
      if (man_alloc)
	Unload();
      *static_cast<t_bunny_context*>(this) = gl_bunny_splash_context;
      memset(&head, 0, sizeof(head));
      head.main_structure = (void*)this;
      head.screens = buffer;
      for (head.nbr_screen = 0; buffer[head.nbr_screen]; ++head.nbr_screen);
      bunny_picture_file = stringdup(dir + "/bunny.dab");
      rope_picture_file = stringdup(dir + "/rope.dab");
      title_picture_file = stringdup(dir + "/title.dab");
      jingle_sound_file = stringdup(dir + "/jingle.dab");
      boom_sound_file = stringdup(dir + "/boom.dab");
      outch_sound_file = stringdup(dir + "/outch.dab");
      falling_sound_file = stringdup(dir + "/falling.dab");
      man_alloc = true;
    }
    void			Load(t_bunny_buffer		**buffer)
    {
      Load(buffer, "./res/splash");
    }
    
    void			Unload(void)
    {
      bunny_free(bunny_picture_file);
      bunny_free(rope_picture_file);
      bunny_free(title_picture_file);
      bunny_free(jingle_sound_file);
      bunny_free(boom_sound_file);
      bunny_free(outch_sound_file);
      bunny_free(falling_sound_file);
      man_alloc = false;
    }

    HangedBunnyStudioSplashScreen(void)
    {}
    HangedBunnyStudioSplashScreen(t_bunny_buffer		**buffer,
				  const std::string		&dir)
    {
      Load(buffer, dir);
    }
    HangedBunnyStudioSplashScreen(t_bunny_buffer		**buffer)
    {
      Load(buffer);
    }
    HangedBunnyStudioSplashScreen(const t_bunny_splash_screen	&conf)
    {
      *static_cast<t_bunny_context*>(this) = gl_bunny_splash_context;
      *static_cast<t_bunny_splash_screen*>(this) = conf;
    }
    ~HangedBunnyStudioSplashScreen(void)
    {
      Unload();
    }
  };
}

#endif	/*			__LAPIN_SPLASH_HPP__		*/
