<div class="prototype">
  $Tvoid@ $Sbunny_set_error_descriptor@($Tint@ $Sfd@);
</div>
<hr />

<div class="resume">
  <h3>Description</h3>
  $A This function sets the file descirptor used for error logging.
  You can send a negative file descriptor to disable error logging.
  By default, the file descriptor used is $SSTDERR_FILENO@.
</div>
<hr />

<div class="parameters">
  <h3>Parameters</h3>
  <ul>
    <li>
      $Tint@ $Sfd@:<br />
      $A The file descriptor to use for error logging. By default, it is
      $SSTDERR_FILENO@. Sending -1 disable error logging.
    </li>
  </ul>
</div>
<hr />

<div class="related_functions">
  <h3>Related functions</h3>
  <ul>
    <li>bunny_get_error_descriptor</li>
    <li>bunny_set_log_descriptor</li>
    <li>bunny_get_log_descriptor</li>
  </ul>
</div>

