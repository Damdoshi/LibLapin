<div class="prototype">
  $Ktypedef@ $Tt_bunny_response@ (*$Tt_bunny_joy_connect@)(
  $Tt_bunny_event_state@ $Sstate@,
  $Tint@ $Sjoyid@,
  $Kconst@ $Tt_bunny_joystick@ *$Sjoyinfo@,
  $Tvoid@ *$Sdata@
  );
</div>
<hr />

<div class="resume">
  <h3>Description</h3>
  $A The type of function called when a joystick is connected or disconnected.
</div>
<hr />

<div class="parameters">
  <h3>Parameters</h3>
  <ul>
    <li>
      $Tt_bunny_event_state@ $Sstate@:<br />
      $A Is the joystick connected or disconnected?
    </li>
    <li>
      $Tint@ $Sjoyid@:<br />
      $A The joystick id. From 0 to $SLAST_BUNNY_JOYSTICK@.
    </li>
    <li>
      $Kconst@ $Tt_bunny_joystick@ *$Sjoyinfo@:<br />
      $A Informations about the joystick being connected. $CNULL@ if disconnected.
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
    <li>bunny_set_joy_connect_response</li>
  </ul>
</div>

