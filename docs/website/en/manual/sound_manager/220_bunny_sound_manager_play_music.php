<div class="prototype">
  $Tbool@ $Sbunny_sound_manager_play_music@(
  $Tt_bunny_sound_manager@ *$Ssound_manager@,
  $Tt_bunny_music@, *$Smusic@,
  $Tt_bunny_music_track@ $Strack@
  );
</div>
<hr />

<div class="resume">
  <h3>Description</h3>
  $A Play the sent music that must be a registered music
  in the sent sound manager on the sent track. If it was
  already being played, it is left as it. If another
  music was being played on this track, it is stopped before. If no
  music was being played, the music simply start.
</div>
<hr />

<div class="parameters">
  <h3>Parameters</h3>
  <ul>
    <li>
      $Tt_bunny_sound_manager@ $Ssound_manager@:<br />
      $A The sound manager in which the music was added.
    </li>
    <li>
      $Tt_bunny_music@ *$Smusic@:<br />
      $A The music to play.
    </li>
    <li>
      $Tt_bunny_music_track@ $Strack@:<br />
      $A The track on which the music will be played.
      <br />
      If $SBST_ALL@ is sent, then all musics are stopped
      and then the sent music is played on $SBST_TRACK_01@.
    </li>
  </ul>
</div>
<hr />

<div class="return">
  <h3>Return value</h3>
  <p>
    Return $Ctrue@ if the music is being played now or was already playing.
  </p>
</div>
<hr />

<div class="related_functions">
  <h3>Related functions</h3>
  <ul>
    <li>bunny_sound_manager_stop_music</li>
    <li>bunny_sound_manager_play_sound</li>
    <li>bunny_sound_manager_stop_sound</li>
  </ul>
</div>

