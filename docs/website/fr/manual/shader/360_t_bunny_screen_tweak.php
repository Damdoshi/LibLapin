<div class="prototype">
  $Ktypedef struct@ $Ts_bunny_screen_tweak@<br />
  {<br />
  $A $Tfloat@ $Sblur_level@;<br />
  $A $Tfloat@ $Sluminosity@;<br />
  $A $Tt_bunny_@ $Scolor@;<br />
  $A $Tt_bunny_color_blind_tweak@ $Scolor_blind@;<br />
  $A $Tbool@ $Sinvert_color@;<br />
  $A $Tbool@ $Sgray_scale@;<br />
  $A $Tbool@ $Sblack_white@;<br />
  $A $Tt_bunny_noise_color@ $Snoise_color@;<br />
  $A $Tt_bunny_noise_type@ $Snoise_type@;<br />
  $A $Tdouble@ $Snoise_strenght@;<br />
  <br />
  } $Tt_bunny_screen_tweak@;<br />
</div>
<hr />

<div class="resume">
  <h3>Description</h3>
  $A The configuration structure sent to bunny_screen_tweak_shader to
  configure a shader ready to be used.
</div>
<hr />

<div class="parameters">
  <h3>Attributes</h3>
  <ul>
    <li>
      $Tfloat@ $Sblur_level@:<br />
      $A The blur that will be applied to the sent picture.
    </li>
    <li>
      $Tfloat@ $Sluminosity@:<br />
      $A A color coefficient to be multiplied with all color component.
    </li>
    <li>
      $Tdouble@ $Scolor@[3]:<br />
      $A Color coefficients to be multiplied with red, green and blue
      color components, case after case.
    </li>
    <li>
      $Tt_bunny_color_blind_tweak@ $Scolor_blind@:<br />
      $A Color component shifting.
    </li>
    <li>
      $Tbool@ $Sinvert_color@:<br />
      $A Invert color.
    </li>
    <li>
      $Tbool@ $Sgray_scale@:<br />
      $A Set to zero to stay in colors. Precise the amount of gray
      shade you want to be displayed. 1 turns the whole screen black.
      2 turns the whole screen pure black and white. 255 turns the whole
      picture in full grayscale.<br />
      <br />
      <b>Currently, the effect is not working as expected.</b>
    </li>
    <li>
      $Tt_bunny_noise_color@ $Snoise_color@:<br />
      $A Define the color of the additionnal noise.
    </li>
    <li>
      $Tt_bunny_noise_tpye@ $Snoise_type@:<br />
      $A Set the noise graphic type.
    </li>
    <li>
      $Tdouble@ $Snoise_strenght@:<br />
      $A The noise opacity.
    </li>
  </ul>
</div>

<div class="related_functions">
  <h3>Related functions</h3>
  <ul>
    <li>bunny_screen_tweak_shader</li>
  </ul>
</div>
