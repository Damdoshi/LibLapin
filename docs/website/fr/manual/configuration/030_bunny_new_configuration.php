<div class="prototype">
  $Tt_bunny_configuration@ *$Sbunny_new_configuration@($Tvoid@);
</div>
<hr />

<div class="resume">
  <h3>Description</h3>
  $A Generate a configuration structure.
  It must be destroyed by bunny_delete_configuration.
</div>
<hr />

<div class="return">
  <h3>Return value</h3>
  <ul>
    <li>
      On $Bsuccess@, the function returns the address of
      a valid t_bunny_configuration.
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
  </ul>
  <br />
  <p>
    Logs written by this function are tagged with the $L"configuration"@ label.
  </p>
</div>
<hr />

<div class="related_functions">
  <h3>Related functions</h3>
  <ul>
    <li>t_bunny_configuration_type</li>
    <li>bunny_new_configuration</li>
    <li>bunny_open_configuration</li>
    <li>bunny_load_configuration</li>
    <li>bunny_save_configuration</li>
    <li>bunny_read_configuration</li>
    <li>bunny_write_configuration</li>
    <li>bunny_delete_configuration</li>
  </ul>
</div>

