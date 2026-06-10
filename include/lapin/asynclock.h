/*
** Jason Brillante "Damdoshi"
** Hanged Bunny Studio 2014-2016
**
** Bibliotheque Lapin
*/

/**
 * @doc
 * @doc-symbol asynclock
 * @doc-kind module
 * @doc-module asynclock
 * @doc-order 0
 * @doc-since 12
 * @doc-until latest
 * @doc-level 10
 *
 * @doc-lang en
 * @brief Provides time helpers and loop-synchronized delayed callbacks.
 * @description The Asynclock module contains timestamp and sleep helpers, plus traps: callbacks registered to be executed before or after the main loop function at a configured time, during a configured duration, or repeatedly.
 * @description When bunny_loop or bunny_loop_mw is used, bunny_asynclock is called by the loop itself. Calling it manually is mainly useful when writing your own loop system.
 * @header lapin/asynclock.h
 *
 * @doc-lang fr
 * @brief Fournit des outils de temps et des callbacks différés synchronisés avec la boucle.
 * @description Le module Asynclock contient des assistants de timestamp et de pause, ainsi que les traps : des callbacks enregistrés pour être exécutés avant ou après la fonction principale de boucle, à partir d'un moment donné, pendant une durée donnée ou de manière répétée.
 * @description Lorsque bunny_loop ou bunny_loop_mw est utilisé, bunny_asynclock est appelée par la boucle elle-même. L'appeler manuellement sert surtout lorsque vous écrivez votre propre système de boucle.
 * @header lapin/asynclock.h
 */

#ifndef			__LAPIN_ASYNCLOCK_H__
# define		__LAPIN_ASYNCLOCK_H__
# if			!defined(__LAPIN_H__)
#  error		You cannot include this file directly.
# endif

/**
 * @doc
 * @doc-symbol bunny_time_old
 * @doc-kind macro
 * @doc-module asynclock
 * @doc-order 282
 * @doc-since 12
 * @doc-until latest
 * @doc-level 20
 *
 * @doc-lang en
 * @brief Tests whether a bunny-clock date is already past.
 * @description bunny_time_old compares the sent absolute bunny-clock date with bunny_get_current_time.
 * @param time The absolute bunny-clock date to test, in seconds.
 * @return-case true Returns a non-zero value when time is lower than the current bunny-clock time.
 * @return-case false Returns 0 while time is still current or in the future.
 * @see bunny_get_current_time
 *
 * @doc-lang fr
 * @brief Teste si une date de l'horloge bunny est déjà passée.
 * @description bunny_time_old compare la date absolue envoyée avec bunny_get_current_time.
 * @param time La date absolue de l'horloge bunny à tester, en secondes.
 * @return-case true Renvoie une valeur non nulle lorsque time est inférieur au temps courant de l'horloge bunny.
 * @return-case false Renvoie 0 tant que time est encore courant ou futur.
 * @see bunny_get_current_time
 */
# define		bunny_time_old(time)		(time < bunny_get_current_time())

/**
 * @doc
 * @doc-symbol bunny_time_alive
 * @doc-kind macro
 * @doc-module asynclock
 * @doc-order 284
 * @doc-since 12
 * @doc-until latest
 * @doc-level 20
 *
 * @doc-lang en
 * @brief Tests whether a bunny-clock date is still current or in the future.
 * @description bunny_time_alive compares the sent absolute bunny-clock date with bunny_get_current_time.
 * @param time The absolute bunny-clock date to test, in seconds.
 * @return-case true Returns a non-zero value while time is greater than or equal to the current bunny-clock time.
 * @return-case false Returns 0 when time is already past.
 * @see bunny_get_current_time
 *
 * @doc-lang fr
 * @brief Teste si une date de l'horloge bunny est encore courante ou future.
 * @description bunny_time_alive compare la date absolue envoyée avec bunny_get_current_time.
 * @param time La date absolue de l'horloge bunny à tester, en secondes.
 * @return-case true Renvoie une valeur non nulle tant que time est supérieur ou égal au temps courant de l'horloge bunny.
 * @return-case false Renvoie 0 lorsque time est déjà passé.
 * @see bunny_get_current_time
 */
# define		bunny_time_alive(time)		(time >= bunny_get_current_time())

