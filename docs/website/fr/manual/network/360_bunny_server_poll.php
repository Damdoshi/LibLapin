<div class="prototype">
  Macro
  $Kconst@ $Tt_bunny_communication@ *$Sbunny_server_poll@(
  $Tt_bunny_server@ *$Sserver@,
  $Tuint32_t@ $Stimeout@
  );
</div>
<hr />

<div class="resume">
  <h3>Description</h3>
  $A This function try to read and write on every opened connection and
  check for newly opened or closed connections on the sent $Server@. Return
  after $timeout@ time pass.<br />
  <br />
  bunny_server_poll returns immediatly if bunny_server_packet_ready returns
  $Ctrue@. You should loop on bunny_server_poll while it does so, so you
  can retrieve all events.
</div>
<hr />

<div class="parameters">
  <h3>Parameters</h3>
  <ul>
    <li>
      $Tt_bunny_server@ *$Sserver@:<br />
      $A The server to manage.
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
    <li>bunny_server_packet_ready</li>
    <li>bunny_server_write</li>
    <li>bunny_server_doom_client</li>
  </ul>
</div>

