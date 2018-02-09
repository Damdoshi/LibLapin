<div class="prototype">
  Macro
  $Kconst@ $Tt_bunny_communication@ *$Sbunny_client_poll@(
  $Tt_bunny_client@ *$Sclient@,
  $Tuint32_t@ $Stimeout@
  );
</div>
<hr />

<div class="resume">
  <h3>Description</h3>
  $A This function try to read and write. Returns after $timeout@ time pass.<br />
  <br />
  bunny_client_poll returns immediatly if bunny_client_packet_ready returns
  $Ctrue@. You should loop on bunny_client_poll while it does so, so you
  can retrieve all events.
</div>
<hr />

<div class="parameters">
  <h3>Parameters</h3>
  <ul>
    <li>
      $Tt_bunny_client@ *$Sclient@:<br />
      $A The client to manage.
    </li>
    <li>
      $Tuint32_t@ $Stimeout@:<br />
      $A Time allocated to network scheduling, in milliseconds.
    </li>
  </ul>
</div>
<hr />

<div class="return">
  <h3>Return value</h3>
  <p>
    Always return a valid pointer on a statically allocated
    t_bunny_communication filled accordingly to what happened in the
    function.
  </p>
</div>
<hr />

<div class="related_functions">
  <h3>Related functions</h3>
  <ul>
    <li>bunny_client_packet_ready</li>
    <li>bunny_client_write</li>
  </ul>
</div>