/**
 * @doc
 * @doc-symbol bunny_time_plus
 * @doc-kind macro
 * @doc-module asynclock
 * @doc-order 286
 * @doc-since 12
 * @doc-until latest
 * @doc-level 20
 *
 * @doc-lang en
 * @brief Builds a bunny-clock date in the future.
 * @description bunny_time_plus adds the sent duration to bunny_get_current_time and returns the resulting absolute bunny-clock date.
 * @param duration The duration to add to the current bunny-clock time, in seconds.
 * @return-case success On $Bsuccess@, returns the current bunny-clock time plus duration.
 * @see bunny_get_current_time
 *
 * @doc-lang fr
 * @brief Construit une date future de l'horloge bunny.
 * @description bunny_time_plus ajoute la durée envoyée à bunny_get_current_time et renvoie la date absolue obtenue dans l'horloge bunny.
 * @param duration La durée à ajouter au temps courant de l'horloge bunny, en secondes.
 * @return-case success En cas de $Bsuccès@, renvoie le temps courant de l'horloge bunny plus duration.
 * @see bunny_get_current_time
 */
# define		bunny_time_plus(duration)	(bunny_get_current_time() + duration)

/**
 * @doc
 * @doc-symbol bunny_time_minus
 * @doc-kind macro
 * @doc-module asynclock
 * @doc-order 288
 * @doc-since 12
 * @doc-until latest
 * @doc-level 20
 *
 * @doc-lang en
 * @brief Builds a bunny-clock date in the past.
 * @description bunny_time_minus subtracts the sent duration from bunny_get_current_time and returns the resulting absolute bunny-clock date.
 * @param duration The duration to subtract from the current bunny-clock time, in seconds.
 * @return-case success On $Bsuccess@, returns the current bunny-clock time minus duration.
 * @see bunny_get_current_time
 *
 * @doc-lang fr
 * @brief Construit une date passée de l'horloge bunny.
 * @description bunny_time_minus soustrait la durée envoyée à bunny_get_current_time et renvoie la date absolue obtenue dans l'horloge bunny.
 * @param duration La durée à soustraire au temps courant de l'horloge bunny, en secondes.
 * @return-case success En cas de $Bsuccès@, renvoie le temps courant de l'horloge bunny moins duration.
 * @see bunny_get_current_time
 */
# define		bunny_time_minus(duration)	(bunny_get_current_time() - duration)

/**
 * @doc
 * @doc-symbol t_bunny_time
 * @doc-kind typedef
 * @doc-module asynclock
 * @doc-order 100
 * @doc-since 12
 * @doc-until latest
 * @doc-level 10
 *
 * @doc-lang en
 * @brief Represents a timestamp in nanoseconds.
 * @description t_bunny_time is an unsigned integer type used by the real-time helpers of the asynclock module. Values returned by bunny_get_time and bunny_delta_time are expressed in nanoseconds.
 * @see bunny_get_time, bunny_delta_time, bunny_sleep
 *
 * @doc-lang fr
 * @brief Représente un timestamp en nanosecondes.
 * @description t_bunny_time est un type entier non signé utilisé par les assistants de temps réel du module asynclock. Les valeurs renvoyées par bunny_get_time et bunny_delta_time sont exprimées en nanosecondes.
 * @see bunny_get_time, bunny_delta_time, bunny_sleep
 */
typedef uint64_t	t_bunny_time;

double			bunny_get_current_time(void);
double			bunny_reset_clock(void);
t_bunny_time		bunny_get_time(void);
unsigned long long	bunny_usleep(unsigned long long			delay);
t_bunny_time		bunny_sleep(t_bunny_time			delay);
t_bunny_time		bunny_delta_time(t_bunny_time			before,
					 t_bunny_time			after);

/**
 * @doc
 * @doc-symbol t_bunny_call_order
 * @doc-kind enum
 * @doc-module asynclock
 * @doc-order 140
 * @doc-since 12
 * @doc-until latest
 * @doc-level 40
 *
 * @doc-lang en
 * @brief Selects when a trap is evaluated during the main loop.
 * @description t_bunny_call_order is used by bunny_new_trap and bunny_asynclock to separate traps called before the loop main function from traps called after it.
 * @value BCO_BEFORE_LOOP_MAIN_FUNCTION The trap is evaluated before the function configured with bunny_set_loop_main_function.
 * @value BCO_AFTER_LOOP_MAIN_FUNCTION The trap is evaluated after the function configured with bunny_set_loop_main_function.
 * @see bunny_new_trap, bunny_asynclock
 *
 * @doc-lang fr
 * @brief Sélectionne le moment où une trap est évaluée pendant la boucle principale.
 * @description t_bunny_call_order est utilisé par bunny_new_trap et bunny_asynclock pour séparer les traps appelées avant la fonction principale de boucle des traps appelées après celle-ci.
 * @value BCO_BEFORE_LOOP_MAIN_FUNCTION La trap est évaluée avant la fonction configurée avec bunny_set_loop_main_function.
 * @value BCO_AFTER_LOOP_MAIN_FUNCTION La trap est évaluée après la fonction configurée avec bunny_set_loop_main_function.
 * @see bunny_new_trap, bunny_asynclock
 */
