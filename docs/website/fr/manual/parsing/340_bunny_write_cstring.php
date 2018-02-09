<div class="prototype">
  $Tbool@ $Sbunny_read_rawstring@(
  $Kconst@ $Tchar@ *$Sstr@,
  $Tchar@ **$Sout@,
  $Tsize_t@ $Ssize@
  );
</div>
<hr />

<div class="resume">
  <h3>Description</h3>
  $A Write the sent string into a C-String format.
</div>
<hr />

<div class="parameters">
  <h3>Parameters</h3>
  <ul>
    <li>
      $Kconst@ $Tchar@ *$Sstr@:<br />
      $A The string to transform.
    </li>
    <li>
      $Tchar@ **$Sout@:<br />
      $A Where the generated string will be saved.<br />
      If *$Sout@ is $CNULL@, then a new string will be allocated
      and saved inside *$Sout@ and $Ssize@ will be ignored.<br />
      If *$Sout@ is not $CNULL@, then this space will be used to
      store the generated string, until $Ssize@ is reached.<br />
      <br />
      The allocated string is inside the bunny memory space (if activated)
      so it must be freed with bunny_free.
    </li>
    <li>
      $Tsize_t@ $Ssize@:<br />
      $A The size of *$Sout@ if *$Sout@ is not $CNULL@.
    </li>
  </ul>
</div>
<hr />

<div class="return">
  <h3>Return value</h3>
  <p>
    $Ctrue@ if the string was generated. $Cfalse@ on error.
  </p>
</div>
<hr />

<div class="error_and_log">
  <h3>Error values and logs</h3>
  <p>
    On error, $Vbunny_errno@ is set to:
  </p>
  <br />
  <ul>
    <li>
      $CENOMEM@:<br />
      <p>
        Out of memory.
      </p>
    </li>
  </ul>
</div>

<div class="related_functions">
  <h3>Related functions</h3>
  <ul>
    <li>bunny_read_cstring</li>
  </ul>
</div>

