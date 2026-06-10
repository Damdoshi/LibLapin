// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2021
//
// LibLapin

#include		"lapin_private.h"

/**
 * @doc-symbol bunny_start_record
 * @doc-module sound
 * @doc-kind function
 * @doc-order 620
 * @doc-since 13
 * @doc-until latest
 * @doc-level advanced
 *
 * @doc-lang en
 * @brief Starts capturing audio with a recorder.
 * @param recorder Recorder to start.
 * @return-success true if recording started.
 * @return-failure false if the recorder could not start.
 * @see bunny_stop_record, bunny_new_recorder, bunny_record_available
 *
 * @doc-lang fr
 * @brief Démarre la capture audio avec un enregistreur.
 * @param recorder Enregistreur à démarrer.
 * @return-success true si l'enregistrement a démarré.
 * @return-failure false si l'enregistreur n'a pas pu démarrer.
 * @see bunny_stop_record, bunny_new_recorder, bunny_record_available
 */
bool			bunny_start_record(t_bunny_recorder		*recorder)
{
  struct bunny_recorder	*rec = (struct bunny_recorder*)recorder;

  if (rec->recorder->start(rec->sample_per_second) == false)
    return (false);
  return (rec->recording = true);
}
