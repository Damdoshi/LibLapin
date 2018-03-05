<div class="prototype">
  $Ktypedef struct@ $Ts_bunny_node@<br />
  {<br />
  $Tvoid@ *$Sdata@;<br />
  $Tt_bunny_node@ * $Kconst@ $Snext@;<br />
  $Tt_bunny_node@ * $Kconst@ $Sprev@;<br />
  <br />
  } $Tt_bunny_node@;<br />
</div>
<hr />

<div class="resume">
  <h3>Description</h3>
  $A A linked list node. It is double linked list so you can get both neighboors.
</div>
<hr />

<div class="parameters">
  <h3>Attributes</h3>
  <ul>
    <li>
      $Tvoid@ *$Sdata@:<br />
      $A The data stored inside the node.
    </li>
    <li>
      $Tt_bunny_node@ * $Kconst@ $Snext@:<br />
      $A The next node. $CNULL@ if the current one is the last.
    </li>
    <li>
      $Tt_bunny_node@ * $Kconst@ $Sprev@:<br />
      $A The prev node. $CNULL@ if the current one is the first.
    </li>
  </ul>
</div>

