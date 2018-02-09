<div class="prototype">
  $Tssize_t@ $Sbunny_print_monitored_value@(
  $Tint@ $Sfd@,
  $Kconst@ $Tchar@ *$Sname@,
  );
</div>
<hr />

<div class="resume">
  <h3>Description</h3>
  $A Write on the sent $Sfd@ the monitored value named $Sname@, or several
  values depending of what is inside $Sname@.
</div>
<hr />

<div class="parameters">
  <h3>Parameters</h3>
  <ul>
    <li>
      $Tint@ $Sfd@:<br />
      $A The file descriptor used for writing.
    </li>
    <li>
      $Kconst@ $Tchar@ *$Sname@:<br />
      $A The name of the monitored value to write.<br />
      $CNULL@ to write all values.<br />
      You can use the character '*' as ending joker.
    </li>
  </ul>
</div>
<hr />

<div class="return">
  <h3>Return value</h3>
  <ul>
    <li>
      Return how many characters was written. -1 on error.
    </li>
  </ul>
</div>
<hr />

<div class="error_and_log">
  <h3>Error values and logs</h3>
  <p>
    On error, $Sbunny_errno@ is set to any value write can set.
  </p>
</div>
<hr />

<div class="related_functions">
  <h3>Related functions</h3>
  <ul>
    <li>bunny_add_monitored_value</li>
    <li>bunny_display_monitored_value</li>
    <li>bunny_remove_monitored_value</li>
  </ul>
</div>

