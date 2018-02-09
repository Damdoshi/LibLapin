<div class="prototype">
  $Ktypedef struct@ $Ts_bunny_pool@<br />
  {<br />
  $A $Kconst@ $Tsize_t@ $Snmemb@;<br />
  $A $Kconst@ $Tsize_t@ $Selemsize@;<br />
  $A $Kconst@ $Tsize_t@ $Snbr_occupied@;<br />
  $A $Tvoid@ * $Kconst@ $Sdata@[];<br />
  <br />
  } $Tt_bunny_pool@;<br />
</div>
<hr />

<div class="resume">
  <h3>Description</h3>
  $A This partially abstract structure represents a pool of
  pre-reserved elements.
</div>
<hr />

<div class="parameters">
  <h3>Attributes</h3>
  <ul>
    <li>
      $Kconst@ $Tsize_t@ $Snmemb@:<br />
      $A The maximum size in elements of the pool.
    </li>
    <li>
      $Kconst@ $Tsize_t@ $Selemsize@:<br />
      $A The size in bytes of a single element.
    </li>
    <li>
      $Kconst@ $Tsize_t@ $Snbr_occupied@:<br />
      $A How many elements are currently reserved inside
      the pool.
    </li>
    <li>
      $Tvoid@ * $Kconst@ $Sdata@[]:<br />
      $A An array of pointer to the stored data. You can safely
      browse this field from index 0 to index $Snbr_occupied@ - 1.
    </li>
  </ul>
</div>
<hr />

<div class="related_functions">
  <h3>Related functions</h3>
  <ul>
    <li>bunny_new_pool</li>
    <li>bunny_delete_pool</li>
  </ul>
</div>
