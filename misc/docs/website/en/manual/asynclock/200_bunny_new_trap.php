<div class="prototype">
  $Tt_bunny_trap@ *$Sbunny_new_trap@(
  $Tt_bunny_trap_function@ $Sfunction@,
  $Tt_bunny_call_order@ $Sorder@,
  $Tdouble@ $Sstart_time@,
  $Tdouble@ $Sduration@,
  $Tvoid@ *$Sparam@
  );
</div>
<hr />

<div class="resume">
  <h3>Description</h3>
  $A Create a new trap and configure it.<br />
  <br />
  You can remove the trap by deleting it with bunny_delete_trap.
</div>
<hr />

<div class="parameters">
  <h3>Parameters</h3>
  <ul>
    <li>
      $Tt_bunny_trap_function@ $Sfunction@:<br />
      $A A function to call when the configured condition is fulfilled.
    </li>
    <li>
      $Tt_bunny_call_order@ $Sorder@:<br />
      $A Configure if the function is called before or after
      the function set by bunny_set_loop_main_function.
    </li>
    <li>
      $Tdouble@ $Sstart_time@:<br />
      $A The parameter $Sstart_time@ is in second when the trap
      can start to act, if it is positive.<br />
      $A If $Sstart_time@ is negative or zero, then instead
      of waiting a specific time to happen, the trap will wait
      that any other trap before him made their business.
    </li>
    <li>
      $Tdouble@ $Sduration@:<br />
      $A If $Sstart_time@ is positive, then the parameter act this way:
      <ul>
        <li>
          If $Sduration@ is superior to 0, each loop if the current time
          is between $Sstart_time and $Start_time@ + $Sduration@, the
          sent $Sfunction@ is called.
        </li>
        <li>
          If $Sduration@ is 0 or really close, the function will be called
          a single time after $Sstart_time@ and then never called again.
        </li>
        <li>
          If $Sduration is negative, then the function will be called
          every -$Sduration seconds if the curent time is greater than $Sstart_time@.
        </li>
      </ul>
      $A If $start_time@ is negative, it works the same way, except that
      there is no other $Sstart_time@ than where there is no more trap awaiting.
    </li>
    <li>
      $Tvoid@ *$Sparam@:<br />
      $A A parameter that will be sent as third parameter of $Sfunction@.
    </li>
  </ul>
</div>
<hr />

<div class="return">
  <h3>Return value</h3>
  <ul>
    <li>
      On $Bsuccess@, the function returns a valid t_bunny_trap.
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
    Logs written by this function are tagged with the $L"asynclock"@ label.
  </p>
</div>
<hr />

<div class="related_functions">
  <h3>Related functions</h3>
  <ul>
    <li>bunny_delete_trap</li>
    <li>bunny_asynclock</li>
    <li>bunny_loop</li>
  </ul>
</div>

