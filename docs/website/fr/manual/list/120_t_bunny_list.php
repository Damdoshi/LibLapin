<div class="prototype">
  $Ktypedef struct@ $Ts_bunny_list@<br />
  {<br />
  $Kconst@ $Tsize_t@ $Slength@;<br />
  $Tt_bunny_node@ * $Kconst@ $Sfront@;<br />
  $Tt_bunny_node@ * $Kconst@ $Sback@;<br />
  <br />
  } $Tt_bunny_list@;<br />
</div>
<hr />

<div class="resume">
  <h3>Description</h3>
  $A The main structure of the list container.
</div>
<hr />

<div class="parameters">
  <h3>Attributes</h3>
  <ul>
    <li>
      $Kconst@ $Tsize_t@ $Slength@:<br />
      $A How many nodes inside the current list.
    </li>
    <li>
      $Tt_bunny_node@ * $Kconst@ $Sfront@:<br />
      $A The first node of the list. $CNULL@ if the list is empty.
    </li>
    <li>
      $Tt_bunny_node@ * $Kconst@ $Sback@:<br />
      $A The last node of the list. $CNULL@ if the list is empty.
    </li>
  </ul>
</div>

