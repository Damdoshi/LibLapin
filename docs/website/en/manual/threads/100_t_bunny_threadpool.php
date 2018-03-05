<div class="prototype">
  $Ktypedef struct@ $Ts_bunny_threadpool@<br />
  {<br />
  $A $Kconst@ $Tvoid@ * $Kconst@ $S_private@;<br />
  $A $Tsize_t@ $Snbr_threads@;<br />
  <br />
  } $Tt_bunny_threadpool@;<br />
</div>
<hr />

<div class="resume">
  <h3>Description</h3>
  $A This structure is an abstract type made to represent created threads.
</div>
<hr />

<div class="parameters">
  <h3>Attributes</h3>
  <ul>
    <li>
      $Kconst@ $Tvoid@ * $Kconst@ $S_private@:<br />
      $A Private attribute that must not be modified or a crash may happen.
    </li>
    <li>
      $Tsize_t@ $Snbr_threads@:<br >
      $A The amount of threads that this threadpool represents.
    </li>
  </ul>
</div>

<div class="related_functions">
  <h3>Related functions</h3>
  <ul>
    <li>bunny_new_threadpool</li>
    <li>bunny_delete_threadpool</li>
  </ul>
</div>
