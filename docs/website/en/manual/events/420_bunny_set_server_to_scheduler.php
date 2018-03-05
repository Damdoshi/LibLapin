<div class="prototype">
  $Tvoid@ $Sbunny_set_server_to_scheduler@($Tt_bunny_server@ *$Sserver@);
</div>
<hr />

<div class="resume">
  <h3>Description</h3>
  $A This function set a network server inside the bunny loop to handle its events.
  To remove it, use bunny_remove_network_from_scheduler.
</div>
<hr />

<div class="parameters">
  <h3>Parameters</h3>
  <ul>
    <li>
      $Tt_bunny_server@ *$Sserver@:<br />
      $A The network server to handle.
    </li>
  </ul>
</div>

<div class="related_functions">
  <h3>Related functions</h3>
  <ul>
    <li>bunny_set_client_to_scheduler</li>
    <li>bunny_remove_network_from_scheduler</li>
  </ul>
</div>

