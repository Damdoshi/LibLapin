<div class="prototype">
  $Tint@ $Sbunny_asynclock@(
  $Tdouble@ $Selapsed_time@,
  $Tt_bunny_call_order@ $Sorder@
  );
</div>
<hr />

<div class="resume">
  <h3>Description</h3>
  $A Browse traps are call associated functions if matching conditions
  are fulfilled.
</div>
<hr />

<div class="parameters">
  <h3>Parameters</h3>
  <ul>
    <li>
      $Tdouble@ $Selapsed_time@:<br />
      $A How much time passed since the last call of bunny_asynclock.
    </li>
    <li>
      $Tt_bunny_call_order@ $Sorder@:<br />
      $A Are we before or after the function call of the function
      that was defined by bunny_set_loop_main_function ?
    </li>
  </ul>
</div>
<hr />

<div class="return">
  <h3>Return value</h3>
  <p>
    Returns how my traps are still registered.
  </p>
</div>
<hr />

<div class="related_functions">
  <h3>Related functions</h3>
  <ul>
    <li>bunny_new_trap</li>
    <li>bunny_delete_trap</li>
    <li>bunny_loop</li>
  </ul>
</div>

