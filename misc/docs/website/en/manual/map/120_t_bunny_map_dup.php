<div class="prototype">
  $Ktypedef@ $Tvoid@ *(*$Tt_bunny_map_dup@)(
  $Kconst@ $Tvoid@ *$Sa@,
  $Tvoid@ *$Sparam@
  );
</div>
<hr />

<div class="resume">
  <h3>Description</h3>
  $ This function pointer type is part of the t_bunny_map structure
  and is useful to duplicate <b>keys</b>. Making this a deep
  copy or a shallow copy is up to you.<br />
  <br />
  If this pointer is not set, keys will not be duplicated when using
  functions like bunny_map_get_data or bunny_map_get_subtree and pointers
  parameters sent to those functions will be used <b>directly</b>, which
  can be dangerous if not considered.
</div>
<hr />

<div class="parameters">
  <h3>Parameters</h3>
  <ul>
    <li>
      $Tvoid@ *$Sa@:<br />
      $A The element to duplicate.
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
    $Sa@'s duplicata or $CNULL@ on error.
  </p>
</div>

<div class="related_functions">
  <h3>Related functions</h3>
  <ul>
    <li>t_bunny_map_cmp</li>
    <li>t_bunny_map_del</li>
    <li>t_bunny_map</li>
    <li>bunny_new_map</li>
    <li>bunny_delete_map</li>
  </ul>
</div>

