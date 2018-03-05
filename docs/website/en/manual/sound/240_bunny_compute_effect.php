<div class="prototype">
  $Tbool@ $Sbunny_compute_effect@(
  $Tt_bunny_effect@ *$Seffect@
  );
</div>
<hr />

<div class="resume">
  <h3>Description</h3>
  $A Generate the sent sound effect in your sound card after what
  you have written into its buffer.
</div>
<hr />

<div class="parameters">
  <h3>Parameters</h3>
  <ul>
    <li>
      $Tt_bunny_effect@ *$Seffect@:<br />
      $A The sound effect to compute.
    </li>
  </ul>
</div>
<hr />

<div class="return">
  <h3>Return value</h3>
  <p>Returns $Ctrue@ on success.</p>
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
    Logs written by this function or subfunctions may be tagged with
    $L"sound"@
    labels.
  </p>
</div>
<hr />

<div class="related_functions">
  <h3>Related functions</h3>
  <ul>
    <li>bunny_new_effect</li>
    <li>bunny_load_effect</li>
  </ul>
</div>

