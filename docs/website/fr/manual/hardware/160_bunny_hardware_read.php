<div class="prototype">
  $Tbool@ $Sbunny_hardware_read@($Tt_bunny_hardware@ *$Shardware@);
</div>
<hr />

<div class="resume">
  <h3>Description</h3>
  $A Read the status on board and copy it to the sent $Shardware@ structure.
  $Sdigital_inputs@ and $Sanalog_inputs@ will be overwritten.
</div>
<hr />

<div class="parameters">
  <h3>Parameters</h3>
  <ul>
    <li>
      $Tt_bunny_hardware@ *$Shardware@:<br />
      $A The structure in which the board status will be written.
    </li>
  </ul>
</div>
<hr />

<div class="return">
  <h3>Return value</h3>
  <p>$Ctrue@ if the reading was done, $Cfalse on error.
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
      $CEAGAIN@:<br />
      <p>
        Retry later. Maybe the board was not ready yet.
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
    <li>bunny_hardware_write</li>
  </ul>
</div>

