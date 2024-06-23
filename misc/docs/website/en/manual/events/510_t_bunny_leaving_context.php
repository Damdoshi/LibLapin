k<div class="prototype">
  $Ktypedef@ $Tvoid@ (*$Tt_bunny_leaving_context@)(
  $Tt_bunny_response@ $Sreturned@,
  $Tvoid@ *$Sdata@
  );
</div>
<hr />

<div class="resume">
  <h3>Description</h3>
  $A The type of function called when bunny_loop or bunny_loop_mw is exited.
</div>
<hr />

<div class="parameters">
  <h3>Parameters</h3>
  <ul>
    <li>
      $Tt_bunny_response@ $Sreturned@:<br />
      $A The value that will be returned by bunny_loop or bunny_loop_mw.
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
    <li>bunny_set_leaving_context_response</li>
  </ul>
</div>

