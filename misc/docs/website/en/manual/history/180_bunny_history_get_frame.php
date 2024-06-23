<div class="prototype">
  $Kconst@ $Tvoid@ *$Sbunny_history_get_frame@(
  $Tt_bunny_history@ *$Shistory@,
  $Tsize_t@ $Stime@);
</div>
<hr />

<div class="resume">
  <h3>Description</h3>
  $A This function returns the state at the sent time index. Note
  that it does not have to have a frame precisely at this time index:
  the state at the sent time index is the last recorded state at or
  before this index. Here is an exemple:
  <ul>
    <li>Time 0: Value is 10</li>
    <li>Time 3: Value is 5</li>
    <li>Time 7: Value is 9</li>
  </ul>
  If you request the value at time index 0, 1 or 2, you will get value 10.<br />
  If you request the value at time index 3, 4, 5 or 6, you will get value 5.<br />
  If you request the value at time index 7 or more, you will get value 9.<br />
</div>
<hr />

<div class="parameters">
  <h3>Parameters</h3>
  <ul>
    <li>
      $Tt_bunny_history@ *$Shistory@:<br />
      $A The history from which you want to get a record.
    </li>
    <li>
      $Tsize_t@ $Stime@:<br />
      $A The time index of the status you seek.
    </li>
  </ul>
</div>
<hr />

<div class="return">
  <h3>Return value</h3>
  <ul>
    <li>
      On $Bsuccess@, the function returns the data you have requested.
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
      $CBE_CANNOT_FIND_ELEMENT@:<br />
      <p>
        There is no status at the current time index.
        In most case, that means the time index is too old and that
        the status at this time was deleted to free memory space.
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
    <li>bunny_history_add_frame</li>
    <li>bunny_history_erase_before</li>
    <li>bunny_history_erase_after</li>
    <li>bunny_history_erase_frame</li>
  </ul>
</div>

