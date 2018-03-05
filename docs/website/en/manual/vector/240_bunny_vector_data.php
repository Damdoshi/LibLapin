<div class="prototype">
  Macro
  $Ttype@ $Sbunny_vector_data@($Tt_bunny_vector@ *$Svector@, $Tsize_t@ $Sidx@, $Stype@);
</div>
<hr />

<div class="resume">
  <h3>Description</h3>
  $A Return the element at position idx in vector. The sent type must match the
  type sent at the vector construction. This macro can be used to read or write.
</div>
<hr />

<div class="parameters">
  <h3>Parameters</h3>
  <ul>
    <li>
      $Tt_bunny_vector@ *$Svector@:<br />
      $A The vector to extract informations from.
    </li>
    <li>
      $Tsize_t@ $Sidx@:<br />
      $A The index of the element you want to fetch. Must not be greater
      than the vector size minus 1.
    </li>
    <li>
      $Stype@:<br />
      $A The type of the element you want to fetch. It must match
      the type sent at the vector construction.
    </li>
  </ul>
</div>
<hr />

<div class="return">
  <h3>Return value</h3>
  <ul>
    <li>
      This function returns the element at position idx in vector.
    </li>
  </ul>
</div>

