<div class="prototype">
  $Tvoid@ $Sbunny_set_line@(
  $Tt_bunny_buffer@ *$Starget@,
  $Kconst@ $Tt_bunny_position@ *$Spositions@,
  $Kconst@ $Tunsigned int@ $*Scolors@
  );
</div>
<hr />

<div class="resume">
  <h3>Description</h3>
  $A This function draws a line from $Sposition@[0] to $Sposition@[1]
  of $Scolor@[0] to $Scolor@[1] progressively in $Starget@.
  <br />
  <br />
  This function can be quite slow: made on GPU side picture like t_bunny_picture
  or t_bunny_window, the cost of going to the GPU for a single line is
  expansive. For CPU side picture, going throught several functions and
  runtime type casting is expansive and cannot be optimised by the compiler
  unlike an array access by hand.
  <br />
  <br />
  This function will work on t_bunny_pixelarray only if a pointer of type
  t_bunny_my_set_line is set to gl_bunny_my_set_line.
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
      $A Coordinates of the line. The array is two cases long.
      circle.
    </li>
    <li>
      $Tunsigned int@ *$Scolor@:<br />
      $A Two colors, used with matching line coordinates.
    </li>
  </ul>
</div>
<hr />

<div class="related_functions">
  <h3>Related functions</h3>
  <ul>
    <li>bunny_set_pixel</li>
    <li>bunny_set_circle</li>
    <li>bunny_set_polygon</li>
    <li>bunny_set_geometry</li>
    <li>bunny_fill</li>
    <li>bunny_clear</li>
  </ul>
</div>

