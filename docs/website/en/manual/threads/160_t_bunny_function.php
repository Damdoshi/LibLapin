<div class="prototype">
  $Ktypedef@ $Tvoid@ (*$Tt_bunny_function@)(
  $Tvoid@ *$Sdata@,
  $Tvoid@ *$Sadd_ptr@
  );
</div>
<hr />

<div class="resume">
  <h3>Description</h3>
  $A This function pointer is used by bunny_thread_foreach as
  target function for threaded collection computation.
</div>
<hr />

<div class="parameters">
  <h3>Parameters</h3>
  <ul>
    <li>
      $Tvoid@ *$Sdata@:<br />
      $A A data from a collection transmitted by bunny_thread_foreach.
    </li>
    <li>
      $Tvoid@ *$Sadd_ptr@:<br />
      $A A data directly sent from bunny_thread_foreach to the function,
      actually, the $Sadd_ptr@ from the function.
    </li>
  </ul>
</div>
<hr />

<div class="related_functions">
  <h3>Related functions</h3>
  <ul>
    <li>bunny_thread_foreach</li>
  </ul>
</div>

