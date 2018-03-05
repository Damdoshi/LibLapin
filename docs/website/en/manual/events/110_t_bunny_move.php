<div class="prototype">
  $Ktypedef@ $Tt_bunny_response@ (*$Tt_bunny_move@)(
  $Kconst@ $Tt_bunny_position@ *$Srelative@,
  $Tvoid@ *$Sdata@
  );
</div>
<hr />

<div class="resume">
  <h3>Description</h3>
  $A The type of function called when a mouse move event happen.
</div>
<hr />

<div class="parameters">
  <h3>Parameters</h3>
  <ul>
    <li>
      $Kconst@ $Tt_bunny_position@ *$Srelative@:<br />
      $A The relative movement of the mouse since last time.
    </li>
    <li>
      $Tvoid@ *$Sdata@:<br />
      $A The data sent as the last parameter of bunny_loop or bunny_loop_mw.
    </li>
  </ul>
</div>

<div class="related_functions">
  <h3>Related functions</h3>
  <ul>
    <li>bunny_set_move_response</li>
  </ul>
</div>

