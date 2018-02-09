<div class="prototype">
  $Tt_bunny_configuration@ *$Sbunny_configuration_first@(
  $Tt_bunny_configuration@ *$Sconfiguration@
  );
</div>
<hr />

<div class="resume">
  <h3>Description</h3>
  $A Return the first children node of the sent one.
</div>
<hr />

<div class="parameters">
  <h3>Parameters</h3>
  <ul>
    <li>
      $Tt_bunny_configuration@ *$Sconfiguration@:<br />
      $A The configuration node to browse.
    </li>
  </ul>
</div>
<hr />

<div class="return">
  <h3>Return value</h3>
  <p>
    Returns the first children of $Sconfiguration@, it may be
    bunny_configuration_end($Sconfiguration), that would means the sent node is empty.
  </p>
</div>
<hr />

<div class="related_functions">
  <h3>Related functions</h3>
  <ul>
    <li>bunny_configuration_next</li>
    <li>bunny_configuration_end</li>
    <li>bunny_configuration_is_last</li>
  </ul>
</div>

