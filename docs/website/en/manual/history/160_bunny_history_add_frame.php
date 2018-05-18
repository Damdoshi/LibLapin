<div class="prototype">
  $Tsize_t@ $Sbunny_history_add_frame@(
  $Tt_bunny_history@ *$Shistory@,
  $Tsize_t@ $Stime@,
  $Kconst@ $Tvoid@ *$Sdata@);
</div>
<hr />

<div class="resume">
  <h3>Description</h3>
  $A This function create a copy of the sent $Sdata@ (which must be of
  size $Shistory->frame_size@, which is the value sent to bunny_new_history)
  and store it at time index $Stime@ in $Shistory@.<br />
  <br />
  If there was already a recorded frame, then no new allocation is made:
  the recorded data is overwritten.
</div>
<hr />

<div class="parameters">
  <h3>Parameters</h3>
  <ul>
    <li>
      $Tt_bunny_history@ *$Shistory@:<br />
      $A The history in which you will add a new record.
    </li>
    <li>
      $Tsize_t@ $Stime@:<br />
      $A The time index associated to the data you sent.
    </li>
    <li>
      $Kconst@ $Tvoid@ *$Sdata@:<br />
      $A The data that will be copied.
    </li>
  </ul>
</div>
<hr />

<div class="return">
  <h3>Return value</h3>
  <ul>
    <li>
      On $Bsuccess@, the function returns the amount of frames
      inside the history.
    </li>
    <li>
      On $Bfailure@, it returns 0.
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
    Logs written by this function are tagged with the $L"history"@ label.
  </p>
</div>
<hr />

<div class="related_functions">
  <h3>Related functions</h3>
  <ul>
    <li>bunny_history_get_frame</li>
    <li>bunny_history_clear</li>
  </ul>
</div>

