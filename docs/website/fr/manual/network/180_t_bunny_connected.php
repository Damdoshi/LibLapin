<div class="prototype">
  $Ktypedef struct@ $Ts_bunny_connected@<br />
  {<br />
  $A $Tt_bunny_comptype@ $Scomtype@;<br />
  $A $Tunsigned int@ $Stime@;<br />
  $A $Tt_bunny_comerror@ $Serrortype@;<br />
  $A $Tint@ $Sfd@;<br />
  <br />
  } $Tt_bunny_connected@;<br />
</div>
<hr />

<div class="resume">
  <h3>Description</h3>
  $A This structure is used by t_bunny_communication if its t_bunny_comtype
  is $SNETCONNECTED@. It indicates a new connection was opened.
</div>
<hr />

<div class="parameters">
  <h3>Attributes</h3>
  <ul>
    <li>
      $Tt_bunny_comtype@ $Scomtype@:<br />
      $A Should contain $SNETCONNECTED@ if this is effectively a t_bunny_connected.
    </li>
    <li>
      $Tunsigned int@ $Stime@:<br />
      $A Time that was not consumed by the scheduling operation returning
      the t_bunny_communication.
    </li>
    <li>
      $Tint@ $Sfd@:<br />
      $A The file descriptor of the new connection.
    </li>
  </ul>
</div>

<div class="related_functions">
  <h3>Related functions</h3>
  <ul>
    <li>t_bunny_communication</li>
    <li>t_bunny_comtype</li>
  </ul>
</div>