typedef enum		e_bunny_call_order
  {
    BCO_BEFORE_LOOP_MAIN_FUNCTION,
    BCO_AFTER_LOOP_MAIN_FUNCTION
  }			t_bunny_call_order;

struct			s_bunny_trap;

/**
 * @doc
 * @doc-symbol t_bunny_trap_function
 * @doc-kind callback
 * @doc-module asynclock
 * @doc-order 160
 * @doc-since 12
 * @doc-until latest
 * @doc-level 40
 *
 * @doc-lang en
 * @brief Callback type called when a trap condition is fulfilled.
 * @description t_bunny_trap_function receives the elapsed time transmitted to bunny_asynclock, the trap responsible for the call and the arbitrary data pointer configured when the trap was created.
 * @description The sent trap can safely be deleted from inside the callback with bunny_delete_trap. It is only marked for removal and deleted when the asynclock can do it safely.
 * @param elapsed_time The elapsed time sent to bunny_asynclock by bunny_loop, bunny_loop_mw or user code.
 * @param trap The trap responsible for this function call.
 * @param data The arbitrary pointer configured when the trap was created.
 * @see t_bunny_trap, bunny_new_trap, bunny_delete_trap, bunny_asynclock
 *
 * @doc-lang fr
 * @brief Type de callback appelé lorsque la condition d'une trap est remplie.
 * @description t_bunny_trap_function reçoit le temps écoulé transmis à bunny_asynclock, la trap responsable de l'appel et le pointeur arbitraire configuré lors de la création de la trap.
 * @description La trap envoyée peut être supprimée sans danger depuis le callback avec bunny_delete_trap. Elle est seulement marquée pour suppression et détruite lorsque l'asynclock peut le faire sans risque.
 * @param elapsed_time Le temps écoulé envoyé à bunny_asynclock par bunny_loop, bunny_loop_mw ou le code utilisateur.
 * @param trap La trap responsable de cet appel de fonction.
 * @param data Le pointeur arbitraire configuré lors de la création de la trap.
 * @see t_bunny_trap, bunny_new_trap, bunny_delete_trap, bunny_asynclock
 */
typedef void		(*t_bunny_trap_function)(double			elapsed_time,
						 struct s_bunny_trap	*trap,
						 void			*data);

/**
 * @doc
 * @doc-symbol t_bunny_trap
 * @doc-kind struct
 * @doc-module asynclock
 * @doc-order 180
 * @doc-since 12
 * @doc-until latest
 * @doc-level 40
 *
 * @doc-lang en
 * @brief Represents a scheduled callback handled by the asynclock.
 * @description t_bunny_trap is partially abstract. Its private field and timing fields describe the internal scheduling state. User code may replace function or additional_param if it needs to change what will be called when the trap occurs.
 * @field _private Private implementation storage. Do not modify it.
 * @field start_time Absolute start time, in seconds, or a non-positive value for queued traps. Do not modify it.
 * @field duration Trap duration or repeat period, in seconds. Do not modify it.
 * @field function The function called when the trap occurs.
 * @field additional_param The third parameter sent to function.
 * @see t_bunny_trap_function, bunny_new_trap, bunny_delete_trap, bunny_asynclock
 *
 * @doc-lang fr
 * @brief Représente un callback planifié géré par l'asynclock.
 * @description t_bunny_trap est partiellement abstraite. Son champ privé et ses champs de temps décrivent l'état interne de planification. Le code utilisateur peut remplacer function ou additional_param s'il doit changer ce qui sera appelé lorsque la trap se déclenche.
 * @field _private Espace de stockage privé de l'implémentation. Ne le modifiez pas.
 * @field start_time Temps de départ absolu, en secondes, ou valeur non positive pour les traps en file. Ne le modifiez pas.
 * @field duration Durée ou période de répétition de la trap, en secondes. Ne le modifiez pas.
 * @field function La fonction appelée lorsque la trap se déclenche.
 * @field additional_param Le troisième paramètre envoyé à function.
 * @see t_bunny_trap_function, bunny_new_trap, bunny_delete_trap, bunny_asynclock
 */
typedef struct		s_bunny_trap
{
  const char		_private[3 * sizeof(void*)];
  const double		start_time;
  const double		duration;
  t_bunny_trap_function	function;
  void			*additional_param;
}			t_bunny_trap;

t_bunny_trap		*bunny_new_trap(t_bunny_trap_function		function,
					 t_bunny_call_order		order,
					 double				start_time,
					 double				duration,
					 void				*param);
void			bunny_delete_trap(t_bunny_trap			*trap);
int			bunny_asynclock(double				elapsed_time,
					t_bunny_call_order		order);

#endif	/*		__LAPIN_ASYNCLOCK_H__	*/
