<div class="prototype">
  $Ktypedef struct@ $Ts_bunny_trap@<br />
  {<br />
  $Kconst@ $Tchar@ $S_private@[3 * $Ksizeof@($Tvoid@*)];<br />
  $Kconst@ $Tdouble@ $Sstart_time@;<br />
  $Kconst@ $Tdouble@ $Sduration@;<br />
  $Tt_bunny_trap_function@ $Sfunction@;<br />
  $Tvoid@ *$Sadditional_param@;<br />
  <br />
  } $Tt_bunny_trap@;
</div>
<hr />

<div class="resume">
  <h3>Description</h3>
  $A This structure is partially abstract. The only editable fields
  are the function called when the trap happen and the arbitrary data
  that is sent.<br />
  <br />
  This structure represents a trap: an event that occurs under condition
  of pace.
</div>
<hr />

<div class="parameters">
  <h3>Attributes</h3>
  <ul>
    <li>
      $Kconst@ $Tchar@ $S_private@[3 * $Ksizeof@($Tvoid@*)]:<br />
      $A A private field that you must not modify or it may make your program crash.
    </li>
    <li>
      $Kconst@ $Tdouble@ $Sstart_time@:<br />
      $A Start time is a date we must reach before the event can occurs.<br />
      There is some special features that are described in bunny_new_trap manual.
    </li>
    <li>
      $Kconst@ $Tdouble@ $Sduration@:<br />
      $A Duration is a duration after start time during the event
      can occur.<br />
      There is some special features that are described in bunny_new_trap manual.
    </li>
    <li>
      $Tt_bunny_trap_function@ $Sfunction@:<br />
      $A The function that is called when the trap occurs.
      It is defined when the trap is created.
    </li>
    <li>
      $Tvoid@ *$Sadditional_param@:<br />
      $A The third parameter sent to the function which is called when the trap occurs.
      It is defined when the trap is created.
    </li>
  </ul>
</div>
<hr />

<div class="related_functions">
  <h3>Related functions</h3>
  <ul>
    <li>t_bunny_trap_function</li>
    <li>bunny_new_trap</li>
    <li>bunny_delete_trap</li>
    <li>bunny_asynclock</li>
  </ul>
</div>

