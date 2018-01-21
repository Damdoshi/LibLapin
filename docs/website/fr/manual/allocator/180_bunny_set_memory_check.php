<div class="prototype">
  $Tvoid@ $Sbunny_set_memory_check@($Tbool@ $Schk@);
</div>
<hr />

<div class="resume">
  <h3>Description</h3>
  $A This function allows you to ask a memory checkup at the end of your program.
  The amount of asked bytes, of chunks, how many of them remains, etc.<br />
  It also makes a memory check that will make your program crash if some invalid
  writes occured during the execution.
</div>
<hr />

<div class="parameters">
  <h3>Parameters</h3>
  <ul>
    <li>
      $Tbool@ $Schk@:<br />
      $A Activate or deactivate the memory check.
    </li>
  </ul>
</div>
<hr />

<div class="related_functions">
  <h3>Related functions</h3>
  <ul>
    <li>bunny_malloc</li>
    <li>bunny_calloc</li>
    <li>bunny_realloc</li>
    <li>bunny_free</li>
  </ul>
</div>

