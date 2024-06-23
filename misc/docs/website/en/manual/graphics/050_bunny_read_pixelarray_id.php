<div class="prototype">
  $Tt_bunny_pixelarray@ *$Sbunny_read_pixelarray_id@(
  $Kconst@ $Tvoid@ *$Sbuffer@,
  $Tsize_t@ $Slength@,
  $Kconst@ $Tchar@ *$Sfrom_file@
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
    <li>
      $Kconst@ $Tchar@ *$Sfrom_file@:<br />
      $A The file from which $Sbuffer@ is extracted. $CNULL@ is acceptable,
      but it will prevent the ressource manager to index this picture.
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

<div class="related_functions">
  <h3>Related functions</h3>
  <ul>
    <li>t_bunny_pixelarray</li>
    <li>bunny_new_pixelarray</li>
    <li>bunny_load_pixelarray</li>
    <li>bunny_read_pixelarray</li>
    <li>bunny_save_pixelarray</li>
    <li>bunny_delete_clipable</li>
  </ul>
</div>

