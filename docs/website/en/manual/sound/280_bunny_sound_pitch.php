<div class="prototype">
  $Tvoid@ $Sbunny_sound_pitch@(
  $Tt_bunny_sound@ *$Ssound@,
  $Tdouble@ $Spitch@
  );
</div>
<hr />

<div class="resume">
  <h3>Description</h3>
  $A Set the sent pitch to the sent sound.
  Do not use this function if the sound is inside a t_bunny_manager.
  Use bunny_managed_sound_pitch instead.
</div>
<hr />

<div class="parameters">
  <h3>Parameters</h3>
  <ul>
    <li>
      $Tt_bunny_sound@ *$Ssound@:<br />
      $A The sound to modify.
    </li>
    <li>
      $Tdouble@ $Spitch@:<br />
      $A The pitch to set.
    </li>
  </ul>
</div>
<hr />

<div class="related_functions">
  <h3>Related functions</h3>
  <ul>
    <li>bunny_sound_volume</li>
    <li>bunny_sound_loop</li>
    <li>bunny_sound_position</li>
    <li>bunny_sound_attenuation</li>
  </ul>
</div>

