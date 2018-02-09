<div class="prototype">
  $Tbool@ $Sbunny_plugin_callv@(
  $Tt_bunny_plugin@ *$Splugin@,
  $Kconst@ $Tchar@ *$Sfuncname@,
  $Tt_bunny_value@ *$Sreturn_value@,
  $S...@
  );
</div>
<hr />

<div class="resume">
  <h3>Description</h3>
  $A Call $Sfuncname@, a bunny plugin function from $Splugin with parameters
  from $S... variadic parameters@ and store the returned value inside
  $Sreturn_value@.<br />
  <br />
  $S... variadic parameters@ are read thanks to the description of
  $Sfuncname@ registered inside $Splugin@. <b>Watch what you send!</b>
  It should be only made of t_bunny_value with specific fields written.
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
      $S...@:<br />
      $A Parameters to send to $Sfuncname@. Those are reads after the
      description of the function prototype of $Sfuncname@, described
      in a t_bunny_prototype stored inside $Splugin@.<br />
      <br />
      <b>Those parameters should all be t_bunny_value.<b> Some systems
      may make lucky conversion from native types to a union compatible
      format, but I currently cannot guarantee it, because I consider
      I did not have tested it enough.
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
    <li>bunny_plugin_call</li>
  </ul>
</div>

