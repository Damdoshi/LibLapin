<div class="prototype">
  $Tbool@ $Sbunny_pool_fast_foreach@(
  $Tt_bunny_threadpool@ *$Sthreadpool@,
  $Tt_bunny_pool@ *$Spool@,
  $Tt_bunny_pool_foreach@ $Sfunction@,
  $Tvoid@ *$Sparam@
  );
</div>
<hr />

<div class="resume">
  <h3>Description</h3>
  $A Execute the sent $Sfunction@ on each element of the sent $Spool@
  with threads from the threadpool $Sthreadpool@. Give to the executed function
  $Sparam@ as second parameter, data from $Spool@ being the first.
</div>
<hr />

<div class="parameters">
  <h3>Parameters</h3>
  <ul>
    <li>
      $Tt_bunny_threadpool@ *$Sthreadpool@:<br />
      $A The threadpool that will be use.
    </li>
    <li>
      $Tt_bunny_pool@ *$Spool@:<br />
      $A The collection that will be use.
    </li>
    <li>
      $Tt_bunny_function@ $Sfunction@:<br />
      $A The function that will be called for each element of the sent
      $Spool@. Parameters will be an element from the array and $Sparam@.
    </li>
    <li>
      $Tvoid@ *$Sparam@:<br />
      $A A data that will be sent as second parameter of $Sfunction@.
    </li>
  </ul>
</div>
<hr />

<div class="return">
  <h3>Return value</h3>
  <ul>
    <li>
      On complete $Bsuccess@, the function returns $Ctrue@.
    </li>
    <li>
      On $Bfailure@, it returns $Cfalse@. Failire indicates all
      datas were not treated by threads, some of them may have been
      treated by the main thread because of a thread pool memory exhaustion.
      Elements are always <b>all</b> computed.
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

<div class="related_functions">
  <h3>Related functions</h3>
  <ul>
    <li>t_bunny_pool_foreach</li>
    <li>bunny_pool_foreach</li>
  </ul>
</div>

