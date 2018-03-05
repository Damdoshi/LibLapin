<div class="prototype">
  $Ktypedef struct@ $Ts_bunny_pixelarray@<br />
  {<br />
  $A $Tt_bunny_clipable@ $Sclipable@;<br />
  $A $Tvoid@ * $Kconst@ $Spixels@;<br />
  <br />
  } $Tt_bunny_pixelarray@;<br />
</div>
<hr />

<div class="resume">
  <h3>Description</h3>
  $A This structure inherit from t_bunny_clipable and add an array
  that match the complete size of the graphic buffer inside. It is
  designed to allow per-pixel drawing on <b>CPU</b> side.<br />
  It is faster to do this very specific kind of computing (which is not
  so often required but may be) but very slow when doing sprite based
  program (in this case, t_bunny_picture goes really much faster).
  <br />
  <br />
  Because the bunny library was designed as pedagogical tool
  and may be used for this purpose again in the future, the t_bunny_pixelarray
  management is not fully developped inside the bunny library: drawing
  on it must be done by hand and alpha blending, rotation or scaling from
  t_bunny_pixelarray to t_bunny_picture or t_bunny_window is disabled by default.
  It can be enable with bunny_enable_full_blit.
</div>
<hr />

<div class="parameters">
  <h3>Attributes</h3>
  <ul>
    <li>
      $Tt_bunny_clipable@ $Sclipable@:<br />
      $A The mother structure.
    </li>
    <li>
      $Tvoid@ * $Kconst@ $Spixels@:<br />
      $A The picture pixels themselves. They are width multiplied by height
      multiplied by color size long.
    </li>
  </ul>
</div>

<div class="related_functions">
  <h3>Related functions</h3>
  <ul>
    <li>bunny_new_pixelarray</li>
    <li>bunny_load_pixelarray</li>
    <li>bunny_read_pixelarray_id</li>
    <li>bunny_read_pixelarray</li>
    <li>bunny_save_pixelarray</li>
    <li>t_bunny_my_load_pixelarray</li>
    <li>gl_bunny_my_load_pixelarray</li>
    <li>t_bunny_my_read_pixelarray</li>
    <li>gl_bunny_my_read_pixelarray</li>
  </ul>
</div>
