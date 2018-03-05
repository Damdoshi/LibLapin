<div class="prototype">
  $Tt_bunny_threadpool@ *$Sbunny_new_threadpool@($Tsize_t@ $Ssize@);
</div>
<hr />

<div class="resume">
  <h3>Description</h3>
  $A Create $Ssize@ threads and generate a structure that represent them.
  <br />
  <br />
  The returned threadpool must be destroyed with bunny_delete_threadpool.
</div>
<hr />

<div class="parameters">
  <h3>Parameters</h3>
  <ul>
    <li>
      $Tsize_t@ $Ssize@:<br />
      $A The amount of threads you want to create.
    </li>
  </ul>
</div>
<hr />

<div class="return">
  <h3>Return value</h3>
  <ul>
    <li>
      On $Bsuccess@, the function returns the threadpool.
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
    Logs written by this function are tagged with the $L"thread"@ label.
  </p>
</div>
<hr />

<div class="related_functions">
  <h3>Related functions</h3>
  <ul>
    <li>bunny_delete_threadpool</li>
  </ul>
</div>

