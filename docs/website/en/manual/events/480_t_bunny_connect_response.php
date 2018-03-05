<div class="prototype">
  $Ktypedef@ $Tt_bunny_response@ (*$Tt_bunny_connect_response@)(
  $Tint@ $Sfd@,
  $Tt_bunny_event_state@ $Sstate@,
  $Tvoid@ *$Sdata@
  );
</div>
<hr />

<div class="resume">
  <h3>Description</h3>
  $A The type of function called when a connection is opened or closed.
</div>
<hr />

<div class="parameters">
  <h3>Parameters</h3>
  <ul>
    <li>
      $Tint@ $Sfd@:<br />
      $A The file descriptor that appeired or disappeired.
    </li>
    <li>
      $Tt_bunny_event_state@ $Sstate@:<br />
      $A Is the connection opened or closed?
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
    <li>bunny_set_connect_response</li>
  </ul>
</div>

