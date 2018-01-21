
<div class="prototype">
  $Tvoid@ *$Sbunny_calloc@($Tsize_t@ $Snmemb@, $Tsize_t@ $Ssize@);
</div>
<hr />

<div class="resume">
  <h3>Description</h3>
  $A Reserve memory space for an array of nmemb elements of size bytes each
  and returns a pointer to the allocated memory first byte.
  The memory is set to zero.
  If there is a not enough memory available, the function returns $CNULL@.
  <br />
  <br />
  The returned memory space must be freed with
  bunny_free.
</div>
<hr />

<div class="parameters">
  <h3>Parameters</h3>
  <ul>
    <li>
      $Tsize_t@ $Snmemb@:<br />
      $A The length of the returned array in case.
    </li>
    <li>
      $Tsize_t@ $Ssize@:<br />
      $A The length of a single case in byte.
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

