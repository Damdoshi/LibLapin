<div class="prototype">
  $Tvoid@ $Sbunny_set_polygon@(
  $Tt_bunny_buffer@ *$Starget@,
  $Kconst@ $Tt_bunny_position@ *$Spositions@,
  $Kconst@ $Tunsigned int@ $*Scolors@
  );
</div>
<hr />

<div class="resume">
  <h3>Description</h3>
  $A This function draws a filled triangle between $Sposition@[0], $Sposition@[1]
  and $Sposition@[2] matching colors from $Scolor@[0], $Scolor@[1], $Scolor@[2]
  in $Starget@.
  <br />
  <br />
  This function will work on t_bunny_pixelarray only if a pointer of type
  t_bunny_my_set_polygon is set to gl_bunny_my_set_polygon.
</div>
<hr />

<div class="parameters">
  <h3>Parameters</h3>
  <ul>
    <li>
      $Tt_bunny_buffer@ *$Starget@:<br />
      $A The surface on which drawing will be done.
    </li>
    <li>
      $Tt_bunny_position@ *$Sposition@:<br />
      $A Coordinates of the polygon. The array is three cases long.
      circle.
    </li>
    <li>
      $Tunsigned int@ *$Scolor@:<br />
      $A Three colors, used with matching triangle coordinates.
    </li>
  </ul>
</div>
<hr />

<div class="related_functions">
  <h3>Related functions</h3>
  <ul>
    <li>bunny_set_pixel</li>
    <li>bunny_set_circle</li>
    <li>bunny_set_line</li>
    <li>bunny_set_geometry</li>
    <li>bunny_fill</li>
    <li>bunny_clear</li>
  </ul>
</div>

