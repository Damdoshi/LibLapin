k<div class="prototype">
  $Ktypedef struct@ $Ts_bunny_vertex@<br />
  {<br />
  $A $Tt_bunny_accurate_position@ $Spos@;<br />
  $A $Tt_bunny_position@ $Stex@;<br />
  $A $Tunsigned int@ $Scolor@;<br />
  <br />
  } $Tt_bunny_vertex@;
</div>
<hr />

<div class="resume">
  <h3>Description</h3>
  $A Coordinates for the vertex on screen and for the associated texture or color.
  <br />
</div>
<hr />

<div class="parameters">
  <h3>Symbols</h3>
  <ul>
    <li>
      $Tt_bunny_accurate_position@ $Spos@:<br />
      $A A coordinate.
    </li>
    <li>
      $Tt_bunny_position@ $Stex@:<br />
      $A The coordinate on the texture that match the coordinate in $Spos@ on the shape.
    </li>
    <li>
      $Tunsigned int@ $Scolor@:<br />
      $A If bunny_set_geometry was called without a $Stexture@, the color drawn at the
      sent coordinate.
    </li>
  </ul>
</div>
<hr />

<div class="related_functions">
  <h3>Related functions</h3>
  <ul>
    <li>t_bunny_geometry</li>
    <li>t_bunny_vertex_array</li>
    <li>bunny_set_geometry</li>
  </ul>
</div>

