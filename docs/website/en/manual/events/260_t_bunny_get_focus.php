<div class="prototype">
  $Ktypedef@ $Tt_bunny_response@ (*$Tt_bunny_get_focus@)(
  $Kconst@ $Tt_bunny_window@ *$Swindow@,
  $Tvoid@ *$Sdata@
  );
</div>
<hr />

<div class="resume">
  <h3>Description</h3>
  $A The type of function called when a window got the focus.
</div>
<hr />

<div class="parameters">
  <h3>Parameters</h3>
  <ul>
    <li>
      $Kconst@ $Tt_bunny_window@ *$Swindow@:<br />
      $A The window that got the focus.
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
    <li>bunny_set_get_focus_response</li>
  </ul>
</div>

