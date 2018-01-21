<div class="prototype">
  $Tbool@ $Sbunny_triangle_collision_dot@(
  $Kconst@ $Tt_bunny_vertex_array@ *$Striangle@,
  $Kconst@ $Tt_bunny_accurate_position@ *$Sdot@
  );
</div>
<hr />

<div class="resume">
  <h3>Description</h3>
  $A Test the collision between the two shapes.
</div>
<hr />

<div class="parameters">
  <h3>Parameters</h3>
  <ul>
    <li>
      $Kconst@ $Tt_bunny_vertex_array@ *@Striangle@:
      $A Three coordinates representing the triangle.
    </li>
    <li>
      $Kconst@ $Tt_bunny_accurate_position@ *$Sdot@:
      $A The coordinates of the dot.
    </li>
  </ul>
</div>
<hr />

<div class="return">
  <h3>Return value</h3>
  <p>
    $Ctrue@ or $Cfalse@ depending if there is a collision or not.
  </p>
</div>
<hr />

<div class="details">
  <h3>Additional informations</h3>
  <p>
    This function is part of the first version of the collide module
    and can be quite handy for simple program, but for more complex
    ones, consider using the bunny_collide system.
  </P>
</div>


