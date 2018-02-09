<div class="prototype">
  Macro
  $Tbool@ $Sbunny_client_packet_ready@(
  $Kconst@ $Tt_bunny_client@ *$Sclient@,
  );
</div>
<hr />

<div class="resume">
  <h3>Description</h3>
  $A Return $Ctrue@ if bunny_client_poll can be called without having
  any delay implied because a packet is waiting to be retrieved from it.<br />
  A good design would be to loop on bunny_client_poll while bunny_client_packet_ready
  returns $Ctrue@.
</div>
<hr />

<div class="parameters">
  <h3>Parameters</h3>
  <ul>
    <li>
      $Tt_bunny_client@ *$Sclient@:<br />
      $A The client to manage.
    </li>
  </ul>
</div>
<hr />

<div class="return">
  <h3>Return value</h3>
  <p>
    Return $Ctrue@ if you can safely call bunny_client_poll and it will returns
    immediatly.
  </p>
</div>
<hr />

<div class="related_functions">
  <h3>Related functions</h3>
  <ul>
    <li>bunny_client_poll</li>
    <li>bunny_client_write</li>
  </ul>
</div>

