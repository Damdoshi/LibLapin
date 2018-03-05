<div class="prototype">
  Macro
  $Tbool@ $Sbunny_sound_manager_add@(
  $Tt_bunny_sound_manager@ *$Ssound_manager@,
  *$Ssound@,
  $Tt_bunny_sound_type@ $Stype@
  );
</div>
<hr />

<div class="resume">
  <h3>Description</h3>
  $A This function adds the sent sound into the sound manager
  and associate it to the precised category.<br />
  <br />
  The sound cannot be added into different category.<br />
  <br />
  A sound added inside the sound manager should not have
  its volume or pitch set by bunny_sound_volume or bunny_sound_pitch
  but with bunny_managed_sound_volume or bunny_managed_sound_pitch.<br />
  <br />
  It can be removed with bunny_sound_manager_remove. Note
  that a sound added inside a unique manager and deleted
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
      $A The sound manager in which the sound will be added.
    </li>
    <li>
      *$Ssound@:<br />
      $A A sound to add into the sound manager.<br />
      If you use <b>C11</b> (Not available in C++), this
      function can handle $Tt_bunny_music@*, $Tt_bunny_effect@*
      and $Tt_bunny_sound@* automatically.<br />
      If you use a previous version or C++, this function only
      takes a $Tt_bunny_sound@ and you have to resolve the type
      yourself.
    </li>
    <li>
      $Tt_bunny_sound_type@ $Stype@:<br />
      $A The category in which the sound will be stored.
    </li>
  </ul>
</div>
<hr />

<div class="return">
  <h3>Return value</h3>
  <p>
    Return $Ctrue@ if the sound was inserted or was
    already inserted. $Cfalse@ on error.
  </p>
</div>
<hr />

<div class="details">
  <h3>Additional informations</h3>
  <p>This macro wraps a call to a real function, which is:</p>
  <p>
    $Tbool@ $S_bunny_sound_manager_add@(
    $Tt_bunny_sound_manager@ *$Ssound_manager@,
    $Tt_bunny_sound@ *$Ssound@,
    $Tt_bunny_sound_type@ $Stype@
    );
  </p>
</div>
<hr />

<div class="related_functions">
  <h3>Related functions</h3>
  <ul>
    <li>bunny_sound_manager_remove</li>
    <li>bunny_delete_sound</li>
  </ul>
</div>

