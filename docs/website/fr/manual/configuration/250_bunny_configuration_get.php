<div class="prototype">
  <b>C11</b> Macro
  $Tbool@ $Sbunny_configuration_get(
  $Tt_bunny_configuration@ *$Sconfiguration@,
  $Sstorage_space@
  );
</div>
<hr />

<div class="resume">
  <h3>Description</h3>
  $A Get the value inside the sent node.<br />
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
      $Sstorage_space@:<br />
      $A This $Sstorage_space@ can be a $Kconst@ or not $Tchar@**, a $Tdouble@* or
      an $Tint@*. It will receive the data that was inside the configuration node.
    </li>
  </ul>
</div>
<hr />

<div class="return">
  <h3>Return value</h3>
  <p>
    Returns $Ctrue@ if a value was stored inside $Sstorage_space@ or $Cfalse@ if
    it was not.
  </p>
</div>
<hr />

<div class="details">
  <h3>Additional informations</h3>
  <p>This macro wraps several calls to real functions, which are:</p>
  <p>
    $Tbool@ $Sbunny_configuration_get_string@(
    $Tt_bunny_configuration@ *$Sconfiguration@,
    $Kconst@ $Tchar@ **$Sstorage@
    );
  </p>
  <p>
    $Tbool@ $Sbunny_configuration_get_double@(
    $Tt_bunny_configuration@ *$Sconfiguration@,
    $Tdouble@ *$Sstorage@
    );
  </p>
  <p>
    $Tbool@ $Sbunny_configuration_get_int@(
    $Tt_bunny_configuration@ *$Sconfiguration@,
    $Tint@ *$Sstorage@
    );
  </p>
</div>
<hr />

<div class="related_functions">
  <h3>Related functions</h3>
  <ul>
    <li>bunny_configuration_access</li>
    <li>bunny_configuration_get_child</li>
    <li>bunny_configuration_get_case</li>
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

