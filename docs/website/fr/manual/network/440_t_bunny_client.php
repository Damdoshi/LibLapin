<div class="prototype">
  $Ktypedef struct@ $Tt_bunny_client@<br />
  {<br />
  $Kconst@ $Tvoid@ * $Kconst@ $S_private@[2];<br />
  $Kconst@ $Tint@ $Sfd@;<br />
  $Kconst@ $Tchar@ * $Kconst@ $Shost@;<br />
  $Kconst@ $Suint16_t@ $Sport@;<br />
  <br />
  } $Tt_bunny_client@;<br />
</div>
<hr />

<div class="resume">
  <h3>Description</h3>
  $A This structure is partially abstract and represents a client.
  It is created by bunny_new_client_opt
  or bunny_new_client and deleted by bunny_delete_client.
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
      $Kconst@ $Tchar@ * $Kconst@ $Shost@:<br />
      $A The host on which the client is connected.
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
    <li>bunny_new_client_opt</li>
    <li>bunny_new_client</li>
    <li>bunny_delete_client</li>
  </ul>
</div>
