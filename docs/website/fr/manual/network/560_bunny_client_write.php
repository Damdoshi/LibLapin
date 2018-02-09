<div class="prototype">
  $Tbool@ $Sbunny_client_write@(
  $Tt_bunny_client@ *$Sclient@,
  $Kconst@ $Tvoid@ *$Sdata@,
  $Tsize_t@ $Slength@
  );
</div>
<hr />

<div class="resume">
  <h3>Description</h3>
  $A Push a write request for the connection that is managed by $Sclient@,
  of $Sdata@ of $Slength@ bytes.
</div>
<hr />

<div class="parameters">
  <h3>Parameters</h3>
  <ul>
    <li>
      $Tt_bunny_client@ *$Sclient@:<br />
      $A The client who own the sent file descriptor.
    </li>
    <li>
      $Kconst@ $Tvoid@ *$Sdata@:<br />
      $A The data to write.
    </li>
    <li>
      $Tsize_t@ $Slength@:<br />
      $A The length of the $Sdata@ to write.
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
    <li>bunny_client_poll</li>
    <li>bunny_client_packet_ready</li>
  </ul>
</div>

