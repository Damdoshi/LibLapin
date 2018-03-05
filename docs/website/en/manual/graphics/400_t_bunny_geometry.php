<div class="prototype">
  $Ktypedef enum@ $Te_bunny_geometry@<br />
  {<br />
  $A $SBGY_PIXELS@,<br />
  $A $SBGY_LINES@,<br />
  $A $SBGY_LINE_STRIP@,<br />
  $A $SBGY_TRIANGLES@,<br />
  $A $SBGY_TRIANGLE_STRIP@,<br />
  $A $SBGY_TRIANGLE_FAN@,<br />
  $A $SBGY_QUADS@,<br />
  $A $SLAST_GEOMETRY@,<br />
  <br />
  } $Tt_bunny_geometry@;
</div>
<hr />

<div class="resume">
  <h3>Description</h3>
  $A A type to send to bunny_set_geometry to indicate which kind of shape to draw,
  how to interpret the sent t_bunny_vertex_array.
</div>
<hr />

<div class="parameters">
  <h3>Symbols</h3>
  <ul>
    <li>
      $SBGY_PIXELS@:<br />
      $A Indicates the vertex array contains pixels.
    </li>
    <li>
      $SBGY_LINES@:<br />
      $A Indicates the vertex array contains couple of coordinates forming several lines.
    </li>
    <li>
      $SBGY_LINE_STRIP@:<br />
      $A Indicates the vertex array contains several coordinates forming a single
      broken lines.
    </li>
    <li>
      $SBGY_TRIANGLES@:<br />
      $A Indicates the vertex array contains trio of coordinates forming several triangles.
    </li>
    <li>
      $SBGY_TRIANGLE_STRIP:<br />
      $A Indicates the vertex array contains at least three coordinates and then, each
      additionnal coordinate use the two previous ones to add a new triangle.
    </li>
    <li>
      $SBGY_TRIANGLE_FAN:<br />
      $A Indicates the vertex array contains at least three coordinates. The first
      coordinate is shared by every triangles formed by following ones.
    </li>
    <li>
      $SBGY_QUADS:<br />
      $A Indicates the vertex array contains quartets of coordinates forming quads.
      Coordinates of a single quad must be fully clockwise or anti clockwise.
    </li>
  </ul>
</div>
<hr />

<div class="related_functions">
  <h3>Related functions</h3>
  <ul>
    <li>t_bunny_vertex</li>
    <li>t_bunny_vertex_array</li>
    <li>bunny_set_geometry</li>
  </ul>
</div>

