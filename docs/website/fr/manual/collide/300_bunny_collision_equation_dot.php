<div class="prototype">
  $Tbool@ $Sbunny_collision_equation_dot@(
  $Kconst@ $Tt_bunny_equation_collision@ *$Sa@,
  $Kconst@ $Tt_bunny_dot_collision@ *$Sb@
  );
</div>
<hr />

<div class="resume">
  <h3>Description</h3>
  $A Test the collision between an equation square and a dot shape.
  Returns the complete collision information.
</div>
<hr />

<div class="parameters">
  <h3>Parameters</h3>
  <ul>
    <li>
      $Kconst@ $Tt_bunny_equation_collision@ *$Sa@:
      $A The shape to collide with $Sb@.
    </li>
    <li>
      $Kconst@ $Tt_bunny_dot_collision@ *$Sb@:
      $A The shape to collide with $Sa@.
    </li>
  </ul>
</div>
<hr />

<div class="return">
  <h3>Return value</h3>
  <p>
    A Return a t_bunny_collide_point which contains the point
    at the surface of the equation where the collision happened
    and which is the inclination level of the equation at this point.
</div>
<hr />

<div class="related_functions">
  <h3>Related functions</h3>
  <ul>
    <li>t_bunny_collide_point</li>
  </ul>
</div>

