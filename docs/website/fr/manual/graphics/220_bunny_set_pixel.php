<div class="prototype">
  $Tvoid@ $Sbunny_set_pixel@(
  $Tt_bunny_buffer@ *$Starget@,
  $Tt_bunny_position@ $Sposition@,
  $Tunsigned int@ $Scolor@
  );
</div>
<hr />

<div class="resume">
  <h3>Description</h3>
  $A This function draws a pixel of $Scolor@ in $Starget@ at the sent $Sposition@.
  <br />
  <br />
  This function can be quite slow: made on GPU side picture like t_bunny_picture
  or t_bunny_window, the cost of going to the GPU for a single pixel is
  expansive. For CPU side picture, going throught several functions and
  runtime type casting is expansive and cannot be optimised by the compiler
  unlike an array access by hand.
  <br />
  <br />
  This function will work on t_bunny_pixelarray only if a pointer of type
  t_bunny_my_set_pixel is set to gl_bunny_my_set_pixel.
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
      $A The position on the surface for the drawing.
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
    <li>bunny_set_circle</li>
    <li>bunny_set_line</li>
    <li>bunny_set_polygon</li>
    <li>bunny_set_geometry</li>
    <li>bunny_fill</li>
    <li>bunny_clear</li>
  </ul>
</div>

