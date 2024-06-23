<div class="prototype">
  $Ktypedef struct@ $Ts_bunny_queue@<br />
  {<br />
  $A $Kconst@ $Tsize_t@ $Slength@;<br />
  $A $Kconst@ $Tvoid@	* $Kconst@ * $Kconst@ $Sfront@;<br />
  <br />
  } $Tt_bunny_queue@;<br />
</div>
<hr />

<div class="resume">
  <h3>Description</h3>
  $A This structure is the main data of the Queue container.
</div>
<hr />

<div class="parameters">
  <h3>Attributes</h3>
  <ul>
    <li>
      $Kconst@ $Tsize_t@ $Slength@:<br />
      $A The amount of elements in the Queue container.
    </li>
    <li>
      $Kconst@ $Tvoid@	* $Kconst@ * $Kconst@ * $Stop@:<br />
      $A A pointer to the front data stored inside the queue.
      It is $CNULL@ if there is none.
    </li>
  </ul>
</div>

