<div class="prototype">
  $Svoid@ $Sbunny_map_foreach@(
  $Tt_bunny_list@ *$Slist@,
  $Tvoid@ (*$Sfunction@)($Tvoid@ *$Sdata@, $Tvoid@ *$Sparam@),
  $Tvoid@ *$Sparam@
  );
</div>
<hr />

<div class="resume">
  <h3>Description</h3>
  $A Call $Sfunction with every nodes of $Slist@ as first parameter,
  one after the other. Send $Sparam@ as second parameter.
</div>
<hr />

<div class="parameters">
  <h3>Parameters</h3>
  <ul>
    <li>
      $Tt_bunny_list@ *$Slist@:<br />
      $A The list that got the elements you want to be computed by
      bunny_list_foreach.
    </li>
    <li>
      $Tvoid@ (*$Tfunction@)($Tvoid@ *$Sdata@, $Tvoid@ *$Sparam@):<br />
      $A The function to call with every nodes of the sent $Slist@.
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
    <li>bunny_list_fast_foreach</li>
  </ul>
</div>

