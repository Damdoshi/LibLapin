<div class="prototype">
  $Tt_bunny_vector@ *$Sbunny_vector_resize@($Tt_bunny_vector@ *$Svec@, $Tsize_t@ $Snewsize@, $Tvoid@ *$Sadd@);
</div>
<hr />

<div class="resume">
  <h3>Description</h3>
  $A Resize the vector to fit a new amount of elements.
  If the new size of the vector is smaller than the previous one, there is no
  reallocation and the operation is fast. If it is greater, a reallocation
  followed by a copy may happen.<br />
  <br />
  If the vector is getting smaller, excessive elements will be sent
  to the destructor function that was defined if there was one.<br />
  <br />
  If the vector is getting greater, new elements will be built by being
  sent to the construction function that was defined if there was one.
  The $Sadd@ parameter will be sent too to the constructor.<br />
  <br />
  If you want to enforce reallocation when reducing the vector, you better
  use bunny_vector_crop after resizing it.
</div>
<hr />

<div class="parameters">
  <h3>Parameters</h3>
  <ul>
    <li>
      $Tt_bunny_vector@ *$Svec@:<br />
      $A The vector to resize.
    </li>
    <li>
      $Tsize_t@ $Snewsize@:<br />
      $A The new size of the vector.
    </li>
    <li>
      $Tvoid@ *$Sadd@:<br />
      $A A parameter to send to the constructor stored inside the
      vector if there is one. Il could be $CNULL@.
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
    <li>bunny_build_vector</li>
    <li>bunny_new_vector</li>
    <li>bunny_delete_vector</li>
  </ul>
</div>

