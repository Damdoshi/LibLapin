<div class="prototype">
  $Ktypedef struct@ $Tt_bunny_server@<br />
  {<br />
  $Kconst@ $Tvoid@ * $Kconst@ $S_private@[2];<br />
  $Kconst@ $Tint@ $Sfd@;<br />
  $Kconst@ $Suint16_t@ $Sport@;<br />
  <br />
  } $Tt_bunny_server@;<br />
</div>
<hr />

<div class="resume">
  <h3>Description</h3>
  $A This structure is partially abstract and represents a server.
  It is created by bunny_new_server_opt
  or bunny_new_server and deleted by bunny_delete_server.
</div>
<hr />

<div class="parameters">
  <h3>Attributes</h3>
  <ul>
    <li>
      $Kconst@ $Tvoid@ * $Kconst@ $S_private@[2]:<br />
      $A Private fields you must not modify or your program may crash.
    </li>
    <li>
      $Kconst@ $Tint@ $Sfd@:<br />
      $A The listening socket of the server.<br />
      <b>Do not close it, do not use fcntl or ioctl on it.</b>
    </li>
    <li>
      $Kconst@ $Suint16_t@ $Sport@:<br />
      $A The port on which the server listens.
    </li>
  </ul>
</div>
<hr />

<div class="related_functions">
  <h3>Related functions</h3>
  <ul>
    <li>bunny_new_server_opt</li>
    <li>bunny_new_server</li>
    <li>bunny_delete_server</li>
  </ul>
</div>
