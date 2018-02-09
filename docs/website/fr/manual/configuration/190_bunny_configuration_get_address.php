<div class="prototype">
  $Kconst@ $Tchar@ *$Sbunny_configuration_get_address(
  $Kconst@ $Tt_bunny_configuration@ *$Sconfiguration@
  );
</div>
<hr />

<div class="resume">
  <h3>Description</h3>
  $A Get the address of the sent node. '.' is the character that signals
  a hashmap entering. '[' and ']' signals an array index.
</div>
<hr />

<div class="parameters">
  <h3>Parameters</h3>
  <ul>
    <li>
      $Kconst@ $Tt_bunny_configuration_type@ $Stype@:<br />
      $A The configuration to inspect.
    </li>
  </ul>
</div>
<hr />

<div class="return">
  <h3>Return value</h3>
  <p>Returns the address of the sent node. "" is the sent node is the root one.
</div>
<hr />

<div class="related_functions">
  <h3>Related functions</h3>
  <ul>
    <li>bunny_configuration_get_parent</li>
    <li>bunny_configuration_get_root</li>
    <li>bunny_configuration_get_address</li>
    <li>bunny_configuration_get_nbr_child</li>
    <li>bunny_configuration_get_nbr_case</li>
  </ul>
</div>

