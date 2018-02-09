<div class="prototype">
  $Ktypedef enum@ $Te_bunny_configuration_type@<br />
  {<br />
  $A $SBC_INI@,<br />
  $A $SBC_DABSIC@,<br />
  $A $SBC_DABSIC_SEQUENCE@,<br />
  $A $SBC_DABSIC_FUNCTION@,<br />
  $A $SBC_DABSIC_EXPRESSION@,<br />
  $A $SBC_XML@,<br />
  $A $SBC_LUA@,<br />
  $A $SBC_CSV@,<br />
  $A $SBC_JSON@,<br />
  $A $SBC_LISP@,<br />
  $A $SBC_CUSTOM@<br />
  <br />
  } $Tt_bunny_rgb@;
</div>
<hr />

<div class="resume">
  <h3>Description</h3>
  $A This enumeration serves to precise the kind of grammar used into a file
  to load with bunny_load_configuration.<br />
  <br />
  Any value greater or equal to $SBC_CUSTOM@ trigger the call of
  gl_bunny_my_read_configuration instead of calling bunny library functions so
  you can extend the bunny library at runtime and still use its API.
</div>
<hr />

<div class="related_functions">
  <h3>Related functions</h3>
  <ul>
    <li>bunny_load_configuration</li>
    <li>bunny_which_format</li>
    <li>bunny_delete_configuration</li>
  </ul>
</div>

