<div class="prototype">
  $Tvoid@ $Sbunny_blit_shader@(
  $Tt_bunny_buffer@ *$Starget@,
  $Kconst@ $Tt_bunny_picture@ *$Spicture@,
  $Kconst@ $Tt_bunny_position@ *$Sposition@,
  $Kconst@ $Tt_bunny_shader@ *$Sshader@
  );
</div>
<hr />

<div class="resume">
  <h3>Description</h3>
  $A This function is the exact equivalent of one of the main
  LibLapin function: bunny_blit. If you do not know this function,
  please read its manual.<br />
  <br />
  The only difference stands with the additionnal shader parameter
  which implies the shader will be executed. If you have defined
  with bunny_shader_set_variable a $SBVT_CURRENT_TEXTURE_TYPE@ and
  you should have done it, then the $Spicture@ parameter will be
  sent to the variable you configured.<br />
  <br />
  <b>Caution</b>:
  This function currently break the inheritence rule: the $Starget@
  cannot be a t_bunny_pixelarray, even if there is a t_bunny_buffer
  inside  a t_bunny_pixelarray.<br />
  In the same fashion, $Spicture@, even if t_bunny_picture is a $Ktypedef@
  on t_bunny_clipable and t_bunny_pixelarray have a t_bunny_clipable
  inside, this is not compatible. The $Spicture@ parameter must be
  a t_bunny_picture created by a bunny_load_picture.
</div>
<hr />

<div class="parameters">
  <h3>Parameters</h3>
  <ul>
    <li>
      $Tt_bunny_buffer@ *$Starget@:<br />
      $A The target on which everything will be drawn.
      Caution: t_bunny_pixelarray are specific types that needs completion
      to work. See the t_bunny_pixelarray manual for more information.
    </li>
    <li>
      $Kconst@ $Tt_bunny_picture@ *$Spicture@:<br />
      $A The original picture to draw, considering the modification that will be
      made with the shader.
    </li>
    <li>
      $Kconst@ $Tt_bunny_position@ *$Sposition@:<br />
      $A The position on which $Spicture@ will be drawn. If this parameter
      is NULL, then the position stored inside $Sposition@ itself will be used.
    </lI>
    <li>
      $Kconst@ $Tt_bunny_shader@ *$Sshader@:<br />
      $A The shader that will be use to tweak the drawing.
    </li>
  </ul>
</div>
<hr />

<div class="related_functions">
  <h3>Related functions</h3>
  <ul>
    <li>bunny_blit</li>
  </ul>
</div>

