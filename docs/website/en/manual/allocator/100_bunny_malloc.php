<div class="prototype">
  $Tvoid@ *$Sbunny_malloc@($Tsize_t@ $Ssize@);
</div>
<hr />

<div class="resume">
  <h3>Description</h3>
  $A Reserve the sent amount of bytes and return a pointer to it.
  If there is a not enough memory available, the function returns $CNULL@.
  <br />
  <br />
  The returned memory space must be freed with bunny_free.
</div>
<hr />

<div class="parameters">
  <h3>Parameters</h3>
  <ul>
    <li>
      $Tsize_t@ $Ssize@:<br />
      $A The amount of bytes to reserve.
    </li>
  </ul>
</div>
<hr />

<div class="return">
  <h3>Return value</h3>
  <ul>
    <li>
      On $Bsuccess@, the function returns the address of the first
      byte of the allocated data chunk.
    </li>
    <li>
      On $Bfailure@, it returns $CNULL@.
    </li>
  </ul>
</div>
<hr />

<div class="error_and_log">
  <h3>Error values and logs</h3>
  <p>
    On error, $Sbunny_errno@ is set to:
  </p>
  <br />
  <ul>
    <li>
      $CENOMEM@:<br />
      <p>
        Out of memory.<br />
        If $CBUNNY_ALLOCATOR_DEACTIVATED@ was not set at library compile time,
        it means the prereserved memory space is exhausted. See
        bunny_set_maximum_ram
        for more information about this prereserved memory space.
      </p>
    </li>
  </ul>
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
      If BUNNY_ALLOCATOR_DEACTIVATED is set, bunny_malloc become a wrapper
      around a call to malloc with an additionnal log output.
    </li>
    <li>
      If BUNNY_ALLOCATOR_DEACTIVATED is not set, bunny_malloc allocates
      memory inside a special space with a delimited size.
    </li>
  </ul>
</div>
<hr />

<div class="related_functions">
  <h3>Related functions</h3>
  <ul>
    <li>bunny_set_maximum_ram</li>
    <li>bunny_free</li>
  </ul>
</div>

