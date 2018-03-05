<div class="prototype">
  $Tbool@ $Sbunny_remove_monitored_value@(
  $Kconst@ $Tchar@ *$Sname@,
  );
</div>
<hr />

<div class="resume">
  <h3>Description</h3>
  $A Remove a previously registered and monitored value.
</div>
<hr />

<div class="parameters">
  <h3>Parameters</h3>
  <ul>
    <li>
      $Kconst@ $Tchar@ *$Sname@:<br />
      $A The name of the monitored value. $CNULL@ to remove all values.
    </li>
  </ul>
</div>
<hr />

<div class="return">
  <h3>Return value</h3>
  <ul>
    <li>
      This function returns $Ctrue@ if the sent data was removed.
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
      $CBE_CANNOT_FIND_ELEMENT@:<br />
      <p>
        Cannot find the monitored value.
      </p>
    </li>
  </ul>
</div>
<hr />

<div class="related_functions">
  <h3>Related functions</h3>
  <ul>
    <li>bunny_add_monitored_value</li>
    <li>bunny_display_monitored_value</li>
    <li>bunny_print_monitored_value</li>
  </ul>
</div>

