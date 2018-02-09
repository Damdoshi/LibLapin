<div class="prototype">
  $Tt_bunny_configuration@ *$Sbunny_configuration_next@(
  $Tt_bunny_configuration@ *$Sconfiguration@
  );
</div>
<hr />

<div class="resume">
  <h3>Description</h3>
  $A Return the next children of the parent of $Sconfiguration.
</div>
<hr />

<div class="parameters">
  <h3>Parameters</h3>
  <ul>
    <li>
      $Tt_bunny_configuration@ *$Sconfiguration@:<br />
      $A The node that is the previous of the next one.
    </li>
  </ul>
</div>
<hr />

<div class="return">
  <h3>Return value</h3>
  <p>
    Returns the next children of the parent of $Sconfiguration@, it may be
    bunny_configuration_end($Sconfiguration), that would means the current node is
    the last one.
  </p>
</div>
<hr />

<div class="related_functions">
  <h3>Related functions</h3>
  <ul>
    <li>bunny_configuration_first</li>
    <li>bunny_configuration_end</li>
    <li>bunny_configuration_is_last</li>
  </ul>
</div>

