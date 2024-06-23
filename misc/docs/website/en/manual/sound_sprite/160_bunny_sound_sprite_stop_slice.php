<div class="prototype">
  $Tbool@ $Sbunny_sound_sprite_stop_slice@(
  $Tt_bunny_sound_sprite@ *$Ssprite@);
</div>
<hr />

<div class="resume">
  <h3>Description</h3>
  $A Stop the slice being played in the sent sound sprite.
</div>
<hr />

<div class="parameters">
  <h3>Parameters</h3>
  <ul>
    <li>
      $Tt_bunny_sound_sprite@ *$Ssprite@:<br />
      $A The sound sprite that contains the sound slice you want to stop.
    </li>
  </ul>
</div>
<hr />

<div class="return">
  <h3>Return value</h3>
  <ul>
    <li>
      On $Bsuccess@, if the sound was stopped the function returns $Ctrue@.
    </li>
    <li>
      On $Bfailure@, it returns $Cfalse@, probably the sound was already stopped.
    </li>
  </ul>
</div>
<hr />

<div class="related_functions">
  <h3>Related functions</h3>
  <ul>
    <li>bunny_sound_sprite_play_slice</li>
  </ul>
</div>
