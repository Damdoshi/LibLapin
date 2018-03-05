<div class="prototype">
  $Ktypedef@ $Tint@ (*$Tt_bunny_comparator@)(
  $Kconst@ $Tvoid@ *$Sa@,
  $Kconst@ $Tvoid@ *$Sb@,
  $Tvoid@ *$Sparam@
  );
</div>
<hr />

<div class="resume">
  <h3>Description</h3>
  $A This function pointer is used by the function
  bunny_vector_sort
  to compare two elements and sort them.
</div>
<hr />

<div class="parameters">
  <h3>Parameters</h3>
  <ul>
    <li>
      $Kconst@ $Tvoid@ *$Sa@:<br />
      $A An element from a vector to be compared.
    </li>
    <li>
      $Kconst@ $Tvoid@ *$Sb@:<br />
      $A Another element from a vector to be compared.
    </li>
    <li>
      $Tvoid@ *$Sparam@:<br />
      $A A parameter sent throught bunny_vector_sort.
    </li>
  </ul>
</div>
<hr />

<div class="return">
  <h3>Return value</h3>
  <p>
    Return a negative value if the first parameter is smaller than
    the second one.<br />
    A zero value if they are equal.<br />
    A positive value if the first parameter is greater than the second one.
</div>
<hr />

<div class="related_functions">
  <h3>Related functions</h3>
  <ul>
    <li>bunny_vector_sort</li>
  </ul>
</div>
