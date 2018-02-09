<div class="prototype">
  <b>C11</b> Macro
  $Tvoid@ $Sbunny_configuration_get(
  $Tt_bunny_configuration@ *$Sconfiguration@,
  $Sdata@
  );
</div>
<hr />

<div class="resume">
  <h3>Description</h3>
  $A Set the value inside the sent node.<br />
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
      $A This $Sdata@ can be a $Kconst@ or not $Tchar@*, a $Tdouble@ or
      an $Tint@. It will be assigned to the sent node.
    </li>
  </ul>
</div>
<hr />

<div class="details">
  <h3>Additional informations</h3>
  <p>This macro wraps several calls to real functions, which are:</p>
  <p>
    $Tvoid@ $Sbunny_configuration_set_string@(
    $Tt_bunny_configuration@ *$Sconfiguration@,
    $Kconst@ $Tchar@ *$Sdata@
    );
  </p>
  <p>
    $Tvoid@ $Sbunny_configuration_set_double@(
    $Tt_bunny_configuration@ *$Sconfiguration@,
    $Tdouble@ $Sdata@
    );
  </p>
  <p>
    $Tvoid@ $Sbunny_configuration_set_int@(
    $Tt_bunny_configuration@ *$Sconfiguration@,
    $Tint@ $Sdata@
    );
  </p>
</div>
<hr />

<div class="related_functions">
  <h3>Related functions</h3>
  <ul>
    <li>bunny_configuration_set_string</li>
    <li>bunny_configuration_set_double</li>
    <li>bunny_configuration_set_int</li>
  </ul>
</div>

