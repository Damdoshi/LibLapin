<div class="prototype">
  $Tbool@ $Sbunny_plugin_call@(
  $Tt_bunny_plugin@ *$Splugin@,
  $Kconst@ $Tchar@ *$Sfuncname@,
  $Tt_bunny_value@ *$Sreturn_value@,
  $Tsize_t@ $Sparam_len@,
  $Tt_bunny_value@ *$Sparams@
  );
</div>
<hr />

<div class="resume">
  <h3>Description</h3>
  $A Call $Sfuncname@, a bunny plugin function from $Splugin with $Sparam_len@
  parameters from the array $Sparams@ and store the returned value inside
  $Sreturn_value@.
</div>
<hr />

<div class="parameters">
  <h3>Parameters</h3>
  <ul>
    <li>
      $Tt_bunny_plugin@ *$Splugin@:<br />
      $A The dynamic library in which $Sfuncname@ is.
    </li>
    <li>
      $Kconst@ $Tchar@ *$Sfuncname@:<br />
      $A The name of the function you want to call
    </li>
    <li>
      $Tt_bunny_value@ *$Sreturn_value@:<br />
      $A A space where to store the value that was returned by $Sfuncname@.
    </li>
    <li>
      $Tsize_t@ $Sparam_len@:<br />
      $A How many parameters there is inside $Sparams@.
    </li>
    <li>
      $Tt_bunny_value@ *$Sparams@:<br />
      $A Parameters to give to $Sfuncname@.
    </li>
  </ul>
</div>
<hr />

<div class="return">
  <h3>Return value</h3>
  <p>Return $Ctrue@ if the function was found and called.</p>
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
    <li>bunny_plugin_get_function</li>
    <li>bunny_plugin_callv</li>
  </ul>
</div>

