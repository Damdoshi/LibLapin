<div class="prototype">
  $Tt_bunny_history@ *$Sbunny_new_history@($Tsize_t@ $Sframe_size@);
</div>
<hr />

<div class="resume">
  <h3>Description</h3>
  $A This function create a state recorder for a data with a specified size.
  <br />
  <br />
  The returned memory space must be freed with bunny_delete_history.
</div>
<hr />

<div class="parameters">
  <h3>Parameters</h3>
  <ul>
    <li>
      $Tsize_t@ $Sframe_size@:<br />
      $A The size of the structure that will be snapshoted in history.
    </li>
  </ul>
</div>
<hr />

<div class="return">
  <h3>Return value</h3>
  <ul>
    <li>
      On $Bsuccess@, the function returns the address of a t_bunny_history
      structure with zeroed fields, except for $Sframe_size@ which with
      have the sent value.
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
    Logs written by this function are tagged with the $L"history"@ label.
  </p>
</div>
<hr />

<div class="related_functions">
  <h3>Related functions</h3>
  <ul>
    <li>t_bunny_history</li>
    <li>bunny_delete_history</li>
  </ul>
</div>

