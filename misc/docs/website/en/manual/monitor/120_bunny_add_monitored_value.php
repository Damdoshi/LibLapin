<div class="prototype">
  <b>C11</b> Macro
  $Tbool@ $Sbunny_add_monitored_value@(
  $Kconst@ $Tchar@ *$Sname@,
  *$Sdata@
  );
</div>
<hr />

<div class="resume">
  <h3>Description</h3>
  $A Add inside the monitoring system the sent data.
  This macro is only available in C11 and is not available in C++.
  If you need to use this functionnality, you should call manually
  the function in which this macro is based.
</div>
<hr />

<div class="parameters">
  <h3>Parameters</h3>
  <ul>
    <li>
      $Kconst@ $Tchar@ *$Sname@:<br />
      $A The name of the monitored value.
    </li>
    <li>
      *$Sdata_pointer@:<br />
      $A A data to monitor. Supported types are $Tint@*, $Tdouble@*
      and $Tchar@*.
    </li>
  </ul>
</div>
<hr />

<div class="return">
  <h3>Return value</h3>
  <ul>
    <li>
      This function return $Ctrue@ if the sent data was added.
    </li>
  </ul>
</div>
<hr />

<div class="error_and_log">
  <h3>Error values and logs</h3>
  <p>
    On error, $Sbunny_errno@ is set to:
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
</div>
<hr />

<div class="details">
  <h3>Additional informations</h3>
  <p>This macro wraps a call to a real function, which is:</p>
  <p>
    $Tbool@ $S_bunny_add_monitored_value@(
    $Kconst@ $Tchar@ *$Sname@,
    $Tt_bunny_monitored_value@ $Stype@,
    $Kconst@ $Tvoid@ *$Sptr@
  </p>
</div>

<div class="related_functions">
  <h3>Related functions</h3>
  <ul>
    <li>bunny_remove_monitored_value</li>
    <li>bunny_display_monitored_value</li>
    <li>bunny_print_monitored_value</li>
  </ul>
</div>

