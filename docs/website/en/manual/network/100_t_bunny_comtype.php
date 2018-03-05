<div class="prototype">
  $Ktypedef enum@ $Te_bunny_comtype@<br />
  {<br />
  $A $SERROR@,<br />
  $A $SEXPIRED@,<br />
  $A $SNETCONNECTED@,<br />
  $A $SNETDISCONNECTED@,<br />
  $A $SMESSAGE@<br />
  <br />
  } $Tt_bunny_rgb@;
</div>
<hr />

<div class="resume">
  <h3>Description</h3>
  $A This enumeration is used to help you performing a runtime cast on
  the t_bunny_communication union.
</div>
<hr />

<div class="parameters">
  <h3>Symbols</h3>
  <ul>
    <li>
      $SERROR@:<br />
      $A The t_bunny_communication union must be used as a t_bunny_network_error.
    </li>
    <li>
      $SEXPIRED@:<br />
      $A The t_bunny_communication union must be used as a t_bunny_expired.
    </li>
    <li>
      $SNETCONNECTED@:<br />
      $A The t_bunny_communication union must be used as a t_bunny_connected.
    </li>
    <li>
      $SNETDISCONNECTED@:<br />
      $A The t_bunny_communication union must be used as a t_bunny_disconnected.
    </li>
    <li>
      $SMESSAGE@:<br />
      $A The t_bunny_communication union must be used as a t_bunny_message.
    </li>
  </ul>
</div>
<hr />

<div class="related_functions">
  <h3>Related functions</h3>
  <ul>
    <li>t_bunny_communication</li>
    <li>t_bunny_network_error</li>
    <li>t_bunny_expired</li>
    <li>t_bunny_connected</li>
    <li>t_bunny_disconnected</li>
    <li>t_bunny_message</li>
  </ul>
</div>

