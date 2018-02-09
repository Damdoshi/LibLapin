<div class="prototype">
  $Tt_bunny_hardware@ *$Sbunny_new_hardware@($Tsize_t@ $Sid@);
</div>
<hr />

<div class="resume">
  <h3>Description</h3>
  $A Open a link with a connected VM110N with the sent $Sid@. The
  returned data must be freed with bunny_delete_hardware.
</div>
<hr />

<div class="parameters">
  <h3>Parameters</h3>
  <ul>
    <li>
      $Tsize_t@ $Sid@:<br />
      $A The id of the board, depending of jumpers on it.
    </li>
  </ul>
</div>
<hr />

<div class="return">
  <h3>Return value</h3>
  <ul>
    <li>
      On $Bsuccess@, the function returns a valid t_bunny_hardware.
    </li>
    <li>
      On $Bfailure@, it returns $CNULL@.
    </li>
  </ul>
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
      $CBE_CANT_GENERATE_RESSOURCE@:<br />
      <p>
        Cannot connect to the board with the sent id. It may be
        because there is no board, because the id is bad or because you
        do not have the right to connect to a USB device (And then, running
        your process as root will make this call successful)
      </p>
    </li>
  </ul>
  <br />
  <p>
    Logs written by this function are tagged with the $L"hardware"@ label.
  </p>
</div>
<hr />

<div class="related_functions">
  <h3>Related functions</h3>
  <ul>
    <li>t_bunny_hardware</li>
    <li>bunny_delete_hardware</li>
  </ul>
</div>

