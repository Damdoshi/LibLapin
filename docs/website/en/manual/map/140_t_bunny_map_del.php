<div class="prototype">
  $Ktypedef@ $Tvoid@ (*$Tt_bunny_map_del@)(
  $Tvoid@ *$Sa@,
  $Tvoid@ *$Sparam@
  );
</div>
<hr />

<div class="resume">
  <h3>Description</h3>
  $ This function pointer type is part of the t_bunny_map structure
  and is useful to delete <b>keys</b>.<br />
  <br />
  It should be sent <b>only</b> if the t_bunny_map_dup functions
  was also set.
</div>
<hr />

<div class="parameters">
  <h3>Parameters</h3>
  <ul>
    <li>
      $Tvoid@ *$Sa@:<br />
      $A The element to free.
    </li>
    <li>
      $Tvoid@ *$Sparam@:<br />
      $A An arbitrary parameter defined as $Sparam@ in t_bunny_map.
    </li>
  </ul>
</div>
<hr />

<div class="related_functions">
  <h3>Related functions</h3>
  <ul>
    <li>t_bunny_map_cmp</li>
    <li>t_bunny_map_dup</li>
    <li>t_bunny_map</li>
    <li>bunny_new_map</li>
    <li>bunny_delete_map</li>
  </ul>
</div>

