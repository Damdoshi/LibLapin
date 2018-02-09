<div class="prototype">
  $Ktypedef enum@ $Te_bunny_color@<br />
  {<br />
  $A $SBE_CANT_GENERATE_RESSOURCE@,<br />
  $A $SBE_SYNTAX_ERROR@,<br />
  $A $SBE_BAD_ADDRESS@,<br />
  $A $SBE_TYPE_ERROR@,<br />
  $A $SBE_CONTAINER_IS_EMPTY@,<br />
  $A $SBE_CANNOT_DUPLICATE@,<br />
  $A $SBE_CANNOT_FIND_ELEMENT@,<br />
  $A $SBE_CANNOT_FIND_EMBEDDED_KEY@,<br />
  $A $SBE_UNKNOWN_DISPLAY_DEVICE@,<br />
  <br />
  } $Tt_bunny_color@;
</div>
<hr />

<div class="resume">
  <h3>Description</h3>
  $A This enumeration describe additionnal error code that can be set
  inside errno. They are used by the bunny library and can be use
  by your program if you want to identify an error.<br />
  <br />
  They are valid error codes to be sent to bunny_strerror, as any other
  errno code. Do not use the system strerror!
</div>
<hr />

<div class="related_functions">
  <h3>Related functions</h3>
  <ul>
    <li>bunny_errno</li>
    <li>bunny_strerror</li>
  </ul>
</div>

