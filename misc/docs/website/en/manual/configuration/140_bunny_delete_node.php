<div class="prototype">
  $Tvoid@ $Sbunny_delete_node@(
  $Tt_bunny_configuration@ *$Sconfiguration@,
  $Kconst@ $Tchar@ *$Saddress@
  );
</div>
<hr />

<div class="resume">
  <h3>Description</h3>
  $A Delete the node at the sent address in the sent configuration.
  All children of this node will be destroyed as well.
</div>
<hr />

<div class="parameters">
  <h3>Parameters</h3>
  <ul>
    <li>
      $Tt_bunny_configuration@ *$Sconfiguration@:<br />
      $A The configuration to partially delete.
    </li>
    <li>
      $Kconst@ $Tchar@ *$Saddress@:<br />
      $A The address of the node to delete.
    </li>
  </ul>
</div>
<hr />
<div class="related_functions">
  <h3>Related functions</h3>
  <ul>
    <li>t_bunny_configuration_type</li>
    <li>bunny_new_configuration</li>
    <li>bunny_load_configuration</li>
    <li>bunny_save_configuration</li>
    <li>bunny_read_configuration</li>
    <li>bunny_write_configuration</li>
  </ul>
</div>

