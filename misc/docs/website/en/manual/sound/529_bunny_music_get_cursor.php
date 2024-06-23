<div class="prototype">
  $Tdouble@ $Sbunny_music_get_cursor@(
  $Kconst@ $Tt_bunny_music@ *$Ssound@
  );
</div>
<hr />

<div class="resume">
  <h3>Description</h3>
  $A Get the current read position of the sent music.
</div>
<hr />

<div class="parameters">
  <h3>Parameters</h3>
  <ul>
    <li>
      $Tt_bunny_music@ *$Smusic@:<br />
      $A The music to inspect.
    </li>
  </ul>
</div>
<hr />

<div class="return">
  <h3>Return value</h3>
  <p>
    Returns the position in seconds in the music that match the currently being
    read part.
  </p>
</div>
<hr />


<div class="related_functions">
  <h3>Related functions</h3>
  <ul>
    <li>bunny_sound_set_cursor</li>
    <li>bunny_sound_get_cursor</li>
  </ul>
</div>

