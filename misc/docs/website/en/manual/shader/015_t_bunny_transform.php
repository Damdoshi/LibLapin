<div class="prototype">
  $Ktypedef struct@ $Ts_bunny_transform@<br />
  {<br />
  $A $Tt_bunny_accurate_position@ $Sorigin@;
  $A $Tt_bunny_accurate_position@ $Stranslation@;
  $A $Tt_bunny_accurate_position@ $Sscale@;
  $A $Tdouble@ $Srotation@;
  <br />
  } $Tt_bunny_transform@;<br />
</div>
<hr />

<div class="resume">
  <h3>Description</h3>
  $A This structure describes a complete transformation: it allows
  you to set in a single time an origin shift, a translation, a scale
  change or a rotation setting.
</div>
<hr />

<div class="parameters">
  <h3>Attributes</h3>
  <ul>
    <li>
      $Tt_bunny_accurate_position@ $Sorigin@:<br />
      $A The origin of the picture. Used as anchor for rotation
      and also shift the position.
    </li>
    <li>
      $Tt_bunny_accurate_position@ $Stranslation@:<br />
      $A A position shift.
    </li>
    <li>
      $Tt_bunny_accurate_position@ $scale@:<br />
      $A A scale.
    </li>
    <li>
      $Tdouble@ $Srotation@<br />
      $A A rotation. Use the origin as rotation center.
    </li>
  </ul>
</div>

