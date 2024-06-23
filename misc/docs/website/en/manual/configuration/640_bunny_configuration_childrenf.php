<div class="prototype">
  $Tt_bunny_configuration@ *$Sbunny_configuration_childrenf(
  $Tt_bunny_configuration@ *$Sconfiguration@,
  $Kconst@ $Tchar@ *$Sfpattern_address@,
  ...
  );
</div>
<hr />

<div class="resume">
  <h3>Description</h3>
  $A Get how many nodes are immediate children of the node at the sent address.
</div>
<hr />

<div class="parameters">
  <h3>Parameters</h3>
  <ul>
    <li>
      $Tt_bunny_configuration@ *$Sconfiguration@:<br />
      $A The configuration to inspect.
    </li>
    <li>
      $Kconst@ $Tchar@ *$Sfpattern_address@:<br />
      $A The pattern to be combined with variadic parameters to create the address
      of the node to reach.
    </li>
    <li>
      ...:<br />
      $A Any valid printf-pattern valid parameter.
    </li>
  </ul>
</div>
<hr />

<div class="return">
  <h3>Return value</h3>
  <p>
    Returns the amount of children the found node have. It returns -1 if the node
    does not exist.
  </p>
</div>
<hr />

<div class="related_functions">
  <h3>Related functions</h3>
  <ul>
    <li>bunny_configuration_casesf</li>
  </ul>
</div>

