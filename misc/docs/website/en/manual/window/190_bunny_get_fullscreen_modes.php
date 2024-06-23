<div class="prototype">
  $Kconst@ $Tt_bunny_size@ *$Sbunny_get_fullscreen_modes@(void);
</div>
<hr />

<div class="resume">
  <h3>Description</h3>
  $A Return an array of all valid fullscreen modes. The array
  is terminated by a { .x = 0, .y = 0 } case.
</div>
<hr />

<div class="return">
  <h3>Return value</h3>
  <ul>
    <li>
      A t_bunny_size structure containing valid resolution
      for a fullscreen mode. The last item is filled with zero.
    </li>
  </ul>
</div>
<hr />

<div class="related_functions">
  <h3>Related functions</h3>
  <ul>
    <li>bunny_start</li>
    <li>bunny_start_style</li>
    <li>bunny_get_current_resolution</li>
  </ul>
</div>



