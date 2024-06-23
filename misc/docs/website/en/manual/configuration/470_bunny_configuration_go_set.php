<div class="prototype">
  <b>C11</b> Macro
  $Tbool@ $Sbunny_configuration_go_set(
  $Tt_bunny_configuration@ *$Sconfiguration@,
  $Sdata@,
  $Kconst@ $Tchar@ *$Saddress@
  );
</div>
<hr />

<div class="resume">
  <h3>Description</h3>
  $A Set to the node at the sent address the sent value. If the node does not
  exist and the create mode is on, the node is created.<br />
  <br />
  This macro is <b>only</b> available if you are using <b>C11</b> or a newer
  version of C. C++ does not support this macro.
</div>
<hr />

<div class="parameters">
  <h3>Parameters</h3>
  <ul>
    <li>
      $Tt_bunny_configuration_type@ $Stype@:<br />
      $A The configuration to inspect.
    </li>
    <li>
      $Sdata@:<br />
      $A This $Sdata@ can be a $Kconst@ $Tchar@*, a $Tdouble@ or
      an $Tint@. This is the data to assign to the requested node.
    </li>
    <li>
      $Kconst@ $Tchar@ *$Saddress@:<br />
      $A The address of the data you need.
    </li>
  </ul>
</div>
<hr />

<div class="return">
  <h3>Return value</h3>
  <p>
    Returns $Ctrue@ if a value was stored inside the node or $Cfalse@ if
    it was not.
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
    <li>
      $CBE_CANNOT_FIND_ELEMENT@:<br />
      <p>
        The node does not exists and cannot be created because the create mode is off.
      </p>
    </li>
  </ul>
  <br />
  <p>
    Logs written by this function are tagged with the $L"configuration"@ label.
  </p>
</div>
<hr />

<div class="details">
  <h3>Additional informations</h3>
  <p>This macro wraps several calls to real functions, which are:</p>
  <p>
    $Tt_bunny_configuration@ *$Sbunny_configuration_go_set_string(
    $Tt_bunny_configuration@ *$Sconfiguration@,
    $Kconst@ $Tchar@ *$Sdata@,
    $Kconst@ $Tchar@ *$Saddress@
    );
  </p>
  <p>
    $Tt_bunny_configuration@ *$Sbunny_configuration_go_set_double(
    $Tt_bunny_configuration@ *$Sconfiguration@,
    $Tdouble@ $Sdata@,
    $Kconst@ $Tchar@ *$Saddress@
    );
  </p>
  <p>
    $Tt_bunny_configuration@ *$Sbunny_configuration_go_set_int(
    $Tt_bunny_configuration@ *$Sconfiguration@,
    $Tint@ $Sdata@,
    $Kconst@ $Tchar@ *$Saddress@
    );
  </p>
</div>
<hr />

<div class="related_functions">
  <h3>Related functions</h3>
  <ul>
    <li>bunny_configuration_go_set_string</li>
    <li>bunny_configuration_go_set_double</li>
    <li>bunny_configuration_go_set_int</li>
  </ul>
</div>

