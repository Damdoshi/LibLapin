<div class="prototype">
  $Tvoid@ $Sbunny_set_client_to_scheduler@($Tt_bunny_client@ *$Sclient@);
</div>
<hr />

<div class="resume">
  <h3>Description</h3>
  $A This function set a network client inside the bunny loop to handle its events.
  To remove it, use bunny_remove_network_from_scheduler.
</div>
<hr />

<div class="parameters">
  <h3>Parameters</h3>
  <ul>
    <li>
      $Tt_bunny_client@ *$Sclient@:<br />
      $A The network client to handle.
    </li>
  </ul>
</div>

<div class="related_functions">
  <h3>Related functions</h3>
  <ul>
    <li>bunny_set_server_to_scheduler</li>
    <li>bunny_remove_network_from_scheduler</li>
  </ul>
</div>

