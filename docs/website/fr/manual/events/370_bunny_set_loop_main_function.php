k<div class="prototype">
  $Tvoid@ $Sbunny_set_loop_main_function@($Tt_bunny_loop@ $Sfunction@);
</div>
<hr />

<div class="resume">
  <h3>Description</h3>
  $A This function allow you to define a callback function that
  will be called at the frequency given to bunny_loop or bunny_loop_mw.
  If the loop is late, calls will be caught back later. Several call to
  the function to catch up will not provoke several calls to the function
  set with bunny_set_display_function but a single one.
</div>
<hr />

<div class="parameters">
  <h3>Parameters</h3>
  <ul>
    <li>
      $Tt_bunny_loop@ $Sfunction@:<br />
      $A The function to call.
    </li>
  </ul>
</div>

<div class="related_functions">
  <h3>Related functions</h3>
  <ul>
    <li>t_bunny_loop</li>
  </ul>
</div>

