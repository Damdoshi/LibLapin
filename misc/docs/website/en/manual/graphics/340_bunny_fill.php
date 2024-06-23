<div class="prototype">
  $Tvoid@ $Sbunny_fill@(
  $Tt_bunny_buffer@ *$Starget@,
  $Tunsigned int@ $Scolor@
  );
</div>
<hr />

<div class="resume">
  <h3>Description</h3>
  $A This function apply a color to the whole $Starget@. If under
  its disguise, the $Starget@ is a t_bunny_clipable, only the clip subpart
  is colored.
  <br />
  <br />
  The alpha channel consideration make the difference between bunny_clear
  and bunny_fill. bunny_fill take care of alpha channel, bunny_clear does
  not.
  <br />
  <br />
  This function will work on t_bunny_pixelarray only if a pointer of type
  t_bunny_my_fill is set to gl_bunny_my_fill.
</div>
<hr />

<div class="parameters">
  <h3>Parameters</h3>
  <ul>
    <li>
      $Tt_bunny_buffer@ *$Starget@:<br />
      $A The surface on which drawing will be done.
    </li>
    <li>
      $Tunsigned int@ $Scolor@:<br />
      $A The color that will be applied. Alpha channel <b>is</b> included
      in the color computation.
    </li>
  </ul>
</div>
<hr />

<div class="related_functions">
  <h3>Related functions</h3>
  <ul>
    <li>bunny_set_pixel</li>
    <li>bunny_set_circle</li>
    <li>bunny_set_line</li>
    <li>bunny_set_polygon</li>
    <li>bunny_set_geometry</li>
    <li>bunny_clear</li>
  </ul>
</div>

