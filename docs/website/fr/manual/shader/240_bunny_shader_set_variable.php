<div class="prototype">
  $Tvoid@ $Sbunny_shader_set_variable@(
  $Tt_bunny_shader@ *$Sshader@,
  $Kconst@ $Tchar@ *$Svariable_name@,
  $Tt_bunny_variable_type@ $Stype@,
  $S...@);
</div>
<hr />

<div class="resume">
  <h3>Description</h3>
  $A In most vertex and fragment shaders, we can find parameters
  that must be sent from the cpu-side program. This function serve
  this purpose: it allows you to sent values inside the graphic card
  from your program.
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
      $Kconst@ $Tchar@ *$Svariable_name:<br />
      $A The name of the variable you want to set inside the shader.
    </li>
    <li>
      $Tt_bunny_variable_type@ $Stype@:<br />
      $A Describe what the variadic part of this function will receive
      as parameter.
    </li>
    <li>
      $S...@:<br />
      $A Variables as described by $Stype@. Please pay attention to
      what you send!<br />
      For example: if you sent BVT_1_FLOAT as $Stype@ but then
      give an int as parameter, no conversion will occurs! The int
      will be interpreted as it as a float and it will not work
      as you expect.<br />
      Use cast if neccessary.
    </li>
  </ul>
</div>
<hr />

<div class="related_functions">
  <h3>Related functions</h3>
  <ul>
    <li>t_bunny_variable_type</li>
    <li>bunny_read_shader</li>
    <li>bunny_blit_shader</li>
  </ul>
</div>

