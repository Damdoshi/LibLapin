<div class="prototype">
  $Ktypedef struct@ $Ts_bunny_normal_map@<br />
  {<br />
  $A $Tt_bunny_size@ $Swindow_size@;<br />
  $A $Tt_bunny_picture@ *$Snormal_map@;<br />
  $A $Tt_bunny_picture@ *$Sspecular_map@;<br />
  $A $Tt_bunny_normal_light@ $Slights@[8];<br />
  <br />
  } $Tt_bunny_normal_map@;<br />
</div>
<hr />

<div class="resume">
  <h3>Description</h3>
  $A This structure describe a dynamic lighting shader.
  It includes ressources you have to define and not only
  simple datas. By sending it to bunny_normal_map_shader,
  you will configure or reconfigure a complete shader.
</div>
<hr />

<div class="parameters">
  <h3>Attributes</h3>
  <ul>
    <li>
      $Tt_bunny_size@ $swindow_size@:<br />
      $A The size of the buny_blit_shader target surface.
    </li>
    <li>
      $Tt_bunny_picture@ *$Snormal_map@:<br />
      $A A picture that contains the relief to apply to
      the bunny_blit_shader source picture. For example,
      this picture in the middle is a normal map, and
      here is how it works:<br />
      <br />
      <div style="text-align: center;">
        <img src="./res/color.png" />
        <img src="./res/normal.png" />
        <img src="./res/color_normal.png" />
      </div>
    </li>
    <li>
      $Tt_bunny_picture@ *$Sspecular_map@:<br />
      $A A picture that contains the color that will be applied,
      after having the $Sspecular_color@ mask applied where
      the specular light have an effect. It could be entirely white.
    </li>
    <li>
      $Tt_bunny_normal_light@ $Slights@[8];<br />
      $A Lights that will impact the way the picture is drawn
      when a bunny_blit_shader is made. Enlighting some parts
      and leave other to darkness.<br />
      <b>Caution</b>: The amount of lights have a real impact on
      performences.
    </li>
  </ul>
</div>

<div class="related_functions">
  <h3>Related functions</h3>
  <ul>
    <li>t_bunny_normal_light</li>
    <li>bunny_normal_map_shader</li>
  </ul>
</div>
