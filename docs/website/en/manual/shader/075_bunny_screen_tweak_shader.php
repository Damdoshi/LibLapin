<div class="prototype">
  $Tt_bunny_shader@ *$Sbunny_screen_tweak_shader@(
  $Kconst@ $Tt_bunny_screen_tweak@ *$Sbst@
  );
</div>
<hr />

<div class="resume">
  <h3>Description</h3>
  $A Read the sent structure and generate the associated shader.
  Multiples calls to bunny_screen_tweak_shader will not generate
  several shader: the returned one is kept in memory and reconfigured
  each time. It is automatically freed when your program exit, but
  you can force its release by sending $CNULL@ as $Sbst@.
</div>
<hr />

<div class="parameters">
  <h3>Parameters</h3>
  <ul>
    <li>
      $Kconst@ $Tt_bunny_screen_tweak@ *$Sbst@:<br />
      $A The shader configuration structure. See t_bunny_screen_tweak
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
    <li>t_bunny_screen_tweak</li>
    <li>bunny_blit_shader</li>
    <li>bunny_delete_shader</li>
  </ul>
</div>

