<div class="prototype">
  $Tvoid@ $Sbunny_set_key_repeat@($Tt_bunny_window@ *$Swindow@,
  $Tbool@ $Srepeat@
  );
</div>
<hr />

<div class="resume">
  <h3>Description</h3>
  $A Enable or disable the key repetition for the sent window.
  Note that the key repetition is <b>not</b> made for be used
  in a video game context: it is not a "keydown status" but
  a pure tool for text editor. Its speed is system configuration
  dependant. If you need a keydown status, use bunny_get_keyboard.
</div>
<hr />

<div class="parameters">
  <h3>Parameters</h3>
  <ul>
    <li>
      $Tt_bunny_window@ *$Swindow@:<br />
      $A The window which will have its key repetition policy modified.
    </li>
    <li>
      $Tbool@ $Srepeat@:<br />
      $A $Ctrue@ to enable key repetition, $Cfalse@ to disable it.
    </li>
  </ul>
</div>

