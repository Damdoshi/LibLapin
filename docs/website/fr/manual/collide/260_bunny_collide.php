<div class="prototype">
  $Tbool@ $Sbunny_collide@(
  $Kconst@ $Tt_bunny_collision@ *$Sa@,
  $Kconst@ $Tt_bunny_collision@ *$Sb@
  );
</div>
<hr />

<div class="resume">
  <h3>Description</h3>
  $A Test if the two shapes collide and return $Ctrue@ or $Cfalse@
  accordingly.<br />
  <br />
  For dot-equation collision, you should prefer use
  bunny_collision_equation_dot which return not only a $Tbool@ but
  the position and the angle of collision.
</div>
<hr />

<div class="parameters">
  <h3>Parameters</h3>
  <ul>
    <li>
      $Kconst@ $Tt_bunny_collision@ *@Sa@:
      $A The shape to collide with $Sb@.
    </li>
    <li>
      $Kconst@ $Tt_bunny_collision@ *@Sb@:
      $A The shape to collide with $Sa@.
    </li>
  </ul>
</div>
<hr />

<div class="return">
  <h3>Return value</h3>
  <p>
    A $Ctrue@ if shapes collide, else $Cfalse@.
</div>
<hr />

<div class="related_functions">
  <h3>Related functions</h3>
  <ul>
    <li>bunny_collision_equation_dot</li>
  </ul>
</div>

