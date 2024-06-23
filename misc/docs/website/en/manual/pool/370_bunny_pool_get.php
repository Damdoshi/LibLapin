<div class="prototype">
  Macro
  $Stype@ $Sbunny_pool_get@(
  $Tt_bunny_pool@ *$Spool@,
  $Tsize_t@ *$Sid@,
  $Stype
  );
</div>
<hr />

<div class="resume">
  <h3>Description</h3>
  $A Get an element from the pool. The sent $Stype@ must
  match the type sent when creating the pool with bunny_new_pool.
  The index of the returned data is given throught $Sid@.
</div>
<hr />

<div class="return">
  <h3>Return value</h3>
  <ul>
    <li>
      The newly reserved element or $CNULL@ if there is no space left.
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
      Out of memory.
    </li>
  </ul>
</div>
<hr />

<div class="details">
  <h3>Additional informations</h3>
  <p>This macro wraps a call to a real function, which is:</p>
  <p>
    $Tvoid@ *$S_bunny_pool_getv@(
    $Tt_bunny_pool@ *$Spool@,
    $Tsize_t@ *$Sid@
    );
  </p>
</div>
<hr />

<div class="related_functions">
  <h3>Related functions</h3>
  <ul>
    <li>bunny_pool_getv</li>
  </ul>
</div>
