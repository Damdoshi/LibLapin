<div class="prototype">
  $Tbool@ $Sbunny_save_effect@(
  $Kconst@ $Tt_bunny_effect@ *$Seffect@,
  $Kconst@ $Tchar@ *$Sstr@
  );
</div>
<hr />

<div class="resume">
  <h3>Description</h3>
  $A Save the sent sound effect into a file. Suppored formats are wav
  and ogg.
</div>
<hr />

<div class="parameters">
  <h3>Parameters</h3>
  <ul>
    <li>
      $Kconst@ $Tt_bunny_effect@ *$Seffect@:<br />
      $A The sound effect to save.
    </li>
    <li>
      $Kconst@ $Tchar@ *$Sstr@:<br />
      $A The file in which save the file.
    </li>
  </ul>
</div>
<hr />

<div class="return">
  <h3>Return value</h3>
  <p>Returns $Ctrue@ on success.
</div>
<hr />

<div class="error_and_log">
  <h3>Error values and logs</h3>
  <p>
    On error, $Vbunny_errno@ is set to:
  </p>
  <br />
  <ul>
    <li>
      $CENOMEM@:<br />
      <p>
        Out of memory.<br />
      </p>
    </li>
  </ul>
  <br />
  <p>
    Logs written by this function or subfunctions may be tagged with
    $L"ressource"@ or
    $L"sound"@
    labels.
  </p>
</div>
<hr />

<div class="related_functions">
  <h3>Related functions</h3>
  <ul>
    <li>bunny_delete_sound</li>
    <li>bunny_sound_play</li>
    <li>bunny_sound_stop</li>
    <li>t_bunny_sound_manager</li>
  </ul>
</div>

