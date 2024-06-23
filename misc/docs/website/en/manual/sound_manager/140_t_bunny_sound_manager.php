<div class="prototype">
  $Ktypedef struct@ $Ts_bunny_sound_manager@<br />
  {<br />
  $A $Kconst@ $Tt_bunny_sound@ * $Kconst@ $Scurrent_music@[$SBST_LAST_TRACK@];<br />
  $Kconst@ $Tdouble@ $Sgeneral_volume@;<br />
  $Kconst@ $Tdouble@ $Svolumes@[$SBST_LAST_SOUND_TYPE@];<br />
  $Kconst@ $Tdouble@ $Sgeneral_pitch@;<br />
  $Kconst@ $Tdouble@ $Spitches@[$SBST_LAST_SOUND_TYPE@];<br />
  <br />
  } $Tt_bunny_sound_manager@;<br />
</div>
<hr />

<div class="resume">
  <h3>Description</h3>
  $A The sound manager structure role is to collect every
  sounds and musics to control their volumes and pitches
  accordingly to a central command - usually a configuration
  panel in a video game.
</div>
<hr />

<div class="parameters">
  <h3>Attributes</h3>
  <ul>
    <li>
      $Kconst@ $Tt_bunny_sound@ * $Kconst@ $Scurrent_music@[$SBST_LAST_TRACK@]:<br />
      $A This field of length $SBST_LAST_TRACK@ have space for all tracks. It contains
      pointers to musics currently being played so it can stop it, replace it
      and avoid to restart it easily.
    </li>
    <li>
      $Kconst@ $Tdouble@ $Sgeneral_volume@:<br />
      $A A value between 0 and 100 which is the general volume. This impact all sounds.
      <br />
      A normal value is around 50.
    </li>
    <li>
      $Kconst@ $Tdouble@ $Svolumes@[$BST_LAST_SOUND_TYPE@@:<br />
      $A Values between 0 and 100 which represent the volume of their category.
      <br />
      A normal value is around 50.
    </li>
    <li>
      $Kconst@ $Tdouble@ $Sgeneral_pitch@:<br />
      $A A value superior to 0 which is the general pitch. This impact all sounds.
      <br />
      The normal value is 1.
    </li>
    <li>
      $Kconst@ $Tdouble@ $Spitches@[$BST_LAST_SOUND_TYPE@@:<br />
      $A Values superior to 0 which represent the pitch of their category.
      <br />
      The normal value is 1.
    </li>
  </ul>
</div>

<div class="related_functions">
  <h3>Related functions</h3>
  <ul>
    <li>bunny_sound_manager_add</li>
    <li>bunny_sound_manager_remove</li>
    <li>gl_bunny_sound_manager</li>
  </ul>
</div>
