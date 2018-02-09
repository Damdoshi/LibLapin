<div class="prototype">
  $Ktypedef enum@ $Te_bunny_response@<br />
  {<br />
  $A $SGO_DOWN@,
  $A $SGO_UP@,
  $A $SLOST_FOCUS@ = $SGO_DOWN@,
  $A $SGOT_FOCUS@ = $SGO_UP@,
  $A $SCONNECTED@ = $SGO_DOWN@,
  $A $SDISCONNECTED@ = $SGO_UP@,
  $A $SENTERING@ = $SGO_DOWN@,
  $A $SLEAVING@ = $SGO_UP@,
  <br />
  } $Tt_bunny_response@;
</div>
<hr />

<div class="resume">
  <h3>Description</h3>
  $A Describe if a button is going up or down, the windows focus is lost or got,
  a joystick is connected or disconnected... or we are entering for the first time
  in the bunny_loop or bunny_loop_mw loop, or leaving it.
</div>
