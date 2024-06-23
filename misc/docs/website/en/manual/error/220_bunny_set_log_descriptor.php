<div class="prototype">
  $Tvoid@ $Sbunny_set_log_descriptor@($Tint@ $Sfd@);
</div>
<hr />

<div class="resume">
  <h3>Description</h3>
  $A This function sets the file descirptor used for standard logging.
  You can send a negative file descriptor to disable standard logging.
  By default, the file descriptor used is $SSTDOUT_FILENO@.
</div>
<hr />

<div class="parameters">
  <h3>Parameters</h3>
  <ul>
    <li>
      $Tint@ $Sfd@:<br />
      $A The file descriptor to use for standard logging. By default, it is
      $SSTDOUT_FILENO@. Sending -1 disable standard logging.
    </li>
  </ul>
</div>
<hr />

<div class="related_functions">
  <h3>Related functions</h3>
  <ul>
    <li>bunny_set_error_descriptor</li>
    <li>bunny_get_error_descriptor</li>
    <li>bunny_get_log_descriptor</li>
  </ul>
</div>

