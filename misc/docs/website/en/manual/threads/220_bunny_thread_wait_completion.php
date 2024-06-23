<div class="prototype">
  $Tvoid@ $Sbunny_thread_wait_completion@(
  $Tt_bunny_threadpool@ *$Spool@
  );
</div>
<hr />

<div class="resume">
  <h3>Description</h3>
  $A Wait until all works are complete and there is no more awaiting work
  in the threadpool queue.
</div>
<hr />

<div class="parameters">
  <h3>Parameters</h3>
  <ul>
    <li>
      $Tt_bunny_threadpool@ *$Spool@:<br />
      $A The threadpool we want to wait the termination of all work.
    </li>
  </ul>
</div>
<hr />

<div class="related_functions">
  <h3>Related functions</h3>
  <ul>
    <li>bunny_thread_foreach</li>
    <li>bunny_thread_push</li>
  </ul>
</div>

