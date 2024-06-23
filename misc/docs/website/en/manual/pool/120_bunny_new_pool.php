<div class="prototype">
  Macro
  $Tt_bunny_pool@ *$Sbunny_new_pool@(
  $Tsize_t@ $Snmemb@,
  $Stype
  );
</div>
<hr />

<div class="resume">
  <h3>Description</h3>
  $A Create a Pool for $Snmemb@ elements of $Stype@.
</div>
<hr />

<div class="return">
  <h3>Return value</h3>
  <ul>
    <li>
      Return a valid $Tt_bunny_pool@ pointer or $CNULL@ if
      an error occured.
    </li>
  </ul>
</div>

<div class="error_and_log">
  <h3>Error values and logs</h3>
  <p>
    On error, $Vbunny_errno@ is set to:
  </p>
  <br />
  <ul>
    <li>
      $CENOMEM@:<br />
      Out of memory.
    </li>
  </ul>
</div>
<hr />

<div class="details">
  <h3>Additional informations</h3>
  <p>This macro wraps a call to a real function, which is:</p>
  <p>
    $Tt_bunny_pool@ *$S_bunny_new_pool@(
    $Tsize_t@ $Snmemb@,
    $Tsize_t@ $Ssize@
    );
  </p>
</div>
<hr />

<div class="related_functions">
  <h3>Related functions</h3>
  <ul>
    <li>bunny_delete_pool</li>
    <li>bunny_pool_clear</li>
  </ul>
</div>
