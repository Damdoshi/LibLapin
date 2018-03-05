<div class="prototype">
  $Kconst@ $Tchar@ *$Sbunny_strerror@($Tint@ $Serror_code@);
</div>
<hr />

<div class="resume">
  <h3>Description</h3>
  $A Return a human readable string that explain the sent error code.
</div>
<hr />

<div class="parameters">
  <h3>Parameters</h3>
  <ul>
    <li>
      $Tint@ $Serror_code@:<br />
      $A A errno/bunny_errno valid code, which includes errno classic
      codes and t_bunny_error code.
    </li>
  </ul>
</div>
<hr />

<div class="return">
  <h3>Return value</h3>
  <p>
    A human readable string explaining the error code, or $CNULL@ if the
    error code is invalid.
  </p>
</div>
<hr />

<div class="related_functions">
  <h3>Related functions</h3>
  <ul>
    <li>t_bunny_error</li>
    <li>bunny_perror</li>
  </ul>
</div>

