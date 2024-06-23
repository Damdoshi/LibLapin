<div class="prototype">
  $Tvoid@ $Sbunny_sound_volume@(
  $Tt_bunny_sound@ *$Ssound@,
  $Tdouble@ $Svolume@
  );
</div>
<hr />

<div class="resume">
  <h3>Description</h3>
  $A Set the sent volume to the sent sound.
  Do not use this function if the sound is inside a t_bunny_manager.
  Use bunny_managed_sound_volume instead.
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
      $Tdouble@ $Svolume@:<br />
      $A The volume to set.
    </li>
  </ul>
</div>
<hr />

<div class="related_functions">
  <h3>Related functions</h3>
  <ul>
    <li>bunny_sound_pitch</li>
    <li>bunny_sound_loop</li>
    <li>bunny_sound_position</li>
    <li>bunny_sound_attenuation</li>
  </ul>
</div>

