<div class="prototype">
  $Tvoid@ $Sbunny_vector_sort@($Tt_bunny_vector@ *$Svec@, $Tt_bunny_comparator@ $Scmp@, $Tvoid@ *$Sparam@);
</div>
<hr />

<div class="resume">
  <h3>Description</h3>
  $A This function sorts the sent vector in ascending order. The sent function
  pointer is used to compare two elements together, allowing you to compare
  complex elements.
</div>
<hr />

<div class="parameters">
  <h3>Parameters</h3>
  <ul>
    <li>
      $Tt_bunny_vector@ *$Svec@:<br />
      $A The vector to resize.
    </li>
    <li>
      $Tt_bunny_comparator@ $Scmp@:<br />
      $A The function pointer used to compare elements.
    </li>
    <li>
      $Tvoid@ *$Sadd@:<br />
      $A A parameter sent to the comparator function when
      comparing two elements.
    </li>
  </ul>
</div>
