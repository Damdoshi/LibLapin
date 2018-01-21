<div class="prototype">
  $Tvoid@ $Sbunny_vector_fast_foreach@(
  $Tt_bunny_threadpool@ *$Spool@,
  $Tt_bunny_vector@ *$Svector@,
  $Tt_bunny_vector_foreach@ $Sfunc@,
  $Tvoid@ *$Sparam@
  );
</div>
<hr />

<div class="resume">
  <h3>Description</h3>
  $A Call the sent function with, as first parameter,
  each elements inside the vector, one after the other,
  and with $Sparam@ as second element.<br />
  <br />
  Elements may be processed in separated threads, depending
  of the sent threadpool. The threadpool is created by
  bunny_new_threadpool.
</div>
<hr />

<div class="parameters">
  <h3>Parameters</h3>
  <ul>
    <li>
      $Tt_bunny_threadpool@ *$Sthread@:<br />
      $A The threadpool that contains the computational force
      that will be used to increase the speed of this function.
    </li>
    <li>
      $Tt_bunny_vector@ *$Svector@:<br />
      $A The vector to browse.
    </li>
    <li>
      $Tt_bunny_vector_foreach@ $Sfunc@:<br />
      $A The function that will be called with every elements.
    </li>
    <li>
      $Tvoid@ *$Sparam@:<br />
      $A A parameter to send to the callback function aside
      the element from the vector.
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
    Logs written by this function are tagged with the $L"container"@ label.
  </p>
</div>
<hr />

<div class="related_functions">
  <h3>Related functions</h3>
  <ul>
    <li>bunny_vector_foreach</li>
  </ul>
</div>

