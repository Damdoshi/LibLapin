<div class="prototype">
  $Ktypedef struct@ $Ts_bunny_sound@<br />
  {<br />
  $A $Kconst@ $Tchar@ $S_private@[$Ksizeof@($Tsize_t@)];<br />
  $A $Kconst@ $Tchar@ * $Kconst@ $Sfile@;<br />
  $A $Tdouble@ $Svolume@;<br />
  $A $Tdouble@ $Spitch@;<br />
  $A $Tbool@ $Sloop@;<br />
  $A $Tdouble@ $Sposition@[3];<br />
  $A $Tdouble@ $Sattenuation@;<br />
  $A $Kconst@ $Tbool@ $Splaying@;<br />
  $A $Kconst@ $Tbool@ $Spause@;<br />
  <br />
  } $Tt_bunny_sound@;<br />
</div>
<hr />

<div class="resume">
  <h3>Description</h3>
  $A The sound structure is a partially abstract structure that
  represents a loaded or a read sound.
  It is a base structure for t_buny_effects and t_bunny_music.<br />
  <br />
  Any structure that could take a t_bunny_sound can take any structure
  based on it.
</div>
<hr />

<div class="parameters">
  <h3>Attributes</h3>
  <ul>
    <li>
      $Kconst@ $Tchar@ $S_private@[$Ksizeof@($Tsize_t@)]:<br />
      $A Private fields you should edit or your program may crash.
    </li>
    <li>
      $Kconst@ $Tchar@ * $Kconst@ $Sfile@:<br />
      $A The field from which the sound or music was extracted.
      It is set to empty string ($L""@) if the sound was created
      with bunny_new_effect.
    </li>
    <li>
      $Tdouble@ $Svolume@:<br />
      $A The volume, between 0 and 100, of the sound.
    </li>
    <li>
      $Tdouble@ $Spitch@:<br />
      $A The pitch, greater than 0 with a normal value that is 1, of the sound.
      The pitch is the speed of the sound being played.
    </li>
    <li>
      $Tbool@ $Sloop@:<br />
      $A $Ctrue@ if you need to make this sound being repeated.
    </li>
    <li>
      $Tdouble@ $Sposition@[3]:<br />
      $A The relative 3D position of the sound. Being relative means
      (0, 0, 0) is "on" the program user. Values to set here may vary
      a lot depending of the $Sattenuation@ value. With the default,
      a distance from the origin of maximum 5 is a good choice.
    </li>
    <li>
      $Tdouble@ $Sattenuation@:<br />
      $A The default sound attenuation. In combination with
      the distance, it will decrease the sound volume. By
      default, the attenuation is set to 5.
    </li>
    <li>
      $Kconst@ $Tbool@ $Splaying@:<br />
      $A Is the sound being played?
    </li>
    <li>
      $Kconst@ $Tbool@ $Spause@:<br />
      $A Is the sound paused?
    </li>
  </ul>
</div>

<div class="related_functions">
  <h3>Related functions</h3>
  <ul>
    <li>t_bunny_effect</li>
    <li>t_bunny_music</li>
    <li>bunny_delete_sound</li>
  </ul>
</div>
