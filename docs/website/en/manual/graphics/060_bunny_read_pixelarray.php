<div class="prototype">
  Macro
  $Tt_bunny_pixelarray@ *$Sbunny_read_pixelarray@(
  $Kconst@ $Tvoid@ *$Sbuffer@,
  $Tsize_t@ $Slength@
  );
</div>
<hr />

<div class="resume">
  <h3>Description</h3>
  $A Create a t_bunny_pixelarray and fill its pixel with the content
  of the sent memory space.<br />
  file format.<br />
  <br />
  $A The returned memory must be freed with bunny_delete_clipable.
</div>
<hr />

<div class="parameters">
  <h3>Parameters</h3>
  <ul>
    <li>
      $Kconst@ $Tvoid@ *$Sbuffer@:<br />
      $A The memory space containing the picture file.
    </li>
    <li>
      $Tsize_t@ $Slength@:<br />
      $A The size of $Sbuffer@ in bytes.
    </li>
  </ul>
</div>
<hr />

<div class="return">
  <h3>Return value</h3>
  <ul>
    <li>
      On $Bsuccess@, the function returns the address of
      a valid t_bunny_pixelarray.
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
    Logs written by this function are tagged with the $L"graphics"@ or
    $L"ressource"@ label.
  </p>
</div>
<hr />

<div class="details">
  <h3>Additional informations</h3>
  <p>This macro wraps a call to a real function, which is:</p>
  <p>
    $Tt_bunny_pixelarray@ *$Sbunny_read_pixelarray_id@(
    $Kconst@ $Tvoid@ *$Sbuffer@,
    $Tsize_t@ $Slength@,
    $Kconst@ $Tchar@ *$Sfrom_file@
    );
  </p>
  <p>
    The $Sfrom_file@ parameter will be given $CNULL@ as value by the
    buny_read_pixelarray macro.
  </p>
</div>
<hr />

<div class="related_functions">
  <h3>Related functions</h3>
  <ul>
    <li>t_bunny_pixelarray</li>
    <li>bunny_new_pixelarray</li>
    <li>bunny_load_pixelarray</li>
    <li>bunny_read_pixelarray_id</li>
    <li>bunny_save_pixelarray</li>
    <li>bunny_delete_clipable</li>
    <li>t_bunny_my_load_pixelarray</li>
    <li>gl_bunny_my_load_pixelarray</li>
    <li>t_bunny_my_read_pixelarray</li>
    <li>gl_bunny_my_read_pixelarray</li>
  </ul>
</div>

