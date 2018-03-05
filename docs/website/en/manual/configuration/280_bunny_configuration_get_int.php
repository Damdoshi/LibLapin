k<div class="prototype">
  $Tbool@ $Sbunny_configuration_get_int(
  $Tt_bunny_configuration@ *$Sconfiguration@,
  $Tint@ *$Sstorage_space@
  );
</div>
<hr />

<div class="resume">
  <h3>Description</h3>
  $A Get the value inside the sent node.<br />
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
      $Tint@ *$Sstorage_spcae@:<br />
      $A The space in which the value inside configuration will be saved.
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

<div class="related_functions">
  <h3>Related functions</h3>
  <ul>
    <li>bunny_configuration_access</li>
    <li>bunny_configuration_get_child</li>
    <li>bunny_configuration_get_case</li>
    <li>bunny_configuration_get</li>
    <li>bunny_configuration_get_string</li>
    <li>bunny_configuration_get_double</li>

    <li>bunny_configuration_go_get_node</li>
    <li>bunny_configuration_go_get</li>
    <li>bunny_configuration_go_get_string</li>
    <li>bunny_configuration_go_get_double</li>
    <li>bunny_configuration_go_get_int</li>
  </ul>
</div>

