<div class="prototype">
  $Tt_bunny_pixelarray@ *$Sbunny_read_pixelarray@(
  $Kconst@ $Tt_bunny_pixelarray@ *$Spixelarray@,
  $Kconst@ $Tchar@ *$Sfile@
  );
</div>
<hr />

<div class="resume">
  <h3>Description</h3>
  $A Save the sent pixelarray into a file.
</div>
<hr />

<div class="parameters">
  <h3>Parameters</h3>
  <ul>
    <li>
      $Kconst@ $Tt_bunny_pixelarray@ *$Spixelarray@:<br />
      $A The pixelarray to save.
    </li>
    <li>
      $Kconst@ $Tchar@ *$Sfile@:br />
      $A The file in which you will save. Supported formats are .png and .jpg.
    </li>
  </ul>
</div>
<hr />

<div class="return">
  <h3>Return value</h3>
  <ul>
    <li>
      On $Bsuccess@, the function returns $Ctrue@.
    </li>
    <li>
      On $Bfailure@, it returns $Cfalse@.
    </li>
  </ul>
</div>
<hr />

<div class="error_and_log">
  <h3>Logs</h3>
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
    <li>bunny_read_pixelarray_id</li>
    <li>bunny_read_pixelarray</li>
    <li>bunny_delete_clipable</li>
    <li>t_bunny_my_load_pixelarray</li>
    <li>gl_bunny_my_load_pixelarray</li>
    <li>t_bunny_my_read_pixelarray</li>
    <li>gl_bunny_my_read_pixelarray</li>
  </ul>
</div>

