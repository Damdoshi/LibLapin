<div class="prototype">
  $Tvoid@ $Sbunny_set_joy_axis_minimum_offset@(
  $Tt_bunny_axis@ $Saxis@,
  $Tfloat@ $Soffset@
  );
</div>
<hr />

<div class="resume">
  <h3>Description</h3>
  $A Set a minimum shift between a previous value and a new one
  to trigger the joystick axis event. It avoids useless repetition
  on analogic joystick that can be annoying on menus.
</div>
<hr />

<div class="parameters">
  <h3>Parameters</h3>
  <ul>
    <li>
      $Tt_bunny_axis@ $Saxis@:<br />
      $A The axis to restrict.
    </li>
    <li>
      $Tfloat@ $Soffset@:<br />
      $A The minimum shift. Must be a value between 0 and 100.
    </li>
  </ul>
</div>

<div class="related_functions">
  <h3>Related functions</h3>
  <ul>
    <li>t_bunny_joy_axis</li>
    <li>bunny_set_joy_axis_minimum_offset</li>
    <li>bunny_get_joy_axis</li>
  </ul>
</div>

