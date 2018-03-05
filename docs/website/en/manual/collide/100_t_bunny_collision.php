<div class="prototype">
  $Ktypedef union@ $Tu_bunny_collision@<br />
  {<br />
  $A $Tt_bunny_collision_type@ $Stype@;<br />
  $A $Tt_bunny_dot_collision@ $Sdot@;<br />
  $A $Tt_bunny_circle_collision@ $Scircle@;<br />
  $A $Tt_bunny_line_collision@ $Sline@;<br />
  $A $Tt_bunny_triangle_collision@ $Striangle@;<br />
  $A $Tt_bunny_rectangular_collision@ $Srectangular@;<br />
  $A $Tt_bunny_quad_collision@ $Squad@;<br />
  $A $Tt_bunny_equation_collision@ $Sequation@;<br />
  <br />
  } $Tt_bunny_collision@;
</div>
<hr />

<div class="resume">
  <h3>Description</h3>
  $A This union contains every kind of collidable shape and an enumeration
  field to allow runtime type identification.<br />
  <br />
  To configure this union, you must set to the $Stype@ attribute a value
  from t_bunny_collision_type, accordingly to the collision shape you
  want to set. If you need to use the t_bunny_dot_collision attribute, for
  example, you will have to set $Stype@ to BCT_DOT.
</div>
<hr />

<div class="parameters">
  <h3>Attributes</h3>
  <ul>
    <li>
      $Tt_bunny_collision_type@ $Stype@:<br />
      $A The type identification enumerated field.
    </li>
    <li>
      $Tt_bunny_dot_collision@ $Sdot@:<br />
      $A A structure that describe a dot, used if you set type to BCT_DOT.
    </li>
    <li>
      $Tt_bunny_circle_collision@ $Scircle@:<br />
      $A A structure that describe a dot, used if you set type to BCT_CIRCLE.
    </li>
    <li>
      $Tt_bunny_line_collision@ $Sline@:<br />
      $A A structure that describe a dot, used if you set type to BCT_LINE.
    </li>
    <li>
      $Tt_bunny_triangle_collision@ $Striangle@:<br />
      $A A structure that describe a dot, used if you set type to BCT_TRIANGLE.
    </li>
    <li>
      $Tt_bunny_rectangular_collision@ $Srectangular@:<br />
      $A A structure that describe a dot, used if you set type to BCT_RECTANGULAR.
    </li>
    <li>
      $Tt_bunny_quad_collision@ $Squad@:<br />
      $A A structure that describe a dot, used if you set type to BCT_QUAD.
    </li>
    <li>
      $Tt_bunny_equation_collision@ $Sequation@:<br />
      $A A structure that describe a dot, used if you set type to BCT_EQUATION.
    </li>
  </ul>
</div>
<hr />

<div class="related_functions">
  <h3>Related functions</h3>
  <ul>
    <li>bunny_collide</li>
    <li>bunny_draw_collision_shape</li>
    <li>t_bunny_dot_collision</li>
    <li>t_bunny_circle_collision</li>
    <li>t_bunny_line_collision</li>
    <li>t_bunny_triangle_collision</li>
    <li>t_bunny_rectangular_collision</li>
    <li>t_bunny_quad_collision</li>
    <li>t_bunny_equation_collision</li>
    <li>t_bunny_collision_type</li>
  </ul>
</div>

