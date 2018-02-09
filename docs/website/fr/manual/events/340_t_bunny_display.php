<div class="prototype">
  $Ktypedef@ $Tvoid@ (*$Tt_bunny_display@)(
  $Tvoid@ *$Sdata@
  );
</div>
<hr />

<div class="resume">
  <h3>Description</h3>
  $A The type of function called at the end of the main loop, when displaying
  is required, if there is enough time left after all events and main computing.
</div>
<hr />

<div class="parameters">
  <h3>Parameters</h3>
  <ul>
    <li>
      $Tvoid@ *$Sdata@:<br />
      $A The data sent as the last parameter of bunny_loop or bunny_loop_mw.
    </li>
  </ul>
</div>

<div class="related_functions">
  <h3>Related functions</h3>
  <ul>
    <li>bunny_set_display_function</li>
  </ul>
</div>

