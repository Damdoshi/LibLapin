<div class="prototype">
  $Tdouble@ $Sbunny_evaluate@(
  $Kconst@ $Tchar@ *$Soperation@,
  $Tt_bunny_configuration@ *$Senv@
  );
</div>
<hr />

<div class="resume">
  <h3>Description</h3>
  $A Compute the operation sent as first parameter. Supported operators are:
  +, -, *, /, >, <, >=, <=, !=, ==, ?: and parenthesis to modify priority.<br />
  It supports double and integers and variable and variable address.
</div>
<hr />

<div class="parameters">
  <h3>Parameters</h3>
  <ul>
    <li>
      $Kconst@ $Tchar@ *$Soperation@:<br />
      $A The operation to compute.
    </li>
    <li>
      $Tt_bunny_configuration@ *$Senv@:<br />
      $A Variables that can be used by the operation.
    </li>
  </ul>
</div>
<hr />

<div class="return">
  <h3>Return value</h3>
  <p>Return the result of the operation or nan($L""@) on error.
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
      $CBE_SYNTAX_ERROR@:<br />
      <p>
        There was a syntax error inside the operation.
      </p>
    </li>
  </ul>
  <br />
  <p>
    Logs written by this function are tagged with the $L"misc"@ label.
  </p>
</div>
<hr />

<div class="details">
  <h3>Additional informations</h3>
  <h4>When compiling LibLapin:</h4>
  <ul>
    <li>
      If $CLAPIN_ALLOCATOR_DEACTIVATED@ is set, bunny_malloc become a wrapper
      around a call to malloc with an additionnal log output.
    </li>
    <li>
      If $CLAPIN_ALLOCATOR_DEACTIVATED@ is not set, bunny_malloc allocates
      memory inside a special space with a delimited size.
    </li>
  </ul>
</div>
