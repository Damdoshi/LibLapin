<div class="prototype">
  Macro
  $Tt_bunny_vector@ *$Sbunny_new_vector@($Tsize_t@ $Snmemb@, $Stype@);
</div>
<hr />

<div class="resume">
  <h3>Description</h3>
  $A Create a Vector instance of nmemb element of specified type.
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
    <li>bunny_build_vector</li>
    <li>bunny_delete_vector</li>
  </ul>
</div>

