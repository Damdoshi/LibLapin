<div class="prototype">
  $Ktypedef@ $Tt_bunny_response@ (*$Tt_bunny_key@)(
  $Tt_bunny_event_state@ $Sstate@,
  $Tt_bunny_keysym@ $Ssym@,
  $Tvoid@ *$Sdata@
  );
</div>
<hr />

<div class="resume">
  <h3>Description</h3>
  $A The type of function called when a keyboard event happen.
  If you need to handle text input, use t_bunny_type instead.
</div>
<hr />

<div class="parameters">
  <h3>Parameters</h3>
  <ul>
    <li>
      $Tt_bunny_event_state@ $Sstate@:<br />
      $A Is the key being pressed or released?
    </li>
    <li>
      $Tt_bunny_keysym@ $Ssym@:<br />
      $A The key being pressed.
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
    <li>bunny_set_key_response</li>
    <li>bunny_get_keyboard</li>
  </ul>
</div>

