<div class="prototype">
  $Ktypedef@ $Tt_bunny_response@ (*$Tt_bunny_type@)(
  $Tuint32_t@ $Sunicode@,
  $Tvoid@ *$Sdata@
  );
</div>
<hr />

<div class="resume">
  <h3>Description</h3>
  $A The type of function called when a character is typed.
</div>
<hr />

<div class="parameters">
  <h3>Parameters</h3>
  <ul>
    <li>
      $Tuint32_t@ $Sunicode@:<br />
      $A The character that was type.
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
    <li>bunny_set_text_response</li>
  </ul>
</div>

