<div class="prototype">
  $Tbool@ $Sbunny_sound_sprite_is_talking@(
  $Tt_bunny_sound_sprite@ *$Ssprite@);
</div>
<hr />

<div class="resume">
  <h3>Description</h3>
  $A Return $Ctrue@ if the slice being played is inside its active duration.
</div>
<hr />

<div class="parameters">
  <h3>Parameters</h3>
  <ul>
    <li>
      $Tt_bunny_sound_sprite@ *$Ssprite@:<br />
      $A The sound sprite to inspect.
    </li>
  </ul>
</div>
<hr />

<div class="return">
  <h3>Return value</h3>
  <p>Returns $Ctrue@ or $Cfalse@ depending of the current time being inside
    the activate duration of the slice.
</div>
<hr />

<div class="related_functions">
  <h3>Related functions</h3>
  <ul>
    <li>bunny_sound_sprite_play_slice</li>
  </ul>
</div>
