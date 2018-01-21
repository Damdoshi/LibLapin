<div class="prototype">
  $Tbool@ $Sbunny_thread_foreach@(
  $Tt_bunny_threadpool@ *$Spool@,
  $Tt_bunny_function@ $Sfunc@,
  $Tvoid@ **$Sdata@,
  $Tsize_t@ $Sdata_array_len@,
  $Tvoid@ *$Sadd_ptr@
  );
</div>
<hr />

<div class="resume">
  <h3>Description</h3>
  $A Split an array computation into threads to speed them.
  The main thread does not work with the other one, it goes on directly.
  You may call bunny_thread_wait_completion if you need to make it wait
  for the others to end their work.
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
      $A The function that will be called for each element of the sent
      array. Parameters will be an element from the array and the $Sadd_ptr@.
    </li>
    <li>
      $Tvoid@ **$Sdata@:<br />
      $A An array of pointers of $Sdata_array_len@. Elements from
      this array will be sent to the function given in $Sfunc@, one
      after the other, following the pace of threads.
    </li>
    <li>
      $Tsize_t@ $Sdata_array_len@:<br />
      $A The size of $Sdata@.
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
    <li>bunny_thread_push</li>
    <li>bunny_thread_wait_completion</li>
  </ul>
</div>

