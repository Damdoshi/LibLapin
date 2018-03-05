<div class="prototype">
  $Ktypedef struct@ $Ts_bunny_anonymous_context@<br />
  {<br />
  $A $Tvoid@ $Skey@;<br />
  $A $Tvoid@ $Stype@;<br />
  $A $Tvoid@ $Sclick@;<br />
  $A $Tvoid@ $Smove@;<br />
  $A $Tvoid@ $Swheel@;<br />
  $A $Tvoid@ $Sconnect@;<br />
  $A $Tvoid@ $Sbutton@;<br />
  $A $Tvoid@ $Saxis@;<br />
  $A $Tvoid@ $Sget_focus@;<br />
  $A $Tvoid@ $Slost_focus@;<br />
  $A $Tvoid@ $Sresize@;<br />
  $A $Tvoid@ $Sloop@;<br />
  $A $Tvoid@ $Sdisplay@;<br />
  $A $Tvoid@ $Sclose@;<br />
  $A $Tvoid@ *$Snetcom@;<br />
  $A $Tvoid@ $Snetmessage@;<br />
  $A $Tvoid@ $Snetconnect@;<br />
  $A $Tvoid@ $Sentering_context@;<br />
  $A $Tvoid@ $Sleaving_context@;<br />
  <br />
  } $Tt_bunny_anonymous_context@;<br />
</div>
<hr />

<div class="resume">
  <h3>Description</h3>
  $A This structure is a full callback context compatible with the t_bunny_context
  structure and present for commodity: the power of void pointers allow you,
  depending of how you compile, not cast slitghly different function pointers
  to make them go inside the structure. Slitghly different means, in most case,
  with a type specified instead of a regular void pointer as $Sdata@ parameter.
</div>
<hr />

<div class="related_functions">
  <h3>Related functions</h3>
  <ul>
    <li>t_bunny_context</li>
    <li>bunny_set_context</li>
    <li>bunny_get_context</li>
  </ul>
</div>
