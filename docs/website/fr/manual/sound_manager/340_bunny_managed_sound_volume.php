<div class="prototype">
  Macro
  $Tbool@ $Sbunny_managed_sound_volume@(
  $Tt_bunny_sound_manager@ *$Ssound_manager@,
  $Tt_bunny_sound@ *$Ssound@,
  $Tdouble@ $Svolume@
  );
</div>
<hr />

<div class="resume">
  <h3>Description</h3>
  $A Set the volume of the sent sound to the given value
  considering the context. The computed value, which
  takes consideration of the proper volume, the global volume
  and the category volume will be stored inside the t_bunny_sound
  itself.
</div>
<hr />

<div class="parameters">
  <h3>Parameters</h3>
  <ul>
    <li>
      $Tt_bunny_sound_manager@ $Ssound_manager@:<br />
      $A The sound manager in which the effect was added.
    </li>
    <li>
      $Tt_bunny_effect@ *$Ssound@:<br />
      $A The sound to configure.<br />
      If you use <b>C11</b> (Not available in C++), this
      function can handle $Tt_bunny_music@*, $Tt_bunny_effect@*
      and $Tt_bunny_sound@* automatically.<br />
      If you use a previous version or C++, this function only
      takes a $Tt_bunny_sound@ and you have to resolve the type
      yourself.
    </li>
    <li>
      $Tdouble@ $Svolume@:<br />
      $A The volume to set.
    </li>
  </ul>
</div>
<hr />

<div class="return">
  <h3>Return value</h3>
  <p>
    Return $Ctrue@ if the effect was found and set.
  </p>
</div>
<hr />

<div class="details">
  <h3>Additional informations</h3>
  <p>This macro wraps a call to a real function, which is:</p>
  <p>
    $Tbool@ $S_bunny_managed_sound_volume@(
    $Tt_bunny_sound_manager@ *$Ssound_manager@,
    $Tt_bunny_sound@ *$Ssound@,
    $Tdouble@ $Svolume@
    );
  </p>
</div>
<hr />

<div class="related_functions">
  <h3>Related functions</h3>
  <ul>
    <li>bunny_managed_sound_pitch</li>
  </ul>
</div>

