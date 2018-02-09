<div class="prototype">
  $Tvoid@ $Sbunny_perror@($Kconst@ $Tchar@ *$Sstr@);
</div>
<hr />

<div class="resume">
  <h3>Description</h3>
  $A Print the sent string followed by ':', a space and the
  bunny_strerror string returned after sending it the current bunny_errno
  value.<br />
  If the sent value was $CNULL@, only the bunny_strerror message is displayed.
  <br />
  A final newline is printed at the end.
</div>
<hr />

<div class="parameters">
  <h3>Parameters</h3>
  <ul>
    <li>
      $Kconst@ $Tchar@ *$Sstr@:<br />
      $A The context of failure. A classic value is the name of the
      function that failed.
    </li>
  </ul>
</div>
<hr />

<div class="related_functions">
  <h3>Related functions</h3>
  <ul>
    <li>t_bunny_error</li>
    <li>bunny_strerror</li>
  </ul>
</div>

