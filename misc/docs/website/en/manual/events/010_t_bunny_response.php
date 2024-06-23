<div class="prototype">
  $Ktypedef enum@ $Te_bunny_response@<br />
  {<br />
  $A $SEXIT_ON_ERROR@,
  $A $SEXIT_ON_CROSS@,
  $A $SEXIT_ON_SUCCESS@,
  $A $SSWITCH_CONTEXT@,
  $A $SGO_ON@
  <br />
  } $Tt_bunny_response@;
</div>
<hr />

<div class="resume">
  <h3>Description</h3>
  $A This enumeration is used as return value by every event callbacks, bunny_loop
  and bunny_loop_mw and mix informations and request. Except $SGO_ON@, every values
  of this enumeration if returned by an event callback will make bunny_loop
  or bunny_loop_mw exiting and returning the concerned value.
</div>
<hr />

<div class="parameters">
  <h3>Symbols</h3>
  <ul>
    <li>
      $SEXIT_ON_ERROR@:<br />
      $A An error happened.
    </li>
    <li>
      $SEXIT_ON_CROSS@:<br />
      $A The exit button on the window itself was pressed.
    </li>
    <li>
      $SEXIT_ON_SUCCESS@:<br />
      $A Simply exit, nothing happen.
    </li>
    <li>
      $SSWITCH_CONTEXT@:<br />
      $A bunny_loop or bunny_loop_mw should be called again with another
      context set.
    </li>
    <li>
      $SGO_ON@:<br />
      $A Do not leave bunny_loop or bunny_loop_mw. Stay in the current context.
    </li>
  </ul>
</div>
