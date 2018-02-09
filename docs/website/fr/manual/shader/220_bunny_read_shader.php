<div class="prototype">
  $Tbool@ $Sbunny_read_shader@(
  $Tt_bunny_shader@ *$Sshader@,
  $Kconst@ $Tchar@ *$Svertex_string@,
  $Kconst@ $Tchar@ *$Sfragment_string
  );
</div>
<hr />

<div class="resume">
  <h3>Description</h3>
  $A Load into the sent reserved shader a vertex configuration
  from a string and a fragment configuration from another one.
</div>
<hr />

<div class="parameters">
  <h3>Parameters</h3>
  <ul>
    <li>
      $Tt_bunny_shader@ *$Sshader@:<br />
      $A The shader to configure.
    </li>
    <li>
      $Kconst@ $Tchar@ *$Svertex_string:<br />
      $A The vertex shader configuration. $CNULL@ can be sent
      to use a default vertex shader to only allow 2D edition
      throught the shader described in $Sfragment_file@.
    </li>
    <li>
      $Kconst@ $Tchar@ *$Sfragment_string:<br />
      $A The fragment shader configuration.
    </li>
  </ul>
</div>
<hr />

<div class="return">
  <h3>Return value</h3>
  <p>This function returns $Ctrue@ or $Cfalse@ depending of its success.
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
      $CEINVAL@:<br />
      <p>
        A fragment shader was expected.
      </p>
    </li>
    <lI>
      $CBE_SYNTAX_ERROR@:<br />
      <p>
        A syntax error was found in a shader.
      </p>
  </ul>
  <br />
  <p>
    Logs written by this function are tagged with the
    $L"ressource"@,
    $L"graphics"@
    and/or
    $L"syntax"@
    label.
  </p>
</div>
<hr />

<div class="related_functions">
  <h3>Related functions</h3>
  <ul>
    <li>bunny_new_shader</li>
    <li>bunny_read_shader</li>
    <li>bunny_blit_shader</li>
    <li>bunny_delete_shader</li>
  </ul>
</div>

