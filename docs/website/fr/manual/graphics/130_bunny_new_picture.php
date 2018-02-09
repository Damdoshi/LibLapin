<div class="prototype">
  $Tt_bunny_picture@ *$Sbunny_new_picture@(
  $Tunsigned int@ $Swidth@,
  $Tunsigned int@ $Sheight@
  );
</div>
<hr />

<div class="resume">
  <h3>Description</h3>
  $A Create a virgin t_bunny_picture. By default, pixels are all filled
  with PINK2 color.<br />
  <br />
  $A The returned memory must be freed with bunny_delete_clipable.
</div>
<hr />

<div class="parameters">
  <h3>Parameters</h3>
  <ul>
    <li>
      $Tunsigned int@ $Swidth@:<br />
      $A The width of the picture in pixels.
    </li>
    <li>
      $Tunsigned int@ $Sheight@:<br />
      $A The height of the picture in pixels.
    </li>
  </ul>
</div>
<hr />

<div class="return">
  <h3>Return value</h3>
  <ul>
    <li>
      On $Bsuccess@, the function returns the address of
      a valid t_bunny_picture filled with PINK2.
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
        Out of memory.
      </p>
    </li>
  </ul>
  <br />
  <p>
    Logs written by this function are tagged with the $L"ressource"@ and
    $L"graphics"@ label.
  </p>
</div>
<hr />

<div class="related_functions">
  <h3>Related functions</h3>
  <ul>
    <li>t_bunny_picture</li>
    <li>bunny_load_picture</li>
    <li>bunny_read_picture_id</li>
    <li>bunny_read_picture</li>
    <li>bunny_delete_clipable</li>
  </ul>
</div>
