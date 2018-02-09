<div class="prototype">
  $Ktypedef enum@ $Te_bunny_noise_type@<br />
  {<br />
  $A $SBNT_NO_NOISE@,<br />
  $A $SBNT_PIXEL_NOISE@,<br />
  $A $SBNT_LINE_NOISE@<br />
  $A $SBNT_ROW_NOISE@<br />
  <br />
  } $Tt_bunny_noise_type@;
</div>
<hr />

<div class="resume">
  <h3>Description</h3>
  $A This enumeration is used by t_bunny_screan_tweak to
  configure the shape of the additional noise over the picture.
</div>
<hr />

<div class="parameters">
  <h3>Symbols</h3>
  <ul>
    <li>
      $SBNT_NO_NOISE@:<br />
      $A There is no noise.
    </li>
    <li>
      $SBNT_PIXEL_NOISE@:<br />
      $A Noise is different on every pixel.
    </li>
    <li>
      $SBNT_LINE_NOISE@:<br />
      $A Noise is different on every horizontal line.
    </li>
    <li>
      $SBNT_ROW_NOISE@:<br />
      $A Noise is different on every vertical line.
    </li>
  </ul>
</div>
<hr />

<div class="related_functions">
  <h3>Related functions</h3>
  <ul>
    <li>t_bunny_screen_tweak</li>
    <li>bunny_screen_tweak_shader</li>
  </ul>
</div>

