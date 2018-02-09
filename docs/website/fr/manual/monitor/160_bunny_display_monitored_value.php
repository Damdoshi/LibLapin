<div class="prototype">
  $Tvoid@ $Sbunny_display_monitored_value@(
  $Tt_bunny_font@ *$Stext_area@,
  $Kconst@ $Tchar@ *$Sname@,
  );
</div>
<hr />

<div class="resume">
  <h3>Description</h3>
  $A Write inside the sent $Stext_area@ the monitored value $Sname@, or several
  value depending of what is inside $Sname@.
</div>
<hr />

<div class="parameters">
  <h3>Parameters</h3>
  <ul>
    <li>
      $Tt_bunny_font@ *$Stext_area@:<br />
      $A The graphic space where all will be written.
    </li>
    <li>
      $Kconst@ $Tchar@ *$Sname@:<br />
      $A The name of the monitored value to write.<br />
      $CNULL@ to write all values.<br />
      You can use the character '*' as ending joker.
    </li>
  </ul>
</div>
<hr />

<div class="related_functions">
  <h3>Related functions</h3>
  <ul>
    <li>bunny_add_monitored_value</li>
    <li>bunny_remove_monitored_value</li>
    <li>bunny_print_monitored_value</li>
  </ul>
</div>

