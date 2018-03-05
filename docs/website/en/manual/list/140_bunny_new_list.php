<div class="prototype">
  $Tt_bunny_list@ *$Sbunny_new_list@($Tvoid@);
</div>
<hr />

<div class="resume">
  <h3>Description</h3>
  $A Create a new empty list container.
  <br />
  <br />
  The returned memory space must be freed with bunny_delete_list.
</div>
<hr />

<div class="return">
  <h3>Return value</h3>
  <ul>
    <li>
      On $Bsuccess@, the function returns the address of a valid t_bunny_list.
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
    Logs written by this function are tagged with the $L"allocator"@ label.
  </p>
</div>
<hr />

<div class="related_functions">
  <h3>Related functions</h3>
  <ul>
    <li>bunny_delete_list</li>
  </ul>
</div>

