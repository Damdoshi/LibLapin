<div class="prototype">
  $Svoid@ *$Sbunny_pool_getv@(
  $Tt_bunny_pool@ *$Spool@,
  $Tsize_t@ *$Sid@
  );
</div>
<hr />

<div class="resume">
  <h3>Description</h3>
  $A Get an element from the pool.
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

<div class="related_functions">
  <h3>Related functions</h3>
  <ul>
    <li>bunny_pool_get</li>
  </ul>
</div>
