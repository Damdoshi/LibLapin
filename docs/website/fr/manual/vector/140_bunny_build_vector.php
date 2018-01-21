<div class="prototype">
  Macro
  $Tt_bunny_vector@ *$Sbunny_build_vector@
  ($Tsize_t@ $Snmemb@, $Stype@,
  $Tt_bunny_constructor@ $Sctor@,
  $Tt_bunny_destructor@ $Sdtor@,
  $Tvoid@ *$add@
  );
</div>
<hr />

<div class="resume">
  <h3>Description</h3>
  $A Create a Vector instance of nmemb elements of a specific type
  with specific rules for construction and destruction of elements inside.
  <br />
  <br />
  The returned vector must be freed with bunny_delete_vector.
</div>
<hr />

<div class="parameters">
  <h3>Parameters</h3>
  <ul>
    <li>
      $Tsize_t@ $Snmemb@:<br />
      $A The amount of elements inside the vector.
    </li>
    <li>
      $Stype@:<br />
      $A The type of elements inside the vector.
    </li>
    <li>
      $Tt_bunny_constructor@ $Sctor@,
      <br />
      $A The function that will be called when the vector needs to create a new
      element, when being created or when being resized.<br />
      $A $CNULL may be sent so no construction is made, only memory allocation.
    </li>
    <li>
      $Tt_bunny_destructor@ $Sdtor@,
      <br />
      $A The function that will be called when the vector needs to delete an
      element, when being deleted or when being resized.
      $A $CNULL may be sent so no destruction is made, only memory release.
    </li>
    <li>
      $Tvoid@ *$Sdata@:<br />
      $A A data that will be sent to the construction function while building
      the initial element. <b>This parameter is not stored!</b>
      $A If both ctor and dtor are NULL, this parameter is useless.
    </li>
  </ul>
</div>
<hr />

<div class="return">
  <h3>Return value</h3>
  <ul>
    <li>
      On $Bsuccess@, the function returns a vector instance.
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
    On error, $Sbunny_errno@ is set to:
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
    $Tt_bunny_vector@ *$S_bunny_new_vector@
    ($Tsize_t@ $Snmemb@, $Tsize_t@ $size@,
    $Tt_bunny_constructor@ $Sctor@,
    $Tt_bunny_destructor@ $Sdtor@,
    $Tvoid@ *$add@
    );
  </p>
</div>
<hr />

<div class="related_functions">
  <h3>Related functions</h3>
  <ul>
    <li>bunny_new_vector</li>
    <li>bunny_delete_vector</li>
  </ul>
</div>

