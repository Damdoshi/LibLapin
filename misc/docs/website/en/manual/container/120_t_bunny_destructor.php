<div class="prototype">
  $Ktypedef@ $Tbool@ (*$Tt_bunny_destructor@)(
  $Tvoid@ *$Sdata@
  );
</div>
<hr />

<div class="resume">
  <h3>Description</h3>
  $A This function pointer type is used by some containers to create
  destruction mechanisms and complete memory release in some ways, like
  in C++.
</div>
<hr />

<div class="parameters">
  <h3>Parameters</h3>
  <ul>
    <li>
      $Tvoid@ *$Sdata@:<br />
      $A The data to delete.
    </li>
  </ul>
</div>
<hr />

<div class="return">
  <h3>Return value</h3>
  <p>Returns $Ctrue@ on success. $Cfalse@ if something failed.</p>
</div>
<hr />

<div class="related_functions">
  <h3>Related functions</h3>
  <ul>
    <li>t_bunny_constructor</li>
  </ul>
</div>

