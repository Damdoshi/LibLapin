<div class="prototype">
  $Ktypedef@ $Tvoid@ *(*$St_bunny_my_set_geometry@)(
  $Tt_bunny_pixelarray@ *$Starget@,
  $Tt_bunny_geometry@ $Sgeometry@,
  $Tt_bunny_vertex_array@ *$Sarray@,
  $Tt_bunny_pixelarray@ *$Stexture@
  );
</div>
<hr />

<div class="resume">
  <h3>Description</h3>
  $A This type is the one used by gl_bunny_my_geometry function pointer
  that may be used to complete bunny_set_geometry by giving it the ability to
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
      $Tt_bunny_geometry@ $Sgeometry@:<br />
      $A The kind of shape that will be drawn.
    </li>
    <li>
      $Tt_bunny_vertex_array@ *$Sarray@:<br />
      $A Informations about the shape to draw.
    </li>
    <li>
      $Tt_bunny_clipable@ *$Sclipable@:<br />
      $A The texture of the geometry, can be $CNULL@.
      </li>
  </ul>
</div>
<hr />

<div class="related_functions">
  <h3>Related functions</h3>
  <ul>
    <li>t_bunny_my_set_pixel</li>
    <li>t_bunny_my_set_circle</li>
    <li>t_bunny_my_set_line</li>
    <li>t_bunny_my_set_polygon</li>

    <li>gl_bunny_my_set_pixel</li>
    <li>gl_bunny_my_set_circle</li>
    <li>gl_bunny_my_set_line</li>
    <li>gl_bunny_my_geometry</li>
  </ul>
</div>

