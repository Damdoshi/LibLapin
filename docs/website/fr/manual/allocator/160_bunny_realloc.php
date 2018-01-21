
<div class="prototype">
  $Tvoid@ *$Sbunny_realloc@($Tvoid@ *$Sptr@, $Tsize_t@ $Ssize@);
</div>
<hr />

<div class="resume">
  <h3>Description</h3>
  $A Change the size of the sent memory block to $Ssize@ byte. If the
  new size is smaller than the old one, the sent pointer will be returned
  after changing its metadatas.<br />
  If the new size is larger, the returned pointer may be different from
  the sent one and the additionnal space will not be initialized.<br />
  <br />
  If $Ssize@ is equal to zero, the sent pointer will be freed.<br />
  If $Sptr@ is $CNULL@ and $Ssize@ not zero, a memory space is allocated.
  <br />
  <br />
  The returned memory space must be freed with bunny_free.
</div>
<hr />

<div class="parameters">
  <h3>Parameters</h3>
  <ul>
    <li>
      $Tvoid@ *$Sptr@:<br />
      $A The memory space to reallocate.
    </li>
    <li>
      $Tsize_t@ $Ssize@:<br />
      $A The new size of the memory space.
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
      On $Bfailure@, it returns $CNULL@. The sent memory space is untouched.
    </li>
  </ul>
</div>
<hr />

<div class="error_and_log">
  <h3>Error values, errors and logs</h3>
  <p>
    If the sent address is invalid, a SIGSEGV signal will be sent to your
    program if $CBUNNY_ALLOCATOR_DEACTIVATED was set at compile time.
  </p>
  <br />
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
      If $CBUNNY_ALLOCATOR_DEACTIVATED@ is set, bunny_calloc become a wrapper
      around a call to calloc with an additionnal log output.
    </li>
    <li>
      If $CBUNNY_ALLOCATOR_DEACTIVATED@ is not set, bunny_calloc allocates
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

