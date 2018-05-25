<div class="prototype">
  $Tt_bunny_sound_sprite@ *$Sbunny_load_sound_sprite@($Kconst@ $Tchar@ *$Sfile@);
</div>
<hr />

<div class="resume">
  <h3>Description</h3>
  $A Open a configuration file describing a way to exploit a sound file.
  <br />
  <br />
  Delete the sound sprite file with bunny_delete_sound when you do not
  need it anymore.
</div>
<hr />

<div class="parameters">
  <h3>Parameters</h3>
  <ul>
    <li>
      $Kconst@ $Tchar@ *$Sfile@:<br />
      $A The sound sprite configuration file to open.
      Supported files are any file support by bunny_configuration.<br />
      The configuration file format is described below.
    </li>
  </ul>
</div>
<hr />

<div class="return">
  <h3>Return value</h3>
  <ul>
    <li>
      On $Bsuccess@, the function returns a valid t_bunny_sound_sprite pointer.
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
    $L"sound"@,
    $L"syntax"@ or
    $L"sound_sprite"@
    labels.
  </p>
</div>
<hr />

<div class="details">
  <h3>Configuration file format</h3>

  <h4>DABSIC format and complete field description</h4>
  <h5>Mandatory field</h5>

  <ul>
    <li>
      Any field mandatory for a t_bunny_music is mandatory for a
      t_bunny_sound_sprite.
    </li>
    <li>
      A t_bunny_sound_sprite also needs a 'Slices' node to describe
      slices. Example:<br />
      <br />
      [Slices
      $A[Slice00
      $A$A'Content
      $A]
      ]
    </li>
    <li>
      Inside the node describing a single slice in the 'Slices' node,
      two fields are mandatory. The first one is the 'Index' double.
      It is in seconds and is used to indicates where the slice start
      in the sound file.
      Example:<br />
      <br />
      [Slices
      $A[Slice00
      $A$AIndex=2.0
      $A$ADuration=1.0
      $A]
      ]<br />
      <br />
    </li>
    <li>
      The other mandatory field is 'Duration' and indicates the duration
      of the sound slice.
      Example:<br />
      <br />
      [Slices
      $A[Slice00
      $A$AIndex=2.0
      $A$ADuration=1.0
      $A]
      ]<br />
      <br />
  </ul>

  <h5>Optionnal fields</h5>

  <ul>
    <li>
      The 'ActiveDuration' is an optionnal double value which can be used
      inside the slice configuration node. It is associated with the
      $Sactive_duration@ field of the $Tt_bunny_sound_slice@ structure.
      If absent, its default value is the 'Duration' field.
    </li>
    <li>
      There can be other optionnal fields in the slice configuration
      node: the same as for a t_bunny_sound: Volume, Pitch, Loop,
      Position and Attenuation.
    </li>
    <li>
      There can be other optionnal fields in the root configuration
      of the t_bunny_sound_sprite: the same as for a t_bunny_sound:
      Volume, Pitch, Loop, Position and Attenuation.
    </li>
  </ul>

  <h4>INI format</h4>

  <p>
    The INI format follow the same architecture as the DABSIC one.
    Here is its architecture:<br />
    <br />
    $SRessourceFile@=$L"Sound file that will be loaded"@<br />
    $SVolume@=42<br />
    $SPitch@=3<br />
    $SLoop@=$Ctrue@<br />
    $SPosition@=X, Y, Y<br />
    $SAttenuation@=10<br />
    [$TSlices.Slice00@]<br />
    $SIndex@=1.0<br />
    $SDuration@=2.0<br />
    $SActiveDuration@=1.0<br />
    $SVolume@=84<br />
    $SPitch@=2<br />
    $SLoop@=$Cfalse@<br />
    #Etc<br />
    [$TSlices.Slice01@]<br />
    #Etc<br />
    <br />
  </p>

  <h4>CSV format</h4>

  <p>
    Not documented yet.
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
    <li>bunny_sound_sprite_play_slice</li>
    <li>bunny_sound_sprite_stop_slice</li>
    <li>bunny_sound_sprite_trap_or_sync</li>
    <li>bunny_sound_sprite_is_talking</li>
  </ul>
</div>

