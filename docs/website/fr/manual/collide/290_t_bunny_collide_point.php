<div class="prototype">
  $Ktypedef struct@ $Ts_bunny_collide_point@<br />
  {<br />
  $A $Tdouble@ $Sradian@;<br />
  $A $Tt_bunny_accurate_position@ $Sposition@;<br />
  <br />
  } $Tt_bunny_collide_point@;
</div>
<hr />

<div class="resume">
  <h3>Description</h3>
  $A This structure is returned by bunny_collision_equation_dot
  to indicate where the collision occured and what is the inclination
  level on this point.
</div>
<hr />

<div class="parameters">
  <h3>Attributes</h3>
  <ul>
    <li>
      $Tdouble@ $Sradian@:<br />
      $A The inclination level of the equation at this $Sposition@ where
      the collision happened.
    </li>
    <li>
      $Tt_bunny_accurate_position@ $Sposition@:<br />
      $A Coordinates of the collision point.
    </li>
  </ul>
</div>
<hr />

<div class="related_functions">
  <h3>Related functions</h3>
  <ul>
    <li>bunny_collision_equation_dot</li>
  </ul>
</div>

