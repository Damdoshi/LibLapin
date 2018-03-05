<div class="prototype">
  Macro
  $Tsize_t@ $Sbunny_pool_elem_index@(
  $Kconst@ $Tvoid@ *$Selement@
  );
</div>
<hr />

<div class="resume">
  <h3>Description</h3>
  $A Return the index of the sent element.<br />
  <b>Caution</b>: If the pointer is invalid, this will return an invalid
  value, your program may even crash.
</div>
<hr />

<div class="return">
  <h3>Return value</h3>
  <ul>
    <li>
      The index of the sent element in $Tt_bunny_pool@ $Sdata@[].
    </li>
  </ul>
</div>

<div class="related_functions">
  <h3>Related functions</h3>
  <ul>
    <li>bunny_pool_capacity</li>
    <li>bunny_pool_size</li>
    <li>bunny_pool_empty</li>
    <li>bunny_pool_elem_size</li>
  </ul>
</div>
