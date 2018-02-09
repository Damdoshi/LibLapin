<div class="prototype">
  $Tsize_t@ $Sbunny_configuration_get_nbr_child(
  $Kconst@ $Tt_bunny_configuration@ *$Sconfiguration@,
  );
</div>
<hr />

<div class="resume">
  <h3>Description</h3>
  $A Get how many nodes are immediate children of $Sconfiguration@
  and can be accessed by name.
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
  <p>
    Returns the amount of children in $Sconfiguration@ that can be accessed
    by name.
  </p>
</div>
<hr />

<div class="related_functions">
  <h3>Related functions</h3>
  <ul>
    <li>bunny_configuration_get_parent</li>
    <li>bunny_configuration_get_root</li>
    <li>bunny_configuration_get_name</li>
    <li>bunny_configuration_get_address</li>
    <li>bunny_configuration_get_nbr_case</li>
  </ul>
</div>

