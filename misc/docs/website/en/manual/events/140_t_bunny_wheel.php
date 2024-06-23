<div class="prototype">
  $Ktypedef@ $Tt_bunny_response@ (*$Tt_bunny_wheel@)(
  $Tint@ $Swheelid@,
  $Tint@ $Sdelta@,
  $Tvoid@ *$Sdata@
  );
</div>
<hr />

<div class="resume">
  <h3>Description</h3>
  $A The type of function called when a mouse wheel event happen.
</div>
<hr />

<div class="parameters">
  <h3>Parameters</h3>
  <ul>
    <li>
      $Tint@ $Swheelid@:<br />
      $A The id of the mouse that moved.
    </li>
    <li>
      $Tint@ $Sdelta@:<br />
      $A How much the wheel moved.
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
    <li>bunny_set_wheel_response</li>
  </ul>
</div>

