// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2018
//
// Lapin library

#include		<time.h>
#include		"lapin_private.h"

/**
 * @doc
 * @doc-symbol bunny_sleep
 * @doc-kind function
 * @doc-module asynclock
 * @doc-order 116
 * @doc-since 12
 * @doc-until latest
 * @doc-level 10
 *
 * @doc-lang en
 * @brief Sleeps for a duration expressed in nanoseconds.
 * @description bunny_sleep waits until the sent delay expires. If the sleep is interrupted by a signal on systems using nanosleep, the remaining duration is returned.
 * @param delay The requested sleep duration, in nanoseconds.
 * @return-case elapsed On normal completion, returns 0.
 * @return-case interrupted If the sleep is interrupted, returns the remaining duration in nanoseconds.
 * @see bunny_usleep
 *
 * @doc-lang fr
 * @brief Attend pendant une durée exprimée en nanosecondes.
 * @description bunny_sleep attend jusqu'à l'expiration du délai envoyé. Si la pause est interrompue par un signal sur les systèmes utilisant nanosleep, la durée restante est renvoyée.
 * @param delay La durée d'attente demandée, en nanosecondes.
 * @return-case elapsed En fin normale d'attente, renvoie 0.
 * @return-case interrupted Si l'attente est interrompue, renvoie la durée restante en nanosecondes.
 * @see bunny_usleep
 */
t_bunny_time		bunny_sleep(t_bunny_time	delay)
{
#if			!( _WIN32 || __WIN32__ )
  struct timespec	duration;
  struct timespec	remain;

  duration.tv_sec = delay / 1000000000;
  duration.tv_nsec = delay % 1000000000;
  if (nanosleep(&duration, &remain))
    return (remain.tv_sec * 1e9 + remain.tv_nsec);
  return (0);
#else
  t_bunny_time		prev;
  t_bunny_time		elap;

  prev = bunny_get_time();
  sf::sleep(sf::microseconds(delay / 1000));
  if ((elap = bunny_get_time() - prev) > delay)
    return (0);
  return (delay - elap);
#endif
}

/**
 * @doc
 * @doc-symbol bunny_usleep
 * @doc-kind function
 * @doc-module asynclock
 * @doc-order 113
 * @doc-since 12
 * @doc-until latest
 * @doc-level 10
 *
 * @doc-lang en
 * @brief Sleeps for a duration expressed in microseconds.
 * @description bunny_usleep waits until the sent delay expires. Internally, the delay is converted to nanoseconds and sent to bunny_sleep.
 * @description With the current implementation, an interrupted sleep returns the remaining duration as reported by bunny_sleep, therefore in nanoseconds.
 * @param delay The requested sleep duration, in microseconds.
 * @return-case elapsed On normal completion, returns 0.
 * @return-case interrupted If the sleep is interrupted, returns the remaining duration as reported by bunny_sleep.
 * @see bunny_sleep
 *
 * @doc-lang fr
 * @brief Attend pendant une durée exprimée en microsecondes.
 * @description bunny_usleep attend jusqu'à l'expiration du délai envoyé. En interne, le délai est converti en nanosecondes et transmis à bunny_sleep.
 * @description Avec l'implémentation actuelle, une attente interrompue renvoie la durée restante telle que bunny_sleep la rapporte, donc en nanosecondes.
 * @param delay La durée d'attente demandée, en microsecondes.
 * @return-case elapsed En fin normale d'attente, renvoie 0.
 * @return-case interrupted Si l'attente est interrompue, renvoie la durée restante telle que bunny_sleep la rapporte.
 * @see bunny_sleep
 */
unsigned long long	bunny_usleep(unsigned long long	delay)
{
  return (bunny_sleep(delay * 1e3));
}
