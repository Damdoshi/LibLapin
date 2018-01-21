<div class="prototype">
  $Ktypedef@ $Tvoid@ (*$Tt_bunny_vector_foreach@)(
  $Tvoid@ *$Snode@,
  $Tvoid@ *$Sparam@
  );
</div>
<hr />

<div class="resume">
  <h3>Description</h3>
  $A This function pointer is used by
  bunny_vector_foreach
  and
  bunny_vector_fast_foreach
  as they are called by them with elements from a vector
  as parameter.
</div>
<hr />

<div class="parameters">
  <h3>Parameters</h3>
  <ul>
    <li>
      $Tvoid@ *$Snode@:<br />
      $A A node from a vector.
    </li>
    <li>
      $Tvoid@ *$Sparam@:<br />
      $A A parameter sent throught
      bunny_vector_foreach
      or
      bunny_vector_fast_foreach.
    </li>

  </ul>
</div>
<hr />

<div class="related_functions">
  <h3>Related functions</h3>
  <ul>
    <li>bunny_vector_foreach</li>
    <li>bunny_vector_fast_foreach</li>
  </ul>
</div>
