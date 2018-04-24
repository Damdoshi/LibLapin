<div class="prototype">
  $Tbool@ $Sbunny_set_async_computation@(
  $Tsize_t@ $Snbr_thread@
  );
</div>
<hr />

<div class="resume">
  <h3>Description</h3>
  $A Create a threadpool integrated to the bunny loop with the sent amount of
  thread.
</div>
<hr />

<div class="parameters">
  <h3>Parameters</h3>
  <ul>
    <li>
      $Tsize_t@ $Snbr_thread@:<br />
      $A The amount of threads inside the bunny loop thread pool. You can send
      0 to delete the threadpool.<br />
      If a threadpool was already present, it may be freed before a new one
      is created if it contains a different amount of threads.
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

<div class="related_functions">
  <h3>Related functions</h3>
  <ul>
    <li>bunny_async_computation_push</li>
    <li>bunny_async_computation_foreach</li>
  </ul>
</div>

