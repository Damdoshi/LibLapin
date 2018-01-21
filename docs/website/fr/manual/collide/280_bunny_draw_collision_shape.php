<div class="prototype">
  $Tvoid@ $Sbunny_draw_collision_shape@(
  $Tt_bunny_buffer@ *@Starget@,
  $Kconst@ $Tt_bunny_collision@ *$Sshape@,
  $Tunsigned int@ $Scolor@
  );
</div>
<hr />

<div class="resume">
  <h3>Description</h3>
  $A Draw the sent collision $Sshape@ on the $Starget@ buffer.
  Use $Scolor@ to draw.<br />
  <br />
  bunny_draw_collision_shape will use bunny_set_pixel, bunny_set_line
  and bunny_set_circle so it will not work on t_bunny_pixelarray
  unless you previously set the function pointer and code yourself
  those functions.<br />
  <br />
  Also, because there is a lot of writes, this function may be slow
  if called for a lot of complex shapes.
</div>
<hr />

<div class="parameters">
  <h3>Parameters</h3>
  <ul>
    <li>
      $Tt_bunny_buffer@ *$Sstart@:<br />
      $A The buffer on which the shape will be drawn.
    <li>
      $Kconst@ $Tt_bunny_collision@ *@Sa@:<br />
      $A The shape to draw.
    </li>
    <li>
      $Tunsigned int@ @Scolor@:<br />
      $A The color of the drawn shape.
    </li>
  </ul>
</div>
<hr />

<div class="related_functions">
  <h3>Related functions</h3>
  <ul>
    <li>bunny_set_pixel</li>
    <li>bunny_set_line</li>
    <li>bunny_set_circle</li>
  </ul>
</div>

