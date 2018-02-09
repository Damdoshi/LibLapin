<div class="prototype">
  $Tt_bunny_configuration@ *$Sbunny_configuration_go_get_node_va(
  $Tt_bunny_configuration@ *$Sconfiguration@,
  $Tsize_t@ $Snbr_param@,
  $S...@
  );
</div>
<hr />

<div class="resume">
  <h3>Description</h3>
  $A Get the node which is at the sent address.
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
      $Tsize_t@ $Snbr_param@:<br />
      $A How many variadic parameters there is.
    </li>
    <li>
      $S...@:<br />
      $A $Snbr_param@ parameters that can $Kconst@ $Tchar@* or negative or zero int64_t.
      Strings are interpreted as children browsing and negative or zero integers as
      index browsing.
    </li>
  </ul>
</div>
<hr />

<div class="return">
  <h3>Return value</h3>
  <p>
    Returns the required node. Returning $CNULL@ if it does not exists
    and create mode is $Cfalse@.
  </p>
</div>
<hr />

<div class="related_functions">
  <h3>Related functions</h3>
  <ul>
    <li>bunny_configuration_go_get_va</li>
    <li>bunny_configuration_go_get_string_va</li>
    <li>bunny_configuration_go_get_double_va</li>
    <li>bunny_configuration_go_get_int_va</li>
  </ul>
</div>

