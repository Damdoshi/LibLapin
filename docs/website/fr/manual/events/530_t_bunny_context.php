<div class="prototype">
  $Ktypedef struct@ $Ts_bunny_context@<br />
  {<br />
  $A $Tt_bunny_key@ $Skey@;<br />
  $A $Tt_bunny_type@ $Stype@;<br />
  $A $Tt_bunny_click@ $Sclick@;<br />
  $A $Tt_bunny_move@ $Smove@;<br />
  $A $Tt_bunny_wheel@ $Swheel@;<br />
  $A $Tt_bunny_joy_connect@ $Sconnect@;<br />
  $A $Tt_bunny_joy_button@ $Sbutton@;<br />
  $A $Tt_bunny_joy_axis@ $Saxis@;<br />
  $A $Tt_bunny_get_focus@ $Sget_focus@;<br />
  $A $Tt_bunny_lost_focus@ $Slost_focus@;<br />
  $A $Tt_bunny_resize@ $Sresize@;<br />
  $A $Tt_bunny_loop@ $Sloop@;<br />
  $A $Tt_bunny_display@ $Sdisplay@;<br />
  $A $Tt_bunny_close@ $Sclose@;<br />
  $A $Tt_bunny_network@ *$Snetcom@;<br />
  $A $Tt_bunny_message_response@ $Snetmessage@;<br />
  $A $Tt_bunny_connect_response@ $Snetconnect@;<br />
  $A $Tt_bunny_loop@ $Sentering_context@;<br />
  $A $Tt_bunny_leaving_context@ $Sleaving_context@;<br />
  <br />
  } $Tt_bunny_context@;<br />
</div>
<hr />

<div class="resume">
  <h3>Description</h3>
  $A This structure is a full callback context. It allow to set every
  callbacks in a single call to bunny_set_context. $CNULL@ can be use
  to deactivate callbacks.<br />
  <br />
  $A To enable network events, the $Snetcom@ field must be set to
  your t_bunny_server or t_bunny_client.
</div>
<hr />

<div class="related_functions">
  <h3>Related functions</h3>
  <ul>
    <li>t_bunny_anonymous_context</li>
    <li>bunny_set_context</li>
    <li>bunny_get_context</li>
  </ul>
</div>
