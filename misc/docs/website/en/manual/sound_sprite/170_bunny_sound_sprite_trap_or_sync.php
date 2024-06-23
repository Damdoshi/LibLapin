<div class="prototype">
  $Tvoid@ $Sbunny_sound_sprite_trap_or_sync@($Tbool@ $Strap@);
</div>
<hr />

<div class="resume">
  <h3>Description</h3>
  $A Indicates if you want to use the trap system from bunny_asynclock, which
  is working in the main thread.. or a thread from the asynchronous computation
  system in the bunny_loop threadpool.<br />
  <br />
  By default, the sound sprite module use the trap system.
  To use the threaded system, you must before create the bunny loop thread
  pool with bunny_set_async_computation. If this thread pool does not exists,
  even if you have requested to use it, it will use the trap system.
</div>
<hr />

<div class="parameters">
  <h3>Parameters</h3>
  <ul>
    <li>
      $Tbool@ $Strap@:<br />
      $A Send $Ctrue@ to use the asynclock system, $Cfalse@ for the threaded
      system.
    </li>
  </ul>
</div>
<hr />

<div class="related_functions">
  <h3>Related functions</h3>
  <ul>
    <li>bunny_sound_sprite_play_slice</li>
    <li>bunny_set_async_computation</li>
  </ul>
</div>

