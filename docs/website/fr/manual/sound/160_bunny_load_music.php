<div class="prototype">
  $Tt_bunny_music@ *$Sbunny_load_music@($Kconst@ $Tchar@ *$Sfile@);
</div>
<hr />

<div class="resume">
  <h3>Description</h3>
  $A Open a music file and stream it when you play it, from a sound file or
  a configuration file.
  <br />
  <br />
  Delete the music file with bunny_delete_sound when you do not
  need it anymore.
</div>
<hr />

<div class="parameters">
  <h3>Parameters</h3>
  <ul>
    <li>
      $Kconst@ $Tchar@ *$Sfile@:<br />
      $A The music file to open. Supported files are .wav and .ogg.<br />
      This function also support configuration file input. Configuration
      file format is described below.
    </li>
  </ul>
</div>
<hr />

<div class="return">
  <h3>Return value</h3>
  <ul>
    <li>
      On $Bsuccess@, the function returns a valid t_bunny_music pointer.
    </li>
    <li>
      On $Bfailure@, it returns $CNULL@.
    </li>
  </ul>
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
    <li>
      $CEINVAL@:<br />
      <p>
        An invalid file format was sent.<br />
      </p>
    </li>
    <li>
      $CENOENT@:<br />
      <p>
        The file was not found.<br />
      </p>
    </li>
    <li>
      $CBE_SYNTAX_ERROR@:<br />
      <p>
        The sent configuration file contains syntax error.
      </p>
    </li>
  </ul>
  <br />
  <p>
    Logs written by this function or subfunctions may be tagged with
    $L"ressource"@,
    $L"configuration"@,
    $L"syntax"@ or
    $L"sound"@
    labels.
  </p>
</div>
<hr />

<div class="details">
  <h3>Configuration file format</h3>

  <p>
    You can set properties of a t_bunny_sound thanks to a file at runtime.
    This allow you to get rid of a lot of configuration and to create space for
    any outside editor.
    <br />
    <br />
  </p>

  <h4>INI format and complete field description</h4>
  <h5>Mandatory field</h5>

  <ul>
    <li>
      RessourceFile is a single string that contains the address of a sound.<br />
      Usage:<br />
      <br />
      $SRessourceFile@=$L"Sound file that will be loaded"@<br />
    </li>
  </ul>

  <h5>Optionnal fields</h5>

  <ul>
    <li>
      Volume is the volume of the sound. It should be an integer between 0 and 100.
      <br />
      <br />
      $SVolume@=42
    </li>

    <li>
      Pitch is the accelleration of the sound. A pitch of 2 will shorter the
      sound, but also make it more acute. A pitch of 0.5 will make it longer
      and also more low. A single double is neccessary.<br />
      <br />
      $SPitch@=3
    </li>

    <li>
      Loop indicates if the sound must be play continuously or a single time.
      A single integer is required, like 1, $Ctrue@, 0 or $Cfalse@.<br />
      <br />
      $SLoop@=$Ctrue@
    </li>

    <li>
      Position indicates the position of the sound in space.
      It is three double.<br />
      <br />
      $SPosition@=X,Y,Y
    </li>

    <li>
      Attenuation is how fast the sound decrease when going far away. It is a single
      double. that should be between 0 and 10.<br />
      <br />
      $SAttenuation@=10
    </li>
  </ul>

  <h4>CSV format</h4>

  <p>
    The CSV format does not follow the same architecture as the INI one.
    Here is its architecture:<br />
    <br />
    $L"ressourcefile"@;$L"path_to_ressource_file"@<br />
    $L"volume"@;volume<br />
    $L"pitch"@;pitch<br />
    $L"loop"@;loop<br />
    $L"position"@;x;y;z<br />
    $L"attenuation"@;attenuation<br />
    <br />
  </p>

  <h4>DABSIC format</h4>

  <p>
    The DABSIC format follow the same architecture as the INI one.
    Here is its architecture:<br />
    <br />
    $SRessourceFile@=$L"Sound file that will be loaded"@<br />
    $SVolume@=42<br />
    $SPitch@=3<br />
    $SLoop@=$Ctrue@<br />
    {$SPosition@ X, Y, Y }<br />
    $SAttenuation@=10<br />
    <br />
  </p>
  <h4>XML format</h4>

  <p>
    Not documented yet.
  </p>

  <h4>LUA format</h4>

  <p>
    Not documented yet.
  </p>

  <h4>JSON format</h4>

  <p>
    Not documented yet.
  </p>

  <h4>LISP format</h4>

  <p>
    Not documented yet.
  </p>


  <h4>YAML format</h4>

  <p>
    There is no support for YAML yet.
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

