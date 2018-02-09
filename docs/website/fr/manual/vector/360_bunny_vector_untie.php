<div class="prototype">
  $Tt_bunny_list@ *$Sbunny_vector_untie@($Kconst@ $Tt_bunny_vector@ *$Svec@);
</div>
<hr />

<div class="resume">
  <h3>Description</h3>
  $A Create a list containing the elements of the sent vector. All elements
  are duplicated with bunny_memdup so you can delete the vector freely.
  <br />
  <br />
  The returned list must be freed with bunny_delete_list.
</div>
<hr />

<div class="parameters">
  <h3>Parameters</h3>
  <ul>
    <li>
      $Kconst@ $Tt_bunny_vector@ *$Svec@:<br />
      $A The vector you want to duplicate the element and store into a list.
    </li>
  </ul>
</div>
<hr />

<div class="return">
  <h3>Return value</h3>
  <ul>
    <li>
      On $Bsuccess@, the function returns a list instance.
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

<div class="related_functions">
  <h3>Related functions</h3>
  <ul>
    <li>bunny_list_tie</li>
    <li>bunny_delete_list</li>
  </ul>
</div>
