<div class="prototype">
  $Tbool@ $Sbunny_server_packet_ready@(
  $Kconst@ $Tt_bunny_server@ *$Sserver@,
  );
</div>
<hr />

<div class="resume">
  <h3>Description</h3>
  $A Return $Ctrue@ if bunny_server_poll can be called without having
  any delay implied because a packet is waiting to be retrieved from it.<br />
  A good design would be to loop on bunny_server_poll while bunny_server_packet_ready
  returns $Ctrue@.
</div>
<hr />

<div class="parameters">
  <h3>Parameters</h3>
  <ul>
    <li>
      $Tt_bunny_server@ *$Sserver@:<br />
      $A The server to manage.
    </li>
  </ul>
</div>
<hr />

<div class="return">
  <h3>Return value</h3>
  <p>
    Return $Ctrue@ if you can safely call bunny_server_poll and it will returns
    immediatly.
  </p>
</div>
<hr />

<div class="related_functions">
  <h3>Related functions</h3>
  <ul>
    <li>bunny_server_poll</li>
    <li>bunny_server_write</li>
    <li>bunny_server_doom_client</li>
  </ul>
</div>

