<div class="prototype">
  $Tssize_t@ $Sbunny_load_file@(
  $Kconst@ $Tchar@ *$Sfile@,
  $Tvoid@ **$Sdata@,
  $Tsize_t@ *$Ssize@
  );
</div>
<hr />

<div class="resume">
  <h3>Description</h3>
  $A Load a full file. It could be a text or a binary file.<br />
  This file is managed by the ressource manager, like sound effects
  and pictures.
</div>
<hr />

<div class="parameters">
  <h3>Parameters</h3>
  <ul>
    <li>
      $Kconst@ $Tchar@ *$Sfile@:<br />
      $A The file to load.
    </li>
    <li>
      $Tvoid@ **$Sdata@:<br />
      $A A pointer to a pointer in which a memory space address with be saved.
      The memory space itself will be filled with the content of the file.
      The size of the memory space will be stored inside $Ssize@.
    </li>
    <li>
      $Tsize_t@ *$Ssize@:<br />
      $A A pointer to a space in which save the size of the loaded file.
      If set to $CNULL@, an additionnal '\0' will be added at the end of the data.
    </li>
  </ul>
</div>
<hr />

<div class="return">
  <h3>Return value</h3>
  <ul>
    <li>
      On $Bsuccess@, the function returns the size of the loaded data.
    </li>
    <li>
      On $Bfailure@, it returns -1.
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
    Logs written by this function are tagged with the $L"file"@ or $L"ressource@ label.
  </p>
</div>
<hr />

<div class="related_functions">
  <h3>Related functions</h3>
  <ul>
    <li>bunny_save_file</li>
    <li>bunny_make_file_unique</li>
    <li>bunny_delete_file</li>
  </ul>
</div>

