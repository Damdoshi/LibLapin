<div class="prototype">
  $Tbool@ $Sbunny_server_write@(
  $Tt_bunny_server@ *$Sserver@,
  $Kconst@ $Tvoid@ *$Sdata@,
  $Tsize_t@ $Slength@,
  $Tint@ $Sfd@
  );
</div>
<hr />

<div class="resume">
  <h3>Description</h3>
  $A Push a write request for the connection $Sfd@, that is managed by $Sserver@,
  of $Sdata@ of $Slength@ bytes.
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
      $Kconst@ $Tvoid@ *$Sdata@:<br />
      $A The data to write.
    </li>
    <li>
      $Tsize_t@ $Slength@:<br />
      $A The length of the $Sdata@ to write.
    </li>
    <li>
      $Tint@ $Sfd@:<br />
      $A The file descriptor representing the connection you want to write to.
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
    <li>bunny_server_doom_client</li>
  </ul>
</div>

