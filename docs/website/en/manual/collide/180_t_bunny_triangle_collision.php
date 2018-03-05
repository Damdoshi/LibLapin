<div class="prototype">
  $Ktypedef struct@ $Ts_bunny_triangle_collision@<br />
  {<br />
  $A $Tt_bunny_collision_type@ $Stype@;<br />
  $A $Tt_bunny_accurate_position@ $Scoord@[3];<br />
  <br />
  } $Tt_bunny_triangle_collision@;
</div>
<hr />

<div class="resume">
  <h3>Description</h3>
  $A This structure represents a triangle in a 2D space.
  This structure is part of the t_bunny_collision union.
</div>
<hr />

<div class="parameters">
  <h3>Attributes</h3>
  <ul>
    <li>
      $Tt_bunny_collision_type@ $Stype@:<br />
      $A The type identification enumerated field.
      It <b>must</b> be set to BCT_TRIANGLE if you use this structure.
    </li>
    <li>
      $Tt_bunny_accurate_position@ $Scoord@[3]:<br />
      $A Coordinates of the triangle.
    </li>
  </ul>
</div>
<hr />

<div class="related_functions">
  <h3>Related functions</h3>
  <ul>
    <li>t_bunny_collision_type</li>
    <li>t_bunny_collision</li>
  </ul>
</div>

