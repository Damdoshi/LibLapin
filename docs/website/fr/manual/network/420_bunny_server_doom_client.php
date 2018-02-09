<div class="prototype">
  $Tbool@ $Sbunny_server_doom_client@(
  $Tt_bunny_server@ *$Sserver@,
  $Tint@ $Sfd@
  );
</div>
<hr />

<div class="resume">
  <h3>Description</h3>
  $A Delete the connection associated to the sent $Sfd@ when every
  of its associated write request will be achieved.
</div>
<hr />

<div class="parameters">
  <h3>Parameters</h3>
  <ul>
    <li>
      $Tt_bunny_server@ *$Sserver@:<br />
      $A The server who own the sent file descriptor.
    </li>
    <li>
      $Tint@ $Sfd@:<br />
      $A The file descriptor you want to close.
    </li>
  </ul>
</div>
<hr />

<div class="return">
  <h3>Return value</h3>
  <p>
    Return $Ctrue@ or $Cfalse@ on error.
  </p>
</div>
<hr />

<div class="error_and_log">
  <h3>Error values and logs</h3>
  <p>
    On error, $Vbunny_errno@ is set to:
  </p>
  <br />
  <ul>
    <li>
      $CENOMEM@:<br />
      <p>
        Out of memory.
      </p>
    </li>
    <li>
      $CBE_CANNOT_FIND_ELEMENT@:<br />
      <p>
        Cannot find the sent file descriptor.
      </p>
    </li>
  </ul>
  <br />
  <p>
    Logs written by this function are tagged with the $L"network"@ label.
  </p>
</div>
<hr />

<div class="related_functions">
  <h3>Related functions</h3>
  <ul>
    <li>bunny_server_poll</li>
    <li>bunny_server_packet_ready</li>
    <li>bunny_server_write</li>
  </ul>
</div>

