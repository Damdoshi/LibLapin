<div class="prototype">
  $Ktypedef struct@ $Ts_bunny_sound_sprite@<br />
  {<br />
  $A $Tt_bunny_music@ $Ssoundset@;<br />
  $A $Tt_bunny_map@ *$Ssound_areas@;<br />
  $A $Kconst@ $Tt_bunny_sound_slice@ *$Slast_played_slice@;<br />
  $A $Kconst@ $Tt_bunny_music_track@ $Strack@;<br />
  <br />
  } $Tt_bunny_sound_sprite@;<br />
</div>
<hr />

<div class="resume">
  <h3>Description</h3>
  $A The sound sprite is an extension of the t_bunny_music structure.
  Its purpose is to be treated not as a single big chunk of sound but as
  a collection of sound effect (typically: voices) and played partially
  thanks to a set of associated functions.<br />
  <br />
  The reason behind this is to save audio memory, which can be really
  short when you use a wide amount of small sound files: as the
  t_bunny_sound_sprite is based on t_bunny_music, the audio content
  is streamed from the disk and do not consume a lot of memory.
</div>
<hr />

<div class="parameters">
  <h3>Attributes</h3>
  <ul>
    <li>
      $Tt_bunny_music@ $Ssoundset@:<br />
      $A The sound file, treated as a music track, behind the sound sprite.
    </li>
    <li>
      $Tt_bunny_map@ *$Ssound_areas@:<br />
      $A A collection of t_bunny_sound_slice. The key of the map is of type
      uint64_t and it use hash value generated by bunny_sound_sprite_slice_name
      with configuration file path as identificator.
    </li>
    <li>
      $Kconst@ $Tt_bunny_sound_slice@ *$Slast_played_slice@:<br />
      $A The slice currently being played if there is one, or $CNULL@.
    </li>
    <li>
      $Kconst@ $Tt_bunny_music_track@ $Strack@:<br />
      $A If the sound sprite is inside a t_bunny_sound_manager, then the track
      on which the sound sprite is running is precised here. If it is not the
      case or is not running, the value BST_LAST_TRACK is stored here.
    </li>
  </ul>
</div>

<div class="related_functions">
  <h3>Related functions</h3>
  <ul>
    <li>t_bunny_sound_slice</li>
    <li>bunny_load_sound_sprite</li>
    <li>bunny_delete_sound</li>
  </ul>
</div>