<div class="prototype">
  $Tt_bunny_map@ *$Sbunny_new_map@(
  $Tt_bunny_map_cmp@ $Scmp@,
  $Tt_bunny_map_dup@ $Sdup@,
  $Tt_bunny_map_del@ $Sdel@,
  $Tvoid@ *$Sparam@
  );
</div>
<hr />

<div class="resume">
  <h3>Description</h3>
  $A Create a t_bunny_map container. The returned value must be deleted
  with bunny_delete_map.
</div>
<hr />

<div class="parameters">
  <h3>Parameters</h3>
  <ul>
    <li>
      $Tt_bunny_map_cmp@ $Scmp@:<br />
      $A A function to compare keys. Can be $CNULL@.
    </li>
    <li>
      $Tt_bunny_map_dup@ $Sdup@:<br />
      $A A function to duplicate keys. Can be $CNULL@.
    </li>
    <li>
      $Tt_bunny_map_del@ $Sdel@:<br />
      $A A function to delete keys. Can be $CNULL@ if $Sdup@ was also $CNULL@.
    </li>
    <li>
      $Tvoid@ *$Sparam@:<br />
      $A An arbitrary value that will be sent as last parameter of
      $Scmp@, $Sdup@ and $Sdel@.
    </li>
  </ul>
</div>
<hr />

<div class="return">
  <h3>Return value</h3>
  <ul>
    <li>
      On $Bsuccess@, the function returns a valid t_bunny_map.
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
        Out of memory.<br />
      </p>
    </li>
  </ul>
  <br />
  <p>
    Logs written by this function are tagged with the $L"container"@ label.
  </p>
</div>
<hr />

<div class="related_functions">
  <h3>Related functions</h3>
  <ul>
    <li>t_bunny_map</li>
    <li>bunny_delete_map</li>
    <li>t_bunny_map_cmp</li>
    <li>t_bunny_map_dup</li>
    <li>t_bunny_map_del</li>
  </ul>
</div>

