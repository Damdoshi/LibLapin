<div class="prototype">
  Macro
  $Tvoid@ $Sbunny_delete_sound@(
  *$Ssound@
  );
</div>
<hr />

<div class="resume">
  <h3>Description</h3>
  $A Delete the sent sound.
</div>
<hr />

<div class="parameters">
  <h3>Parameters</h3>
  <ul>
    <li>
      *$Ssound@:<br />
      $A The sound to delete.
      If you use <b>C11</b> (Not available in C++), this
      function can handle $Tt_bunny_music@*, $Tt_bunny_effect@*
      and $Tt_bunny_sound@* automatically.<br />
      If you use a previous version or C++, this function only
      takes a $Tt_bunny_sound@ and you have to resolve the type
      yourself.
    </li>
  </ul>
</div>
<hr />

<div class="details">
  <h3>Additional informations</h3>
  <p>This macro wraps a call to a real function, which is:</p>
  <p>
    $Tvoid@ $S_bunny_delete_sound@(
    $Tt_bunny_sound@ *$Ssound@
    );
  </p>
</div>
<hr />

<div class="related_functions">
  <h3>Related functions</h3>
  <ul>
    <li>bunny_new_effect</li>
    <li>bunny_load_effect</li>
    <li>bunny_load_music</li>
  </ul>
</div>

