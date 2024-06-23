<div class="prototype">
  $Tvoid@ $Sbunny_default_screen_tweak@(
  $Tt_bunny_screen_tweak@ *$Sbst@
  );
</div>
<hr />

<div class="resume">
  <h3>Description</h3>
  $A This function set all fields inside the $Sbst@ structure with default values.
  Those default values make the screen tweak shader completly useless: it won't
  change anything to what is displayed.<br />
  <br />
  This is useful so you can only use a single transformation or several but
  don't have to neuter the one you do not use yourself.
</div>
<hr />

<div class="parameters">
  <h3>Parameters</h3>
  <ul>
    <li>
      $Tt_bunny_screen_tweak@ *$Sbst@:<br />
      $A The structure to fill.
    </li>
  </ul>
</div>
<hr />

<div class="related_functions">
  <h3>Related functions</h3>
  <ul>
    <li>t_bunny_screen_tweak</li>
    <li>bunny_screen_tweak_shader</li>
  </ul>
</div>

