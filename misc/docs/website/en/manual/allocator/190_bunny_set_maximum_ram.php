<div class="prototype">
  $Tvoid@ $Sbunny_set_maximum_ram@($Tsize_t@ $Sbytes@);
</div>
<hr />

<div class="resume">
  <h3>Description</h3>
  $A This function can only be called efficiently before any allocation
  made by the bunny library. It allows you to define a maximum heap size.<br />
  When the allocated memory reach this size, then allocation functions managed by
  the bunny library will start to fail.<br />
  <br />
  By default, it is 20MB.
</div>
<hr />

<div class="parameters">
  <h3>Parameters</h3>
  <ul>
    <li>
      $Tsize_t@ $Sbytes@:<br />
      $A The maximum size of the heap.
    </li>
  </ul>
</div>
<hr />

<div class="related_functions">
  <h3>Related functions</h3>
  <ul>
    <li>bunny_set_memory_check</li>
    <li>bunny_allocator_reset</li>
    <li>bunny_malloc_failure</li>
  </ul>
</div>

