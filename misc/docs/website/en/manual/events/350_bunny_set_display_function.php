<div class="prototype">
  $Tvoid@ $Sbunny_set_display_function@($Tt_bunny_display@ $Sfunction@);
</div>
<hr />

<div class="resume">
  <h3>Description</h3>
  $A This function allow you to define a callback function that
  will be called at the end of the bunny_loop or bunny_loop_mw cycle
  if there is enough time remaining (a security ensure that it is called sometimes,
  even if the loop is always late). In the best case, it is called as much as
  the function sent to bunny_set_loop_main_function.
</div>
<hr />

<div class="parameters">
  <h3>Parameters</h3>
  <ul>
    <li>
      $Tt_bunny_display@ $Sfunction@:<br />
      $A The function to call.
    </li>
  </ul>
</div>

<div class="related_functions">
  <h3>Related functions</h3>
  <ul>
    <li>t_bunny_display</li>
  </ul>
</div>

