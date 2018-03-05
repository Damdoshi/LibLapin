<div class="prototype">
  $Tvoid@ $Sbunny_free@($Tvoid@ *$Sdata@);
</div>
<hr />

<div class="resume">
  <h3>Description</h3>
  $A Release the sent memory space so it is made available for later.
</div>
<hr />

<div class="parameters">
  <h3>Parameters</h3>
  <ul>
    <li>
      $Tvoid@ *$Sdata@:<br />
      $A A memory space reserved with bunny_malloc, bunny_calloc, or bunny_realloc.
    </li>
  </ul>
</div>
<hr />

<div class="error_and_log">
  <h3>Error and logs</h3>
  <p>
    If the sent address is invalid, a SIGSEGV signal will be sent to your
    program if BUNNY_ALLOCATOR_DEACTIVATED was set at library compile time.
  </p>
  <br />
  <p>
    Logs written by this function are tagged with the $L"allocator"@ label.
  </p>
</div>
<hr />

<div class="details">
  <h3>Additional informations</h3>
  <h4>When compiling LibLapin:</h4>
  <ul>
    <li>
      If BUNNY_ALLOCATOR_DEACTIVATED is set, bunny_free become a wrapper
      around a call to free with an additionnal log output.
    </li>
  </ul>
</div>
<hr />

<div class="related_functions">
  <h3>Related functions</h3>
  <ul>
    <li>bunny_set_maximum_ram</li>
    <li>bunny_malloc</li>
  </ul>
</div>



