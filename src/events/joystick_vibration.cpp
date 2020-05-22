// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2020
//
// Bibliotheque Lapin

#include		"lapin_private.h"

#ifdef			__WIN32
# include		<windows.h>
# include	        <XInput.h>
#else
# include		<linux/joystick.h>
# include		<fcntl.h>
# include		<libudev.h>
#endif

struct ff_effect	gl_effect[sf::Joystick::Count];

bool			bunny_set_joystick_vibration(int				id,
						     double				strength)
{
  if (id >= NBRCELL(gl_joystick) || id < 0)
    return (false);
#ifdef		__WIN32
  if (id >= 4) // XInput stupid limitation.
    return (false);
  XINPUT_VIBRATION vib;

  memset(&vib, 0, sizeof(vib));
  angle = cos(M_PI * angle / 180.0) / 2;
  vib.wLeftMotorSpeed = 65535 * bunny_clamp((0.5 - angle) * strength, 0, 1);
  vib.wRightMotorSpeed = 65535 * bunny_clamp((0.5 + angle) * strength, 0, 1);
  XInputSetState(id, &vib);
#else
  int		fd = sf::Joystick::getDeviceNode(id);

  // On enregistre l'effet qu'on veut faire afin de pouvoir l'appeller ensuite, si il n'existe pas
  if (gl_effect[id].type == 0)
    {
      gl_effect[id].type = FF_PERIODIC;
      gl_effect[id].id = -1; // -1 signifie, alloue moi un effet
      gl_effect[id].u.periodic.waveform = FF_SINE;
      gl_effect[id].u.periodic.offset = 0;
      gl_effect[id].u.periodic.phase = 0;
      gl_effect[id].u.periodic.envelope.attack_length = 100;
      gl_effect[id].u.periodic.envelope.attack_level = 0x7FFF;
      gl_effect[id].u.periodic.envelope.fade_length = 100;
      gl_effect[id].u.periodic.envelope.fade_level = 0x7FFF;
      gl_effect[id].replay.length = 20000;
      gl_effect[id].replay.delay = 0; // On commence maintenant

      gl_effect[id].u.periodic.period = 100;
      gl_effect[id].u.periodic.magnitude = 0x7FFF;
      gl_effect[id].direction = 0;
      
      // L'id de l'effet sera enregistré dans gl_effect[id].id pour être utilisé ensuite
      // Si id ne vaut pas -1, cela rafraichit l'effet, simplement.
      if (ioctl(fd, EVIOCSFF, &gl_effect[id]) == -1)
	scream_error_if(return (false), errno, "ioctl failure", "event");
    }

  struct input_event ie;

  memset(&ie, 0, sizeof(ie));

  ie.type = EV_FF;
  ie.code = FF_GAIN;
  ie.value = 0xFFFF * strength;
  if (write(fd, &ie, sizeof(ie)) == -1)
    scream_error_if(return (false), errno, "write gain effect failure", "event");
  
  // Ordre de jouer ou non l'effet défini
  ie.type = EV_FF;
  ie.code = gl_effect[id].id;
  ie.value = fabs(strength) > 0.1 ? 3 : -1;
  if (write(fd, &ie, sizeof(ie)) == -1)
    scream_error_if(return (false), errno, "write order effect failure", "event");
#endif

  gl_joystick[id].vibration_gain = strength;
  gl_joystick[id].vibrating = (gl_joystick[id].vibration_gain >= 0.01);
  return (true);
}

