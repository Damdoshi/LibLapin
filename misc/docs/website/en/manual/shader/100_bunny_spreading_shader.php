<div class="prototype">
  $Tt_bunny_shader@ *$Sbunny_spreading_shader@(
  $Tt_bunny_spreading@ *$Sspread@,
  );
</div>
<hr />

<div class="resume">
  <h3>Description</h3>
  $A Read the sent structure and generate the associated shader.
  Multiples calls to bunny_spreading_shader will not generate
  several shader: the returned one is kept in memory and reconfigured
  each time. It is automatically freed when your program exit, but
  you can force its release by sending $CNULL@ as $Sspread@.<br />
  <br />
  This function also reserve memory inside the t_bunny_spreading itself
  if fields $Salpha_buffer@ or $Sspread_buffer@ are $CNULL@. To release
  those fields, use $Sbunny_delete_spreading@.
</div>
<hr />

<div class="parameters">
  <h3>Parameters</h3>
  <ul>
    <li>
      $Tt_bunny_spreading@ *$Sspread@:<br />
      $A The shader configuration structure. See t_bunny_spreading
      for more information.<br />
      If you send $CNULL@, the inside shader handled by the function
      will be freed.
    </li>
  </ul>
</div>
<hr />

<div class="return">
  <h3>Return value</h3>
  <p>
    This function returns a valid t_bunny_shader pointer on success.
    $CNULL on failure. If you send $CNULL@ as $Sbst@, then it will
    always return $CNULL@.
  </p>
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
        A fragment shader was expected.
      </p>
    </li>
  </ul>
  <br />
  <p>
    Logs written by this function are tagged with the
    $L"ressource"@,
    $L"graphics"@
    and/or
    $L"shader"@
    label.
  </p>
</div>
<hr />

<div class="related_functions">
  <h3>Related functions</h3>
  <ul>
    <li>t_bunny_spreading</li>
    <li>bunny_blit_spreading</li>
  </ul>
</div>

