<div class="prototype">
  $Tbool@ $Sbunny_thread_push@(
  $Tt_bunny_threadpool@ *$Spool@,
  $Tt_bunny_function@ $Sfunc@,
  $Tvoid@ *$Sdata@,
  $Tvoid@ *$Sadd_ptr@
  );
</div>
<hr />

<div class="resume">
  <h3>Description</h3>
  $A Push a single work in the threadpool.
</div>
<hr />

<div class="parameters">
  <h3>Parameters</h3>
  <ul>
    <li>
      $Tt_bunny_threadpool@ *$Spool@:<br />
      $A The threadpool that will be use.
    </li>
    <li>
      $Tt_bunny_function@ $Sfunc@:<br />
      $A The function that will be called by the thread to treat $Sdata@.
    </li>
    <li>
      $Tvoid@ *$Sdata@:<br />
      $A The data to be treated by $Sfunc@ asynchronously in a different thread.
    </li>
    <li>
      $Tvoid@ *$Sadd_ptr@:<br />
      $A A data that will be sent as second parameter of $Sfunc@.
    </li>
  </ul>
</div>
<hr />

<div class="return">
  <h3>Return value</h3>
  <ul>
    <li>
      On $Bsuccess@, the function returns $Ctrue@.
    </li>
    <li>
      On $Bfailure@, it returns $Cfalse@.
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
    Logs written by this function are tagged with the $L"thread"@ label.
  </p>
</div>
<hr />

<div class="related_functions">
  <h3>Related functions</h3>
  <ul>
    <li>bunny_thread_foreach</li>
    <li>bunny_thread_wait_completion</li>
  </ul>
</div>

