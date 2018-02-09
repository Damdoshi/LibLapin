<div class="prototype">
  Macro
  $Tbool@ $Sbunny_sound_manager_remove@(
  $Tt_bunny_sound_manager@ *$Ssound_manager@,
  *$Ssound@
  );
</div>
<hr />

<div class="resume">
  <h3>Description</h3>
  $A This function remove the sent sound from the sent
  sound manager.<br />
  <br />
  A sound added inside a unique manager and deleted
  with bunny_delete_sound will be automatically removed
  from its manager. Note it does not handle to be added
  into several manager, so you should avoid doing it at
  the same time.
</div>
<hr />

<div class="parameters">
  <h3>Parameters</h3>
  <ul>
    <li>
      $Tt_bunny_sound_manager@ $Ssound_manager@:<br />
      $A The sound manager in which the sound will be removed.
    </li>
    <li>
      *$Ssound@:<br />
      $A The sound to remove.<br />
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
    $Tvoid@ $S_bunny_sound_manager_remove@(
    $Tt_bunny_sound_manager@ *$Ssound_manager@,
    $Tt_bunny_sound@ *$Ssound@
    );
  </p>
</div>
<hr />

<div class="related_functions">
  <h3>Related functions</h3>
  <ul>
    <li>bunny_sound_manager_add</li>
    <li>bunny_delete_sound</li>
  </ul>
</div>

