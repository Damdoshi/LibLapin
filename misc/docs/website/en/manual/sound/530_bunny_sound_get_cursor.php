<div class="prototype">
  $Tdouble@ $Sbunny_sound_get_cursor@(
  $Kconst@ $Tt_bunny_sound@ *$Ssound@
  );
</div>
<hr />

<div class="resume">
  <h3>Description</h3>
  $A Get the current read position of the sent sound.
</div>
<hr />

<div class="parameters">
  <h3>Parameters</h3>
  <ul>
    <li>
      $Tt_bunny_sound@ *$Ssound@:<br />
      $A The sound to inspect.
    </li>
  </ul>
</div>
<hr />

<div class="return">
  <h3>Return value</h3>
  <p>
    Returns the position in seconds in the sound that match the currently being
    read part.
  </p>
</div>
<hr />


<div class="related_functions">
  <h3>Related functions</h3>
  <ul>
    <li>bunny_sound_set_cursor</li>
    <li>bunny_sound_set_duration</li>
  </ul>
</div>

