<div class="prototype">
  $Ktypedef@ $Tt_bunny_response@ (*$Tt_bunny_joy_axis@)(
  $Tint@ $Sjoyid@,
  $Tt_bunny_axis@ $Saxis@,
  $Tfloat@ $Svalue@,
  $Tvoid@ *$Sdata@
  );
</div>
<hr />

<div class="resume">
  <h3>Description</h3>
  $A The type of function called when a joystick axis moved.
</div>
<hr />

<div class="parameters">
  <h3>Parameters</h3>
  <ul>
    <li>
      $Tint@ $Sjoyid@:<br />
      $A The id of the joystick with the sent axis move.
    </li>
    <li>
      $Tt_bunny_axis@ $Saxis@:<br />
      $A The axis that moved.
    </li>
    <li>
      $Tfloat@ $Svalue@:<br />
      $A A value between -100 and 100 which represents the position of the axis.
    </li>
    <li>
      $Tvoid@ *$Sdata@:<br />
      $A The data sent as the last parameter of bunny_loop or bunny_loop_mw.
    </li>
  </ul>
</div>

<div class="related_functions">
  <h3>Related functions</h3>
  <ul>
    <li>bunny_set_joy_axis_response</li>
    <li>bunny_set_joy_axis_minimum_offset</li>
    <li>bunny_get_joy_axis</li>
  </ul>
</div>

