<div class="prototype">
  $Ktypedef@ $Tt_bunny_response@ (*$Tt_bunny_click@)(
  $Tt_bunny_event_state@ $Sstate@,
  $Tt_bunny_mouse_button@ $Sbutton@,
  $Tvoid@ *$Sdata@
  );
</div>
<hr />

<div class="resume">
  <h3>Description</h3>
  $A The type of function called when a mouse button event happen.
</div>
<hr />

<div class="parameters">
  <h3>Parameters</h3>
  <ul>
    <li>
      $Tt_bunny_event_state@ $Sstate@:<br />
      $A Is the mouse button being pressed or released?
    </li>
    <li>
      $Tt_bunny_mouse_button@ $Sbuton@:<br />
      $A The button being pressed.
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
    <li>bunny_set_click_response</li>
  </ul>
</div>

