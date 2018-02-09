<div class="prototype">
  $Tvoid@ $Sbunny_set_geometry@(
  $Tt_bunny_buffer@ *$Starget@,
  $Tt_bunny_geometry@ $Sgeometry@,
  $Tt_bunny_vertex_array@ *$Sarray@,
  $Tt_bunny_clipable@ *$Stexture@
  );
</div>
<hr />

<div class="resume">
  <h3>Description</h3>
  $A This function draw a complex shape on $Starget@. It can be useful
  to draw a lot of elements in a single call, so the GPU access cost became
  negligible, even for pixel drawing.
  <br />
  <br />
  This function will work on t_bunny_pixelarray only if a pointer of type
  t_bunny_my_geometry is set to gl_bunny_my_geometry.
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
      $Tt_bunny_geometry@ $Sgeometry@:<br />
      $A The kind of shape the $Sarray@ contains.
    </li>
    <li>
      $Tt_bunny_vertex_array@ *$Sarray@:<br />
      $A A structure containing a variable size array of vertices.
    </li>
    <li>
      $Tt_bunny_clipable@ *$Stexture@:<br />
      $A The texture that can be applied to the drawn shape. $CNULL@
      means no texture, provoking the exploitation of the color information
      inside $Sarray@.
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
    <li>bunny_set_polygon</li>
    <li>bunny_set_geometry</li>
    <li>bunny_fill</li>
    <li>bunny_clear</li>
  </ul>
</div>

