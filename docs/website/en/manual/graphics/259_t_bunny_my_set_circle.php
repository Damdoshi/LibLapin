<div class="prototype">
  $Ktypedef@ $Tvoid@ *(*$St_bunny_my_set_circle@)(
  $Tt_bunny_pixelarray@ *$Starget@,
  $Tt_bunny_position@ $Sposition@,
  $Tt_bunny_size@ $Sradius@,
  $Tunsigned int@ $Slining_color@
  );
</div>
<hr />

<div class="resume">
  <h3>Description</h3>
  $A This type is the one used by gl_bunny_my_set_circle function pointer
  that may be used to complete bunny_set_circle by giving it the ability to
  draw on a t_bunny_pixelarray.
</div>
<hr />

<div class="parameters">
  <h3>Parameters</h3>
  <ul>
    <li>
      $Tt_bunny_pixelarray@ *$Starget@:<br />
      $A The picture where the shape will be drawn.
    </li>
    <li>
      $Tt_bunny_position@ $Sposition@:<br />
      $A The position of the shape.
    </li>
    <li>
      $Tt_bunny_size@ $Ssize@:<br />
      $A The size of the shape.
    </li>
    <li>
      $Tunsigned int@ $Scolor@:<br />
      $A The color of the circle.
    </li>
  </ul>
</div>
<hr />

<div class="related_functions">
  <h3>Related functions</h3>
  <ul>
    <li>t_bunny_my_set_line</li>
    <li>t_bunny_my_set_polygon</li>
    <li>t_bunny_my_geometry</li>

    <li>gl_bunny_my_set_pixel</li>
    <li>gl_bunny_my_set_line</li>
    <li>gl_bunny_my_set_polygon</li>
    <li>gl_bunny_my_geometry</li>
  </ul>
</div>

