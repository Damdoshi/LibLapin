<div class="prototype">
  $Tt_bunny_configuration@ *$Sbunny_configuration_get_case(
  $Tt_bunny_configuration@ *$Sconfiguration@,
  $Tsize_t@ $Sindex@
  );
</div>
<hr />

<div class="resume">
  <h3>Description</h3>
  $A Get the node which is an immediate child of $Sconfiguration@ with
  the index $Sindex@.
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
      $Kconst@ $Tchar@ *$Schild@:<br />
      $A The $Sindex@ of the child from $Sconfiguration you want to get.
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

<div class="related_functions">
  <h3>Related functions</h3>
  <ul>
    <li>bunny_configuration_access</li>
    <li>bunny_configuration_get_child</li>
    <li>bunny_configuration_get</li>
    <li>bunny_configuration_get_string</li>
    <li>bunny_configuration_get_double</li>
    <li>bunny_configuration_get_int</li>
    <li>bunny_configuration_get_case</li>

    <li>bunny_configuration_go_get</li>
    <li>bunny_configuration_go_get_node</li>
    <li>bunny_configuration_go_get_string</li>
    <li>bunny_configuration_go_get_double</li>
    <li>bunny_configuration_go_get_int</li>
  </ul>
</div>

