<div class="prototype">
  $Tbool@ $Sbunny_capture_to_picture@(
  $Kconst@ $T t_bunny_capture@ *$Scapture@,
  $Tt_bunny_pixelarray@ *$Spicture@
  );
</div>
<hr />

<div class="resume">
  <h3>Description</h3>
  $A Convert the capture into the sent picture.<br />
  This function creates a temporary t_bunny_pixelarray, so it is not
  faster than bunny_capture_new_pixelarray.
</div>
<hr />

<div class="parameters">
  <h3>Parameters</h3>
  <ul>
    <li>
      $Kconst@ $T t_bunny_capture @ *$S capture @:<br />
      $A The capture to transform into a picture.
    </li>
    <li>
      $T t_bunny_picture @ *$S picture @:<br />
      $A The target.
    </li>
  </ul>
</div>
<hr />

<div class="return">
  <h3>Return value</h3>
  <p>
    The function returns $Ctrue@ if it successed.
  </p>
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
    <li>
      $CEINVAL@:<br />
      <p>
        The sent capture was $CNULL@.
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
    <li>bunny_capture_to_pixelarray</li>
    <li>bunny_capture_new_pixelarray</li>
    <li>bunny_capture_new_picture</li>
  </ul>
</div>

