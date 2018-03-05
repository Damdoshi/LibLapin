<div class="prototype">
  $Ktypedef@ $Tvoid@ (*$Tt_bunny_function@)(
  $Tvoid@ *$Sdata@,
  $Tvoid@ *$Sadd_ptr@
  );
</div>
<hr />

<div class="resume">
  <h3>Description</h3>
  $A This function pointer is used by bunny_pool_foreach and
  bunny_pool_fast_foreach as target function single or multi-threaded
  pool computation.
</div>
<hr />

<div class="parameters">
  <h3>Parameters</h3>
  <ul>
    <li>
      $Tvoid@ *$Sdata@:<br />
      $A A data from a collection transmitted by bunny_pool_foreach
      or bunny_pool_fast_foreach.
    </li>
    <li>
      $Tvoid@ *$Sadd_ptr@:<br />
      $A A data directly sent from bunny_pool_foreach or
      bunny_pool_fast_foreach to the function,
      actually, the $Sparam@ from the function.
    </li>
  </ul>
</div>
<hr />

<div class="related_functions">
  <h3>Related functions</h3>
  <ul>
    <li>bunny_pool_foreach</li>
    <li>bunny_pool_fast_foreach</li>
  </ul>
</div>

