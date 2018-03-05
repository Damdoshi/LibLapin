<div class="prototype">
  $Ktypedef@ $Tint@ (*$Tt_bunny_map_cmp@)(
  $Kconst@ $Tvoid@ *$Sa@,
  $Kconst@ $Tvoid@ *$Sb@,
  $Tvoid@ *$Sparam@
  );
</div>
<hr />

<div class="resume">
  <h3>Description</h3>
  $ This function pointer type is part of the t_bunny_map structure
  and is useful to compare two <b>keys</b> in order to search or sort
  items in the map container.<br />
  <br />
  If this pointer is not set, then keys will be compared as size_t.
</div>
<hr />

<div class="parameters">
  <h3>Parameters</h3>
  <ul>
    <li>
      $Tvoid@ *$Sa@:<br />
      $A The element to compare with $Sb@.
    </li>
    <li>
      $Tvoid@ *$Sb@:<br />
      $A The element to compare with $Sa@.
    </li>
    <li>
      $Tvoid@ *$Sparam@:<br />
      $A An arbitrary parameter defined as $Sparam@ in t_bunny_map.
    </li>
  </ul>
</div>
<hr />

<div class="return">
  <h3>Return value</h3>
  <p>
    Return a positive integer if $Sa@ is greater tha $Sb@. Equal to zero
    if they are equal. Negative if $Sb@ is greater than $Sa@.<br />
  </p>
</div>

<div class="related_functions">
  <h3>Related functions</h3>
  <ul>
    <li>t_bunny_map_dup</li>
    <li>t_bunny_map_del</li>
    <li>t_bunny_map</li>
    <li>bunny_new_map</li>
    <li>bunny_delete_map</li>
  </ul>
</div>

