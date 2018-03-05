<div class="prototype">
  $Tt_bunny_capture@ *$Sbunny_new_capture@($Tt_bunny_camera@ *$Scamera@);
</div>
<hr />

<div class="resume">
  <h3>Description</h3>
  $A Store what the camera is currently seeing.
</div>
<hr />

<div class="parameters">
  <h3>Parameters</h3>
  <ul>
    <li>
      $T t_bunny_camera @ *$S camera @:<br />
      $A The camera you want to snapshot with.
    </li>
  </ul>
</div>
<hr />

<div class="return">
  <h3>Return value</h3>
  <ul>
    <li>
      On $Bsuccess@, the function returns a valid
      t_bunny_capture.
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
    <li>bunny_delete_capture</li>
    <li>bunny_capture</li>
    <li>bunny_capture_to_pixelarray</li>
  </ul>
</div>

