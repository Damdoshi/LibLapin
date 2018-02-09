<div class="prototype">
  $Tvoid@ $Sbunny_sound_manager_stop_music@(
  $Tt_bunny_sound_manager@ *$Ssound_manager@,
  $Tt_bunny_music_track@ $Strack@
  );
</div>
<hr />

<div class="resume">
  <h3>Description</h3>
  $A Stop the music being played on the sent track.
</div>
<hr />

<div class="parameters">
  <h3>Parameters</h3>
  <ul>
    <li>
      $Tt_bunny_sound_manager@ $Ssound_manager@:<br />
      $A The sound manager to edit.
    </li>
    <li>
      $Tt_bunny_music_track@ $Strack@:<br />
      $A The track on which the music is being played.
      <br />
      If $SBST_ALL@ is sent, then all musics are stopped.
    </li>
  </ul>
</div>
<hr />

<div class="related_functions">
  <h3>Related functions</h3>
  <ul>
    <li>bunny_sound_manager_play_music</li>
    <li>bunny_sound_manager_play_sound</li>
    <li>bunny_sound_manager_stop_sound</li>
  </ul>
</div>

