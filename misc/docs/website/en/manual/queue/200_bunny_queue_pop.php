<div class="prototype">
  Macro
  $TType@ $Sbunny_queue_pop@($Tt_bunny_queue@ *$Squeue@, $Stype@);
</div>
<hr />

<div class="resume">
  <h3>Description</h3>
  $A Remove the front element from the sent Queue.
</div>
<hr />

<div class="parameters">
  <h3>Parameters</h3>
  <ul>
    <li>
      $Tt_bunny_queue@ *$Squeue@:<br />
      $A The Queue that will have its front element removed.
    </li>
  </ul>
</div>
<hr />

<div class="return">
  <h3>Return value</h3>
  <ul>
    <li>
      This function return the popped value or $CNULL@ if there was none.
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
      $BE_CONTAINER_IS_EMPTY@:<br />
      <p>
        The queue you tried to pop is empty.
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
    $Tvoid@ *$S_bunny_queue_pop@($Tt_bunny_queue@ *$Squeue@);
  </p>
</div>
<hr />

<div class="related_functions">
  <h3>Related functions</h3>
  <ul>
    <li>bunny_queue_push</li>
  </ul>
</div>

