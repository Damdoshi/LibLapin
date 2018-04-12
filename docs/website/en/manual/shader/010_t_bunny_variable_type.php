<div class="prototype">
  $Ktypedef enum@ $Te_bunny_variable_type@<br />
  {<br />
  $A $SBVT_1_FLOAT@,<br />
  $A $SBVT_2_FLOAT@,<br />
  $A $SBVT_3_FLOAT@,<br />
  $A $SBVT_4_COLOR_COMPONENT@,<br />
  $A $SBVT_FULL_COLOR@,<br />
  $A $SBVT_TRANSFORM@,<br />
  $A $SBVT_PICTURE@,<br />
  $A $SBVT_CURRENT_TEXTURE_TYPE@<br />
  <br />
  } $Tt_bunny_variable_type@;
</div>
<hr />

<div class="resume">
  <h3>Description</h3>
  $A The t_bunny_variable_type is used by bunny_shader_set_variable
  to set inside a t_bunny_shader the value of a variable used inside
  the shader program with the correct type.<br />
  This enumeration describes types accepted by the shader and
  the function.
</div>
<hr />

<div class="parameters">
  <h3>Symbols</h3>
  <ul>
    <li>
      $SBVT_1_FLOAT@:<br />
      $A This indicates bunny_shader_set_variable will receive 1 float.
    </li>
    <li>
      $SBVT_2_FLOAT@:<br />
      $A This indicates bunny_shader_set_variable will receive 2 floats.
      The reception type is vec2.
    </li>
    <li>
      $SBVT_3_FLOAT@:<br />
      $A This indicates bunny_shader_set_variable will receive 3 floats.
      The reception type is vec4.
    </li>
    <li>
      $SBVT_4_COLOR_COMPONENT@:<br />
      $A This indicates bunny_shader_set_variable will receive 4 int on
      1 byte.
    </li>
    <li>
      $SBVT_FULL_COLOR@:<br />
      $A This indicates bunny_shader_set_variable will receive 1 int on
      4 bytes.
    </li>
    <li>
      $SBVT_TRANSFORM@:<br />
      $A This indicates bunny_shader_set_variable will receive a pointer
      on a t_bunny_transform.
    </li>
    <li>
      $SBVT_PICTURE@:<br />
      $A This indicates bunny_shader_set_variable will receive a pointer
      on a t_bunny_picture.
    </li>
    <li>
      $SBVT_CURRENT_TEXTURE_TYPE@:<br />
      $A This indicates the variable the bunny_shader_set_variable
      will be set by bunny_blit, from the second parameter.
    </li>
  </ul>
</div>
<hr />

<div class="related_functions">
  <h3>Related functions</h3>
  <ul>
    <li>bunny_shader_set_variable</li>
  </ul>
</div>

