<div class="prototype">
  $Tt_bunny_pixelarray@ *$Sbunny_capture_new_pixelarray@(
  $Kconst@ $T t_bunny_capture@ *$Scapture@
  );
</div>
<hr />

<div class="resume">
  <h3>Description</h3>
  $A Convert the capture into a new pixelarray.
</div>
<hr />

<div class="parameters">
  <h3>Parameters</h3>
  <ul>
    <li>
      $Kconst@ $T t_bunny_capture @ *$S capture @:<br />
      $A The capture to transform into a pixelarray.
    </li>
  </ul>
</div>
<hr />

<div class="return">
  <h3>Return value</h3>
  <ul>
    <li>
      On $Bsuccess@, the function returns a new pixelarray.
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
    <li>bunny_new_capture</li>
    <li>bunny_capture</li>
    <li>bunny_capture_new_picture</li>
    <li>bunny_capture_to_pixelarray</li>
    <li>bunny_capture_to_picture</li>
  </ul>
</div>

