// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2021
//
// LibLapin

#include		"lapin_private.h"

/**
 * @doc-symbol bunny_record_available
 * @doc-module sound
 * @doc-kind function
 * @doc-order 660
 * @doc-since 13
 * @doc-until latest
 * @doc-level advanced
 *
 * @doc-lang en
 * @brief Indicates whether audio recording is available on the current system.
 * @return-success true if recording is available, false otherwise.
 * @see bunny_record_devices, bunny_new_recorder
 *
 * @doc-lang fr
 * @brief Indique si l'enregistrement audio est disponible sur le système courant.
 * @return-success true si l'enregistrement est disponible, false sinon.
 * @see bunny_record_devices, bunny_new_recorder
 */
bool			bunny_record_available(void)
{
  return (sf::SoundBufferRecorder::isAvailable());
}

