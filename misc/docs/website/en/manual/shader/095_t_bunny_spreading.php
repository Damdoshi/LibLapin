<div class="prototype">
  $Ktypedef struct@ $Ts_bunny_spreading@<br />
  {<br />
  $A $Tt_bunny_color@ $Scolor@[2];<br />
  $A $Tint@ $Sspeed@;<br />
  $A $Tt_bunny_picture@ *$Slayout@;<br />
  $A $Tsize_t@ $Ssource_len@;<br />
  $A $Tt_bunny_position@ $Ssources@[128];<br />
  $A $Tbool@ $Srandom@;<br />

  $M// Private fields@
  $A $Tt_bunny_picture@ *$Salpha_buffer@;<br />
  $A $Tt_bunny_picture@ *$Sspread_buffer@[2];<br />
  $A $Tint@ $Scurrent_buffer@;<br />
  <br />
  } $Tt_bunny_spreading@;<br />
</div>
<hr />

<div class="resume">
  <h3>Description</h3>
  $A This structure describe a color spreading shader.
  A color spreading shader is a shader that will make a specified color
  spread over a picture.
</div>
<hr />

<div class="parameters">
  <h3>Attributes</h3>
  <ul>
    <li>
      $Tt_bunny_color@ $Scolor@[2]:<br />
      $A This field is the color that will be used when the t_bunny_spreading
      is blitted over any target with $Sbunny_blit_shader@.<br />
      Two colors are needed as you can flip from one to the other.<br />
      If you need more than two colors, you can deduce from the $Scurrent_buffer@,
      field the color which is unused and can be modified.
    </li>
    <li>
      $Tint@ $Sspeed@:<br />
      $A This field is the speed of the spreading: it is purely the amount of
      time the shader is called each time you can $Sbunny_blit_spreading@.
    </li>
    <li>
      $Tt_bunny_picture@ *$Slayout@:<br />
      $A This field contains the shape the color can spread on. Pure opaque black
      prevents the color to spread. Any other color allow it.
    </li>
    <li>
      $Tsize_t@ $Ssource_len@:<br />
      $A How many color source there is to allow spreading. If there is no source
      and the buffer is clean, no spreading will occur.
    </li>
    <li>
      $Tt_bunny_position@ $Ssources@[128]:<br />
      $A The position of every source of color that will be spread. Sources should
      be on non opaque black when positioned on $Slayout@.
    </li>
    <li>
      $Tbool@ $Srandom@:<br />
      $A Is the spreading random or not? A non random spreading is regular. It keeps,
      the previous shape. If sources are isolated dots, diamond shapes will appeirs.
      <br />
      <br />
      If random is true, the spreading will be more organic.
    </li>

    <li>
      $Tt_bunny_picture@ *$Salpha_buffer@:<br />
      $A You must set this field to $CNULL@.
    </li>
    <li>
      $Tt_bunny_picture@ *$Sspread_buffer@[2]:<br />
      $A You must set those fields to $CNULL@.
    </li>
    <li>
      $Tint@ $Scurrent_buffer@:<br />
      $A You must set this field to 0.
    </li>
  </ul>
</div>

<div class="related_functions">
  <h3>Related functions</h3>
  <ul>
    <li>bunny_spreading_shader</li>
    <li>bunny_blit_spreading</li>
    <li>bunny_fill_spreading</li>
    <li>bunny_flip_spreading</li>
    <li>bunny_draw_spreading_source</li>
    <li>bunny_clear_spreading</li>
    <li>bunny_delete_spreading</li>
  </ul>
</div>
