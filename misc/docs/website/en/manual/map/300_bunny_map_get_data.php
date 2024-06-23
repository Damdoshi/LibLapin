<div class="prototype">
  Macro
  $Stype@ $Sbunny_map_get_data@(
  $Tt_bunny_map@ *$Smap@,
  $Skey@,
  $Stype@
  );
</div>
<hr />

<div class="resume">
  <h3>Description</h3>
  $A Get the data inside the sent $Smap@ at $Skey@, which is of type $Stype@.
</div>
<hr />

<div class="parameters">
  <h3>Parameters</h3>
  <ul>
    <li>
      $Tt_bunny_map@ *$Smap@:<br />
      $A The map node in which there is the data you want.
    </li>
    <li>
      $Skey@:<br />
      $A The key of the element you want to get.
    </li>
    <li>
      $Stype@:<br />
      $A The type of the data you want to get, any type is possible.
    </li>
  </ul>
</div>
<hr />

<div class="return">
  <h3>Return value</h3>
  <p>It returns the data inside the sent $Smap@ at $Skey@, of type $Stype@.
</div>
<hr />

<div class="details">
  <h3>Additional informations</h3>
  <p>This macro wraps a call to a real function, which is:</p>
  <p>
    $Tvoid@ *$S_bunny_map_get_data@($Tt_bunny_map@ *$Smap@, $Tvoid@ *$Skey@);
  </p>
</div>

<div class="related_functions">
  <h3>Related functions</h3>
  <ul>
    <li>bunny_map_get_subtree</li>
    <li>bunny_map_data</li>
    <li>bunny_map_set_data</li>
  </ul>
</div>

