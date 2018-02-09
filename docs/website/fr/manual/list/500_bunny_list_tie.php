<div class="prototype">
  Macro
  $Tt_bunny_vector@ *$Sbunny_list_tie@(
  $Kconst $Tt_bunny_list@ *$Slist@,
  $Stype@
  );
</div>
<hr />

<div class="resume">
  <h3>Description</h3>
  $A Generate a vector a copy of all elements inside the list.
</div>
<hr />

<div class="parameters">
  <h3>Parameters</h3>
  <ul>
    <li>
      $Tt_bunny_list@ *$Slist@:<br />
      $A The list to transform.
    </li>
    <li>
      $Stype@:<br />
      $A The type of the vector and of the data inside the list.
    </li>
  </ul>
</div>
<hr />

<div class="return">
  <h3>Return value</h3>
  <p>Return the newly created vector or $CNULL@ on error.</p>
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
    Logs written by this function are tagged with the $L"container"@ label.
  </p>
</div>
<hr />

<div class="details">
  <h3>Additional informations</h3>
  <p>This macro wraps a call to a real function, which is:</p>
  <p>
    $Tt_bunny_vector@ *$S_bunny_list_tie@(
    $Tt_bunny_list@ *$Slist@,
    $Tsize_t@ $Selemsize@
    );
  </p>
</div>
<hr />

<div class="related_functions">
  <h3>Related functions</h3>
  <ul>
    <li>bunny_vector_untie</li>
    <li>bunny_delete_vector</li>
  </ul>
</div>

