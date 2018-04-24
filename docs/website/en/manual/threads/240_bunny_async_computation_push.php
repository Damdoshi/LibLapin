<div class="prototype">
  $Tbool@ $Sbunny_async_computation_push@(
  $Tt_bunny_function@ $Sfunc@,
  $Tvoid@ *$Sdt@
  );
</div>
<hr />

<div class="resume">
  <h3>Description</h3>
  $A This function push a computation request inside the bunny loop thread pool.
</div>
<hr />

<div class="parameters">
  <h3>Parameters</h3>
  <ul>
    <li>
      $Tt_bunny_function@ $Sfunc@:<br />
      $A The function to compute with the second parameter as first parameter,
      and the loop data as second parameter.
    </li>
    <li>
      $Tvoid@ *$Sdt@:<br />
      $A The data to compute.
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
    <li>bunny_set_async_computation</li>
    <li>bunny_async_computation_foreach</li>
  </ul>
</div>

