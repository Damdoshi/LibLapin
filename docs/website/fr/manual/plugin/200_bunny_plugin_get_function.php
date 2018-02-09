<div class="prototype">
  $Tvoid@ *$Sbunny_plugin_get_function@(
  $Kconst@ $Tt_bunny_plugin@ *$Splugin@,
  $Kconst@ $Tchar@ *$Sfuncname@
  );
</div>
<hr />

<div class="resume">
  <h3>Description</h3>
  $A Return a function pointer from the library represented by $Splugin@,
  even if it is not part of the bunny plugin interface: any function
  inside the library can be requested.
</div>
<hr />

<div class="parameters">
  <h3>Parameters</h3>
  <ul>
    <li>
      $Kconst@ $Tt_bunny_plugin@ *$Splugin@:<br />
      $A The dynamic library in which $Sfuncname@ is.
    </li>
    <li>
      $Kconst@ $Tchar@ *$Sfuncname@:<br />
      $A The name of the function you want to fetch.
    </li>
  </ul>
</div>
<hr />

<div class="return">
  <h3>Return value</h3>
  <ul>
    <li>
      On $Bsuccess@, the function returns the address of the requested
      function. You have to cast it yourself into the correct type.
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
        $Sfuncname@ cannot be found inside $Splugin@.
      </p>
    </li>
  </ul>
  <br />
  <p>
    Logs written by this function are tagged with the $L"plugin"@ label.
  </p>
</div>
<hr />

<div class="related_functions">
  <h3>Related functions</h3>
  <ul>
    <li>t_bunny_plugin</li>
    <li>bunny_new_plugin</li>
    <li>bunny_delete_plugin</li>
    <li>bunny_plugin_call</li>
    <li>bunny_plugin_callv</li>
  </ul>
</div>

