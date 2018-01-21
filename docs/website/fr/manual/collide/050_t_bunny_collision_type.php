<div class="prototype">
  $Ktypedef enum@ $Te_bunny_collision_type@<br />
  {<br />
  $A $SBCT_DOT@,<br />
  $A $SBCT_CIRCLE@,<br />
  $A $SBCT_LINE@,<br />
  $A $SBCT_TRIANGLE@,<br />
  $A $SBCT_RECTANGLE@,<br />
  $A $SBCT_QUAD@,<br />
  $A $SBCT_EQUATION@,<br />
  $A $SLAST_COLLISION_TYPE@<br />
  <br />
  } $Tt_bunny_collision_type@;
</div>
<hr />

<div class="resume">
  <h3>Description</h3>
  $A This enumeration is used by t_bunny_collision to dynamicaly type
  itself into one of its attribute.
</div>
<hr />

<div class="parameters">
  <h3>Symbols</h3>
  <ul>
    <li>
      $SBCT_DOT@:<br />
      If the t_bunny_collision field $Stype@ have this value, then
      it means the union is a t_bunny_dot_collision.
    </li>
    <li>
      $SBCT_CIRCLE@:<br />
      If the t_bunny_collision field $Stype@ have this value, then
      it means the union is a t_bunny_circle_collision.
    </li>
    <li>
      $SBCT_LINE@:<br />
      If the t_bunny_collision field $Stype@ have this value, then
      it means the union is a t_bunny_line_collision.
    </li>
    <li>
      $SBCT_TRIANGLE@:<br />
      If the t_bunny_collision field $Stype@ have this value, then
      it means the union is a t_bunny_triangle_collision.
    </li>
    <li>
      $SBCT_RECTANGLE@:<br />
      If the t_bunny_collision field $Stype@ have this value, then
      it means the union is a t_bunny_rectangular_collision.
    </li>
    <li>
      $SBCT_QUAD@:<br />
      If the t_bunny_collision field $Stype@ have this value, then
      it means the union is a t_bunny_quad_collision.
    </li>
    <li>
      $SBCT_EQUATION@:<br />
      If the t_bunny_collision field $Stype@ have this value, then
      it means the union is a t_bunny_equation_collision.
    </li>
  </ul>
</div>

<div class="related_functions">
  <h3>Related functions</h3>
  <ul>
    <li>t_bunny_collision</li>
  </ul>
</div>
