<div class="prototype">
  $Tt_bunny_vector@ *$Sbunny_vector_crop@($Tt_bunny_vector@ *$Svec@);
</div>
<hr />

<div class="resume">
  <h3>Description</h3>
  $A Force the inside memory chunk handled by the vector to fits its
  requested size, reallocating it if neccessary.
</div>
<hr />

<div class="parameters">
  <h3>Parameters</h3>
  <ul>
    <li>
      $Tt_bunny_vector@ *$Svec@:<br />
      $A The vector to crop.
    </li>
  </ul>
</div>
<hr />

<div class="return">
  <h3>Return value</h3>
  <ul>
    <li>
      On $Bsuccess@, the function returns the address of the vector.
      If the vector was reallocated then it is a new one and the sent
      one does not exist anymore.
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
        Out of memory.
      </p>
    </li>
  </ul>
  <br />
  <p>
    Logs written by this function are tagged with the $L"container"@ label.
  </p>
</div>
<hr />

<div class="related_functions">
  <h3>Related functions</h3>
  <ul>
    <li>bunny_resize_vector</li>
  </ul>
</div>

