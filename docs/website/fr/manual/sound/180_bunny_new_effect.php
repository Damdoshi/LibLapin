<div class="prototype">
  $Tt_bunny_effect@ *$Sbunny_new_effect@($Tdouble@ $Sduration@);
</div>
<hr />

<div class="resume">
  <h3>Description</h3>
  $A Create a sound effect of the sent duration in seconds. It means in practice
  that its t_bunny_effect $Ssample@ buffer will have $Sduration@ *
  SAMPLE_PER_SECONDS signed short ints to describe the sound.
  <br />
  <br />
  Delete the sound file with bunny_delete_sound when you do not
  need it anymore.
</div>
<hr />

<div class="parameters">
  <h3>Parameters</h3>
  <ul>
    <li>
      $Tdouble@ $Sduration@:<br />
      $A The duration of the generated sound in seconds.
    </li>
  </ul>
</div>
<hr />

<div class="return">
  <h3>Return value</h3>
  <ul>
    <li>
      On $Bsuccess@, the function returns a valid t_bunny_effect pointer.
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
    Logs written by this function or subfunctions may be tagged with
    $L"ressource"@ or
    $L"sound"@
    labels.
  </p>
</div>
<hr />

<div class="related_functions">
  <h3>Related functions</h3>
  <ul>
    <li>bunny_delete_sound</li>
    <li>bunny_sound_play</li>
    <li>bunny_sound_stop</li>
    <li>t_bunny_sound_manager</li>
  </ul>
</div>

