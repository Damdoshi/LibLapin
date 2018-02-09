<div class="prototype">
  $Tt_bunny_picture@ *$Sbunny_load_picture@(
  $Kconst@ $Tchar@ *$Sfile@
  );
</div>
<hr />

<div class="resume">
  <h3>Description</h3>
  $A Create a t_bunny_picture and fill its pixel with the content
  of the sent file.<br />
  <br />
  The sent picture can be a configuration file that match the t_bunny_clipable
  file format. This format is described in the t_bunny_clipable manual.<br />
  <br />
  $A The returned memory must be freed with bunny_delete_clipable.
</div>
<hr />

<div class="parameters">
  <h3>Parameters</h3>
  <ul>
    <li>
      $Kconst@ $Tchar@ *$Sfile@:<br />
      $A A picture or configuration file that will be loaded and written inside
      the returned t_bunny_picture.
    </li>
  </ul>
</div>
<hr />

<div class="return">
  <h3>Return value</h3>
  <ul>
    <li>
      On $Bsuccess@, the function returns the address of
      a valid t_bunny_picture.
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
    <li>
      $CEINVAL@:<br />
      <p>
        Cannot load the sent configuration file.
      </p>
    </li>
  </ul>
  <br />
  <p>
    Logs written by this function are tagged with the $L"graphics"@ or
    $L"ressource"@ or $L"syntax"@ label.
  </p>
</div>
<hr />

<div class="related_functions">
  <h3>Related functions</h3>
  <ul>
    <li>t_bunny_picture</li>
    <li>bunny_new_picture</li>
    <li>bunny_read_picture_id</li>
    <li>bunny_read_picture</li>
    <li>bunny_save_picture</li>
    <li>bunny_delete_clipable</li>
  </ul>
</div>

