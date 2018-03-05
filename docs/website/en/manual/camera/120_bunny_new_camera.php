<div class="prototype">
  $Tt_bunny_camera@ *$Sbunny_new_camera@($T int@ $Scam_id@);
</div>
<hr />

<div class="resume">
  <h3>Description</h3>
  $A Start the camera matching the sent id. Return an object
  to represent it.
</div>
<hr />

<div class="parameters">
  <h3>Parameters</h3>
  <ul>
    <li>
      $T int @ $S cam_id@:<br />
      $A The id of the camera to start. 0 is often used.
    </li>
  </ul>
</div>
<hr />

<div class="return">
  <h3>Return value</h3>
  <ul>
    <li>
      On $Bsuccess@, the function returns a valid
      t_bunny_camera.
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
    On error, $Sbunny_errno@ is set to:
  </p>
  <br />
  <ul>
    <li>
      $CENOMEM@:<br />
      <p>
        Out of memory.
      </p>
    </li>
  </ul>
  <br />
  <p>
    Logs written by this function are tagged with the $L"camera"@ label.
  </p>
</div>
<hr />

<div class="related_functions">
  <h3>Related functions</h3>
  <ul>
    <li>bunny_delete_camera</li>
    <li>bunny_new_capture</li>
  </ul>
</div>

