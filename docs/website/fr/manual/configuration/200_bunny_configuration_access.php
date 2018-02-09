<div class="prototype">
  <b>C11</b> Macro
  $Tt_bunny_configuration@ *$Sbunny_configuration_access(
  $Tt_bunny_configuration@ *$Sconfiguration@,
  $Sid@
  );
</div>
<hr />

<div class="resume">
  <h3>Description</h3>
  $A Get the node which is at the sent position.<br />
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
      $Sid@:<br />
      $A This $Sid@ can be a $Kconst@ or not $Tchar@*, a $Tsize_t@ or
      an $Tint@. If this is a numeral, a simple array resolution is made.
      If it is a string, an address resolution is made.
    </li>
  </ul>
</div>
<hr />

<div class="return">
  <h3>Return value</h3>
  <p>Returns the required node. Returning $CNULL@ if it does not exists
    and create mode is $Cfalse@.
</div>
<hr />

<div class="details">
  <h3>Additional informations</h3>
  <p>This macro wraps several calls to real functions, which are:</p>
  <p>
    $Tt_bunny_configuration@ *$Sbunny_configuration_go_get_node@(
    $Tt_bunny_configuration@ *$Sconfiguration@,
    $Kconst@ $Tchar@ *$Saddress@
    );
  </p>
  <p>
    $Tt_bunny_configuration@ *$Sbunny_configuration_get_case@(
    $Tt_bunny_configuration@ *$Sconfiguration@,
    $Tsize_t@ $Sindex@
    );
  </p>
</div>
<hr />

<div class="related_functions">
  <h3>Related functions</h3>
  <ul>
    <li>bunny_configuration_get_child</li>
    <li>bunny_configuration_get_case</li>
    <li>bunny_configuration_get</li>
    <li>bunny_configuration_get_string</li>
    <li>bunny_configuration_get_double</li>
    <li>bunny_configuration_get_int</li>

    <li>bunny_configuration_go_get</li>
    <li>bunny_configuration_go_get_node</li>
    <li>bunny_configuration_go_get_string</li>
    <li>bunny_configuration_go_get_double</li>
    <li>bunny_configuration_go_get_int</li>
  </ul>
</div>

