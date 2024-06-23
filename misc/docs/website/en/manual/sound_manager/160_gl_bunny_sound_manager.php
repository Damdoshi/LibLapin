<div class="prototype">
  $Tt_bunny_sound_manager@ $Sgl_bunny_sound_manager@;
</div>
<hr />

<div class="resume">
  <h3>Description</h3>
  $A A global sound manager brought by the library itself.
  This allows you to not make the sound manager follow you everywhere.<br />
  You can still create your own sound manager if you need to, but
  I am not sure about its usefulness.
</div>
<hr />

<div class="parameters">
  <h3>Default values</h3>
  <ul>
    <li>
      $Kconst@ $Tt_bunny_sound@ * $Kconst@ $Scurrent_music@[$SBST_LAST_TRACK@]:<br />
      $A Set to NULL.
    </li>
    <li>
      $Kconst@ $Tdouble@ $Sgeneral_volume@:<br />
      $A Set to 50.0.
    </li>
    <li>
      $Kconst@ $Tdouble@ $Svolumes@[$BST_LAST_SOUND_TYPE@@:<br />
      $A Set to 70.0, 80.0 and 90.0.
    </li>
    <li>
      $Kconst@ $Tdouble@ $Sgeneral_pitch@:<br />
      $A A value superior to 0 which is the general pitch. This impact all sounds.
      <br />
      The normal value is 1.0.
    </li>
    <li>
      $Kconst@ $Tdouble@ $Spitches@[$BST_LAST_SOUND_TYPE@@:<br />
      $A Values superior to 0 which represent the pitch of their category.
      <br />
      The normal value is 1.0.
    </li>
  </ul>
</div>

<div class="related_functions">
  <h3>Related functions</h3>
  <ul>
    <li>bunny_sound_manager_add</li>
    <li>bunny_sound_manager_remove</li>
    <li>t_bunny_sound_manager</li>
  </ul>
</div>
