<div class="prototype">
  $Tt_bunny_shader@ *$Sbunny_new_shader@($void@);
</div>
<hr />

<div class="resume">
  <h3>Description</h3>
  $A Generate a new shader on your graphic board
  ready to be configured.<br />
  <br />
  You can free the allocated memory space with bunny_delete_shader.
</div>
<hr />

<div class="return">
  <h3>Return value</h3>
  <ul>
    <li>
      On $Bsuccess@, the function returns a valid t_bunny_shader
      ready to be configured with bunny_load_shader and
      bunny_shader_set_variable.
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
        Out of memory.
      </p>
    </li>
  </ul>
  <br />
  <p>
    Logs written by this function are tagged with the
    $L"ressource"@ and $L"graphics"@ label.
  </p>
</div>
<hr />

<div class="related_functions">
  <h3>Related functions</h3>
  <ul>
    <li>bunny_blit_shader</li>
    <li>bunny_delete_shader</li>
    <li>bunny_load_shader</li>
    <li>bunny_shader_set_variable</li>
  </ul>
</div>

