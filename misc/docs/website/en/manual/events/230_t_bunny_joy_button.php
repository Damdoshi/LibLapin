<div class="prototype">
  $Ktypedef@ $Tt_bunny_response@ (*$Tt_bunny_joy_button@)(
  $Tt_bunny_event_state@ $Sstate@,
  $Tint@ $Sjoyid@,
  $Tint@ $Sbutton@,
  $Tvoid@ *$Sdata@
  );
</div>
<hr />

<div class="resume">
  <h3>Description</h3>
  $A The type of function called when a joystick button is pressed or released.
</div>
<hr />

<div class="parameters">
  <h3>Parameters</h3>
  <ul>
    <li>
      $Tt_bunny_event_state@ $Sstate@:<br />
      $A Was the button pressed or released?
    <li>
      $Tint@ $Sjoyid@:<br />
      $A The id of the joystick with the button being pressed or released.
    </li>
    <li>
      $Tint@ $Sbutton@:<br />
      $A The button that was pressed or released.
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
    <li>bunny_set_joy_button_response</li>
    <li>bunny_get_joy_button</li>
  </ul>
</div>

