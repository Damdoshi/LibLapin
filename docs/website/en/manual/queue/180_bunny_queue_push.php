<div class="prototype">
  Macro
  $Tbool@ $Sbunny_queue_push@($Tt_bunny_queue@ *$Squeue@, $Sdata@);<br />
</div>
<hr />

<div class="resume">
  <h3>Description</h3>
  $A Push at the end of the Queue the sent data.
</div>
<hr />

<div class="parameters">
  <h3>Parameters</h3>
  <ul>
    <li>
      $Tt_bunny_queue@ *$Squeue@:<br />
      $A The Queue in which the data will be pushed.
    </li>
    <li>
      $Sdata@:<br />
      $A A data of any type that will be pushed at the end of the Queue.
    </li>
  </ul>
</div>
<hr />

<div class="return">
  <h3>Return value</h3>
  <ul>
    <li>
      This function return $Ctrue@ if the sent data was added inside
      the queue.
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

<div class="details">
  <h3>Additional informations</h3>
  <p>This macro wraps a call to a real function, which is:</p>
  <p>
    $Tbool@ $S_bunny_queue_push@($Tt_bunny_queue@ *$Squeue@, $Tvoid@ *$Sdata@);
  </p>
</div>

<div class="related_functions">
  <h3>Related functions</h3>
  <ul>
    <li>bunny_queue_pop</li>
  </ul>
</div>

