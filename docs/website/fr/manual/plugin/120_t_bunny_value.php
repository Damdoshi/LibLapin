k<div class="prototype">
  $Ktypedef union@ $Tu_bunny_value@<br />
  {<br />
  $A $Tint64_t@ $Sinteger@;<br />
  $A $Tdouble@ $Sreal@;<br />
  $A $Kconst@ $Tchar@ *$Sstring@;<br />
  $A $Tvoid@ *$Sany@;<br />
  <br />
  } $Tt_bunny_value@;
</div>
<hr />

<div class="resume">
  <h3>Description</h3>
  $A The t_bunny_value union is design to handle four different types. It is
  should be used with a t_bunny_value_type aside to indicates how to read
  the value it contains.<br />
</div>
<hr />

<div class="related_functions">
  <h3>Related functions</h3>
  <ul>
    <li>bunny_plugin_call</li>
    <li>bunny_plugin_callv</li>
  </ul>
</div>


