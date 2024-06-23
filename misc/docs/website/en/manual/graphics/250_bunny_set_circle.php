<div class="prototype">
  Macro
  $Tvoid@ $Sbunny_set_circle@(
  $Tt_bunny_buffer@ *$Starget@,
  $Tt_bunny_position@ $Sposition@,
  $Tt_bunny_size@ $Sradius@,
  $Tunsigned int@ $Scolor@
  );
</div>
<hr />

<div class="resume">
  <h3>Description</h3>
  $A This function draws a circle of $Scolor@ in $Starget@ at the sent $Sposition@
  and of size $Sradius@.
  <br />
  <br />
  This function can be quite slow: made on GPU side picture like t_bunny_picture
  or t_bunny_window, the cost of going to the GPU for a single circle is
  expansive. For CPU side picture, going throught several functions and
  runtime type casting is expansive and cannot be optimised by the compiler
  unlike an array access by hand.
  <br />
  <br />
  This function will work on t_bunny_pixelarray only if a pointer of type
  t_bunny_my_set_disk is set to gl_bunny_my_set_disk..
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
      $Tt_bunny_position@ $Sposition@:<br />
      $A The position on the surface for the drawing, this is the center of the
      circle.
    </li>
    <li>
      $Tt_bunny_size@ $Sradius@:<br />
      $A The size of the circle.
    </li>
    <li>
      $Tunsigned int@ $Scolor@:<br />
      $A The color of the drawing.
    </li>
  </ul>
</div>
<hr />

<div class="related_functions">
  <h3>Related functions</h3>
  <ul>
    <li>bunny_set_pixel</li>
    <li>bunny_set_line</li>
    <li>bunny_set_polygon</li>
    <li>bunny_set_disk</li>
    <li>bunny_set_geometry</li>
    <li>bunny_fill</li>
    <li>bunny_clear</li>
  </ul>
</div>

