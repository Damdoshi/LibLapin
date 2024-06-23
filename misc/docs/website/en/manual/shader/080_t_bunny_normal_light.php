<div class="prototype">
  $Ktypedef struct@ $Ts_bunny_normal_light@<br />
  {<br />
  $A $Tbool@ $Sactive@;<br />
  $A $Tfloat@ $Sx@;<br />
  $A $Tfloat@ $Sy@;<br />
  $A $Tfloat@ $Sz@;<br />
  $A $Tt_bunny_color@ $Slight_color@;<br />
  $A $Tfloat@ $Slight_attenuation@;<br />
  <br />
  $A $Tt_bunny_color@ $Sambient_color@;<br />
  $A $Tfloat@ $Sambient_depth@;<br />
  $A $Tfloat@ $Sambient_attenuation@;<br />
  <br />
  $A $Tt_bunny_color@ $Sspecular_color@;<br />
  $A $Tfloat@ $Sspecular_depth@;<br />
  $A $Tfloat@ $Sspecular_attenuation@;<br />
  <br />
  } $Tt_bunny_normal_light@;<br />
</div>
<hr />

<div class="resume">
  <h3>Description</h3>
  $A This structure is a substructure of the t_bunny_normal_map structure
  which serve as configuration structure for bunny_normal_map_shader
  and the rendering of pictures which include a normal map to handle
  dynamic lighting.
</div>
<hr />

<div class="parameters">
  <h3>Attributes</h3>
  <ul>
    <li>
      $Tbool@ $sactive@:<br />
      $A Is the light described in this structure active or not?
      If not, it is useless to set other fields in this structure.
    </li>
    <li>
      $Tfloat@ $Sx@:<br />
      $A The position on X of the light on screen.
    </li>
    <li>
      $Tfloat@ $Sy@:<br />
      $A The position on Y of the light on screen.
    </li>
    <li>
      $Tfloat@ $Sz@:<br />
      $A The position on Z in space. This modulates the impact
      of the light by impacting reflections.
    </li>
    <li>
      $Tt_bunny_color@ $Slight_color@:<br />
      $A The light color on illuminated space.
    </li>
    <li>
      $Tfloat@ $Slight_attenuation@:<br />
      $A The attenuation of the light accordingly to the distance.
      0.5 is a good reference value.
    </li>
    <li>
      $Tt_bunny_color@ $Sambient_color@:<br />
      $A The color of space around the light.
    </li>
    <li>
      $Tfloat@ $Sambient_depth@:<br />
      $A The position on the Z axis of the ambient light. 0.4 is a good
      reference value.
    </li>
    <li>
      $Tfloat@ $Sambient_attenuation@:<br />
      $A The attenuation of the light accordingly to the distance.
      4.0 is a good reference value.
    </li>
    <li>
      $Tt_bunny_color@ $Sspecular_color@:<br />
      $A The color of heavily enlighted areas. The $Sspecular_color@
      is quite impacted by the color on the t_bunny_normal_map $Sspecular_map@.
    </li>
    <li>
      $Tfloat@ $Sspecular_depth@:<br />
      $A The position on the Z axis of the ambient light. 0.3 is a good
      reference value.
    </li>
    <li>
      $Tfloat@ $Sspecular_attenuation@:<br />
      $A The attenuation of the light accordingly to the distance.
      1.0 is a good reference value.
    </li>
  </ul>
</div>

<div class="related_functions">
  <h3>Related functions</h3>
  <ul>
    <li>t_bunny_normal_map</li>
    <li>bunny_normal_map_shader</li>
  </ul>
</div>
