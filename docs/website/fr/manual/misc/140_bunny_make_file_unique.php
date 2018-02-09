k<div class="prototype">
  $Tbool@ $Sbunny_make_file_unique@(
  $Kconst@ $Tchar@ *$Sfile@,
  $Kconst@ $Tvoid@ *$Sdata@,
  $Tsize_t@ $Slength@
  );
</div>
<hr />

<div class="resume">
  <h3>Description</h3>
  $A In the bunny library, some bottom level ressources are shared. This means
  that when you load several times the same file, the content of the file
  itself is only loaded once and then it is given to multiples holders.<br />
  <br />
  Sometimes, you only base your work on a file but plan to edit
  it to create a new one... And editing it would edit all files used
  by all other holders, so before doing it, you will need to call
  bunny_make_file_unique so your file got duplicated and pulled
  out the ressource manager.<br />
</div>
<hr />

<div class="parameters">
  <h3>Parameters</h3>
  <ul>
    <li>
      $Kconst@ $Tchar@ *$Sfile@:<br />
      $A The name of the file you want to turn unique.
    </li>
    <li>
      $Kconst@ $Tvoid@ *$Sdata@:<br />
      $A The data of the file.
    </li>
    <li>
      $Tsize_t@ $Slength@:<br />
      $A The size of the data of the file you want to turn unique.
    </li>
  </ul>
</div>
<hr />

<div class="return">
  <h3>Return value</h3>
  <p>
    Return the data turned unique. $CNULL@ on error.
  </p>
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
        Out of memory.<br />
      </p>
    </li>
  </ul>
  <br />
  <p>
    Logs written by this function or subfunctions may be tagged with
    $L"allocator"@ label.
  </p>
</div>
<hr />

<div class="related_functions">
  <h3>Related functions</h3>
  <ul>
    <li>bunny_load_file</li>
    <li>bunny_save_file</li>
    <li>bunny_delete_file</li>
  </ul>
</div>

