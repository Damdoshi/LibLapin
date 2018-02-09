<div class="prototype">
  $Ktypedef union@ $Tu_bunny_communication@<br />
  {<br />
  $Tt_bunny_comtype@ $Scomtype@;<br />
  $Tt_bunny_network_error@ $Serror@;<br />
  $Tt_bunny_expired@ $Sexpired@;<br />
  $Tt_bunny_connected@ $Sconnected@;<br />
  $Tt_bunny_disconnected@ $Sdisconnected@;<br />
  $Tt_bunny_message@ $Smessage@;<br />
  <br />
  } $Tt_bunny_communication@;<br />
</div>
<hr />

<div class="resume">
  <h3>Description</h3>
  $A This union is returned by bunny_server_poll and bunny_client_poll
  to indicates what happened when they were executing. The first attribute
  i$Scomtype@ is a t_bunny_comtype and is useful to identify which
  field inside the union is used and filled.
</div>
<hr />

<div class="related_functions">
  <h3>Related functions</h3>
  <ul>
    <li>t_bunny_comtype</li>
    <li>t_bunny_network_error</li>
    <li>t_bunny_expired</li>
    <li>t_bunny_connected</li>
    <li>t_bunny_disconnected</li>
    <li>t_bunny_message</li>
  </ul>
</div>
