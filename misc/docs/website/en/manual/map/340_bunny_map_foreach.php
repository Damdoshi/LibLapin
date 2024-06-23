<div class="prototype">
  $Svoid@ $Sbunny_map_foreach@(
  $Tt_bunny_map@ *$Smap@,
  $Tvoid@ (*$Sfunction@)($Tt_bunny_map@ *$Smap@, $Tvoid@ *$Sparam@),
  $Tvoid@ *$Sparam@
  );
</div>
<hr />

<div class="resume">
  <h3>Description</h3>
  $A Call $Sfunction with every nodes of $Smap@ as first parameter,
  one after the other. Send $Sparam@ as second parameter.
</div>
<hr />

<div class="parameters">
  <h3>Parameters</h3>
  <ul>
    <li>
      $Tt_bunny_map@ *$Smap@:<br />
      $A The map that got the elements you want to be computed by
      bunny_map_foreach.
    </li>
    <li>
      $Tvoid@ (*$Tfunction@)($Tt_bunny_map@ *$Smap@, $Tvoid@ *$Sparam@):<br />
      $A The function to call with every nodes of the sent $Smap@.
    </li>
    <li>
      $Tvoid@ *$Sparam@:<br />
      $A The parameter sent to $Sfunction@ as the second one.
    </li>
  </ul>
</div>
<hr />

<div class="related_functions">
  <h3>Related functions</h3>
  <ul>
    <li>bunny_map_fast_foreach</li>
  </ul>
</div>

