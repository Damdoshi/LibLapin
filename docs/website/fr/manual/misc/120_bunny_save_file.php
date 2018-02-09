<div class="prototype">
  $Tbool@ $Sbunny_save_file@(
  $Kconst@ $Tchar@ *$Sfile@,
  $Tvoid@ *$Sdata@,
  $Tsize_t@ $Ssize@
  );
</div>
<hr />

<div class="resume">
  <h3>Description</h3>
  $A Save $Ssize@ bytes from $Sdata@ into $Sfile@.
</div>
<hr />

<div class="parameters">
  <h3>Parameters</h3>
  <ul>
    <li>
      $Kconst@ $Tchar@ *$Sfile@:<br />
      $A The file to in which save.
    </li>
    <li>
      $Tvoid@ *$Sdata@:<br />
      $A The data to save.
    </li>
    <li>
      $Tsize_t@ $Ssize@:<br />
      $A The size of the data to save.
    </li>
  </ul>
</div>
<hr />

<div class="return">
  <h3>Return value</h3>
  <p>Return $Ctrue@ if everything went well.</p>
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
      Any errno code that can be set by open or write.
    </lI>
  </ul>
  <br />
  <p>
    Logs written by this function are tagged with the $L"file"@ or $L"ressource@ label.
  </p>
</div>
<hr />

<div class="related_functions">
  <h3>Related functions</h3>
  <ul>
    <li>bunny_load_file</li>
    <li>bunny_make_file_unique</li>
    <li>bunny_delete_file</li>
  </ul>
</div>

