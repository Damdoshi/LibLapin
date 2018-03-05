<div class="prototype">
  $Ktypedef struct@ $Ts_bunny_equation_collision@<br />
  {<br />
  $A $Tt_bunny_collision_type@ $Stype@;<br />
  $A $Tt_bunny_accurate_position@ $Scoord@[2];<br />
  $A $Tt_bunny_accurate_position@ $Samplitude@;<br />
  $A $Tdouble@ $Sa@;<br />
  $A $Tdouble@ $Sb@;<br />
  $A $Tdouble@ $Sc@;<br />
  $A $Tbool@ $Sorigin_at_center@;<br />
  $A $Tbool@ $Sflipx@;<br />
  $A $Tbool@ $Sflipy@;<br />
  <br />
  } $Tt_bunny_equation_collision@;
</div>
<hr />

<div class="resume">
  <h3>Description</h3>
  $A This structure represents a equation in a 2D space.
  This structure is part of the t_bunny_collision union, but may
  be used separately as the equation collide function returns more
  than a collide/not collide information.<br />
  <br />
  The equation computed for this collision is second degree function:<br />
  $A a * x * x + b * x + c<br />
</div>
<hr />

<div class="parameters">
  <h3>Attributes</h3>
  <ul>
    <li>
      $Tt_bunny_collision_type@ $Stype@:<br />
      $A The type identification enumerated field.
      It <b>must</b> be set to BCT_EQUATION if you use this structure.
    </li>
    <li>
      $Tt_bunny_accurate_position@ $Scoord@[2]:<br />
      $A Coordinates of the rectangle in which the equation will be taken
      in consideration.
    </li>
    <li>
      $Tt_bunny_accurate_position@ $Samplitude@:<br />
      $A The mathematical amplitude of the square. You may wish
      to have a direct correspondance between coord[1], which contains
      the size in pixels and amplitude which contains a size on an arbitrary
      scale. To do so, simply set the same values in coord[1] and in
      amplitude.
    </li>
    <li>
      $Tdouble@ $a@:<br />
      $A The parameter $Sa@ in the second degree equation.
    </li>
    <li>
      $Tdouble@ $b@:<br />
      $A The parameter $Sb@ in the second degree equation.
    </li>
    <li>
      $Tdouble@ $c@:<br />
      $A The parameter $Sc@ in the second degree equation.
    </li>
    <li>
      $Tbool@ $Sorigin_at_center@:<br />
      $A If this field is $Ctrue@, the origina will be placed at the center of the
      equation square. If $Cfalse@, it will depend of $Sflipx@ and $Sflipy@
      attributes, but if they are both false, the origin will be on the top left corner.
    </li>
    <li>
      $Tbool@ $Sflipx@:<br />
      $A If this field is $Cfalse@, the X axis goes from left to right.<br />
      If it is $Ctrue@, from right to left. It will move the origin from
      the left side to the right side of the equation square if $Sorigin_at_center@
      is $Cfalse@.
    </li>
    <li>
      $Tbool@ $Sflipy@:<br />
      $A If this field is $Cfalse@, the Y axis goes from top to bottom.<br />
      If it is $Ctrue@, from bottom to top. It will move the origin from the
      the top side to the bottom side of the equation square if $Sorigin_at_center@
      is $Cfalse@.
    </li>
  </ul>
</div>
<hr />

<div class="related_functions">
  <h3>Related functions</h3>
  <ul>
    <li>t_bunny_collision_type</li>
    <li>t_bunny_collision</li>
    <li>t_bunny_collide_point</li>
    <li>bunny_collision_equation_dot</li>
  </ul>
</div>

