<div class="prototype">
  $Ktypedef@ $Tt_bunny_response@ (*$Tt_bunny_message_response@)(
  $Tint@ $Sfd@,
  $Kconst@ $Tvoid@ *$Sbuffer@,
  $Tsize_t@ $Ssize@,
  $Tvoid@ *$Sdata@
  );
</div>
<hr />

<div class="resume">
  <h3>Description</h3>
  $A The type of function called when a network message is received.
</div>
<hr />

<div class="parameters">
  <h3>Parameters</h3>
  <ul>
    <li>
      $Tint@ $Sfd@:<br />
      $A The file descriptor that received the message.
    </li>
    <li>
      $Kconst@ $Tvoid@ *$Sbuffer@:<br />
      $A The received data.
    </li>
    <li>
      $Tsize_t@ $Ssize@:<br />
      $A The size in bytes of the received data.
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
    <li>bunny_set_message_response</li>
  </ul>
</div>

