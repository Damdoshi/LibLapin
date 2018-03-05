<div class="prototype">
  $Tt_bunny_plugin@ *$Sbunny_new_plugin@($Kconst@ $Tchar@ *$Slibfile@);
</div>
<hr />

<div class="resume">
  <h3>Description</h3>
  $A Load the sent dynamic library and functions inside.
</div>
<hr />

<div class="parameters">
  <h3>Parameters</h3>
  <ul>
    <li>
      $Kconst@ $Tchar@ *$Slibfile@:<br />
      $A A dynamic library file, which respect the bunny plugin format.
    </li>
  </ul>
</div>
<hr />

<div class="return">
  <h3>Return value</h3>
  <ul>
    <li>
      On $Bsuccess@, the function returns the address of a valid
      t_bunny_plugin pointer.
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
      $CEINVAL@:<br />
      <p>
        Cannot open the sent file, or the sent dynamic library
        does not contains the function __get_function_list which is mandatory
        for a bunny plugin.
      </p>
    </li>
    <li>
      $CENOMEM@:<br />
      <p>
        Out of memory.
      </p>
    </li>
    <li>
      $CBE_CONFIGURED_FUNCTION_NOT_FOUND@:<br />
      <p>
        A function present in the bunny plugin table was not
        found in the loaded plugin.
      </p>
    </li>
    <li>
      $CBE_TOO_MANY_PARAMETERS@:<br />
      <p>
        Functions in bunny plugin can only have up to 4 parameters.
      </p>
    </li>
  </ul>
  <br />
  <p>
    Logs written by this function are tagged with the $L"ressource"@ and
    $L"plugin"@ label.
  </p>
</div>
<hr />

<div class="related_functions">
  <h3>Related functions</h3>
  <ul>
    <li>t_bunny_plugin</li>
    <li>bunny_delete_plugin</li>
    <li>bunny_plugin_call</li>
    <li>bunny_plugin_callv</li>
    <li>bunny_plugin_get_function</li>
  </ul>
</div>

