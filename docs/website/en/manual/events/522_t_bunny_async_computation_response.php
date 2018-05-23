<div class="prototype">
  $Ktypedef@ $Tvoid@ (*$Tt_bunny_async_computation_response@)(
  $Tvoid@ *$Scomputed@,
  $Tvoid@ *$Sdata@
  );
</div>
<hr />

<div class="resume">
  <h3>Description</h3>
  $A The type of function called when an asynchronous computation requested is terminated.
</div>
<hr />

<div class="parameters">
  <h3>Parameters</h3>
  <ul>
    <li>
      $Tvoid@ *$Scomputed@:<br />
      $A The result of the asynchronous operation.
    </li>
    <li>
      $Tvoid@ *$Sdata@:<br />
      $A The data sent as the last parameter of bunny_loop or bunny_loop_mw.
    </li>
  </ul>
</div>

<div class="related_functions">
  <h3>Related functions</h3>
  <ul>
    <li>bunny_set_async_computation_response</li>
    <li>bunny_set_async_computation</li>
  </ul>
</div>

