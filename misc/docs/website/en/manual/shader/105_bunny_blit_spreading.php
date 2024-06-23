<div class="prototype">
  $Tvoid@ $Sbunny_blit_spreading@(
  $Tt_bunny_buffer@ *$Sbuffer@,
  $Kconst@ $Tt_bunny_position@ *$Spos@,
  $Tt_bunny_spreading@ *$Sspread@
  );
</div>
<hr />

<div class="resume">
  <h3>Description</h3>
  $A This function spread the color inside the matching buffer and draw the result
  inside the sent buffer at the sent position.
  Note that $Tt_bunny_clipable@ properties of $Slayout can be used to transform
  the drawing, like the $Sclip@ on $Sbunny_blit@.
</div>
<hr />

<div class="parameters">
  <h3>Parameters</h3>
  <ul>
    <li>
      $Tt_bunny_buffer@ *$Sbuffer@:<br />
      $A The target on which the color spreading buffer will be drawn.
    </li>
    <li>
      $Kconst@ $Tt_bunny_position@:<br />
      Where to draw $Sspread@.
    </li>
    <li>
      $Tt_bunny_spreading@ *$Sspread@:<br />
      $A The color spreading effect to draw.
    </li>
  </ul>
</div>
<hr />

<div class="related_functions">
  <h3>Related functions</h3>
  <ul>
    <li>t_bunny_spreading</li>
    <li>bunny_draw_spreading_source</li>
    <li>bunny_fill_spreading</li>
    <li>bunny_clear_spreading</li>
  </ul>
</div>

