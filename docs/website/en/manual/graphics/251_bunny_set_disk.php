<div class="prototype">
  $Tvoid@ $Sbunny_set_disk@(
  $Tt_bunny_buffer@ *$Starget@,
  $Tt_bunny_position@ $Sposition@,
  $Tt_bunny_size@ $Sradius@,
  $Tunsigned int@ $Sinside_color@,
  $Tunsigned int@ $Slining_color@,
  $Tint@ $Slining_thickness@
  );
</div>
<hr />

<div class="resume">
  <h3>Description</h3>
  $A This function draws a disk of $Sinside_color@ in $Starget@ at the sent
  $Sposition@ and of size $Sradius@. This disk have a lining of $Slining_thickness@
  pixels and of color $Slining_color@.
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
  t_bunny_my_set_circle is set to gl_bunny_my_set_circle.
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
      $Tunsigned int@ $Sinside_color@:<br />
      $A The color of the disk. Can be transparent.
    </li>
    <li>
      $Tunsigned int@ $Slining_color@:<br />
      $A The color of the disk lining. Can be transparent.
    </li>
    <li>
      $Tint@ $Slining_thickness@:<br />
      $A The thickness of the lining in pixels.
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
    <li>bunny_set_circle</li>
    <li>bunny_set_geometry</li>
    <li>bunny_fill</li>
    <li>bunny_clear</li>
  </ul>
</div>

