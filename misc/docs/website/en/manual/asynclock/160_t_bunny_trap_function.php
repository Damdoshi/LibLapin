<div class="prototype">
  $Ktypedef@ $Tvoid@ (*$Tt_bunny_trap_function@)(
  $Tdouble@ $Selapsed_time@,
  $Tt_bunny_trap@ *$Strap@,
  $Tvoid@ *$Sdata@
  );
</div>
<hr />

<div class="resume">
  <h3>Description</h3>
  $A This function will be called when its matching trap occurs.
  It will receive informations about the trap and also arbitrary value.
  <br />
  <br />
  You can safely delete the sent trap with bunny_delete_trap, it will
  not cause any trouble: it will only be marked for suppression and
  be deleted when it is possible.
</div>
<hr />

<div class="parameters">
  <h3>Parameters</h3>
  <ul>
    <li>
      $Tdouble@ $Selapsed_time@:<br />
      The program elapsed time, sent to bunny_asynclock by bunny_loop,
      bunny_loop_mw or another function set in your program.
    <li>
      $Tt_bunny_trap@ *$Strap@:<br />
      $A The trap structure which is responsible for this function call.
    </li>
    <li>
      $Tvoid@ *$Sdata@:<br />
      $A A data configured when creating the trap.
    </li>
  </ul>
</div>
<hr />

<div class="related_functions">
  <h3>Related functions</h3>
  <ul>
    <li>bunny_new_trap</li>
    <li>bunny_delete_trap</li>
    <li>bunny_asynclock</li>
  </ul>
</div>

