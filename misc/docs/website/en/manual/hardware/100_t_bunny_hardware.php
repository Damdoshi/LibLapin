<div class="prototype">
  $Ktypedef struct@ $Ts_bunny_hardware@<br />
  {<br />
  $A $Kconst@ $Tvoid@ *$Kconst@ $S_private@;<br />
  $A $Kconst@ $Tint@ $Sid@;<br />
  $A $Kconst@ $Tbool@ $Sdigital_inputs@[5];<br />
  $A $Kconst@ $Tdouble@ $Sanalog_inputs@[2];<br />
  $A $Tbool@ $Sdigital_outputs@[8]@;<br />
  $A $Tdouble@ $Sanalog_outputs@[2];<br />
  <br />
  } $Tt_bunny_hardware@;<br />
</div>
<hr />

<div class="resume">
  <h3>Description</h3>
  $A This structure represents the VM110N board. It is partially abstract.
  Some fields are read only and are modified only by the bunny hardware
  functions, some can be modified to change the board status.
</div>
<hr />

<div class="parameters">
  <h3>Attributes</h3>
  <ul>
    <li>
      $Kconst@ $Tvoid@ *$Kconst@ $S_private@:<br />
      $A Private field you should not modify or your program may crash.
    </li>
    <li>
      $Kconst@ $Tint@ $Sid@:<br />
      $A The id of the board. Four boards can be supported.
    </li>
    <li>
      $Kconst@ $Tbool@ $Sdigital_inputs@[5]:<br />
      $A The status of digital inputs on the board.
    </li>
    <li>
      $Kconst@ $Tdouble@ $Sanalog_inputs@[2]:<br />
      $A The status of analog inputs on the board. Analog values varies
      between 0 and 1.
    </li>
    <li>
      $Tbool@ $Sdigital_outputs@[8]@;<br />
      $A Editable field that allow you to set a board status on some pins.
      After editing this field, calling bunny_hardware_write will transform
      your values into reality.
    </li>
    <li>
      $Tdouble@ $Sanalog_outputs@[2]:<br />
      $A Editable field that allow you to set a board status on some pins.
      After editing this field, calling bunny_hardware_write will transform
      your values into reality. Analog values can varies between 0 and 1.
    </li>
  </ul>
</div>

<div class="related_functions">
  <h3>Related functions</h3>
  <ul>
    <li>bunny_new_hardware</li>
    <li>bunny_delete_hardware</li>
  </ul>
</div>
