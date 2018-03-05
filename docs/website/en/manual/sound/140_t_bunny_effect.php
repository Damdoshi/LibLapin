<div class="prototype">
  $Ktypedef struct@ $Ts_bunny_effect@<br />
  {<br />
  $A $Tt_bunny_sound@ $Ssound@;<br />
  $A $Kconst@ $Tdouble@ $Sduration@;<br />
  <br />
  } $Tt_bunny_effect@;<br />
</div>
<hr />

<div class="resume">
  <h3>Description</h3>
  $A This structure describe a sound effect. If not simply generated
  from bunny_load_effect, it may be a little complex: the t_bunny_effect
  is the equivalent of t_bunny_pixelarray but for sound: they are a track
  that will be read, short int after short int, to generate a sound.
  <br />
  Any function that takes a t_bunny_sound as parameter can take
  a t_bunny_music as one.
</div>
<hr />

<div class="parameters">
  <h3>Attributes</h3>
  <ul>
    <li>
      $Tt_bunny_sound@ $Ssound@:<br />
      $A The sound base.
    </li>
    <li>
      $Kconst@ $Tsize_t@ $Ssample_per_second@:<br />
      $A The duration of the music in seconds.
    </li>
    <li>
      $Kconst@ $Tdouble@ $Sduration@:<br />
      $A The duration in seconds. Multiplied by $Ssample_per_second@
      will give you the length of $Ssample@.
    </li>
    <li>
      $Tint16_t@ * $Kconst@ $Ssample@:<br />
      $A A constant address to a writable area of *Ssample_per_second@ *
      $Sduration@ short signed int. Each case store a value which
      compose the wave of the sound effect. <br />
      <br />
      Modifications inside the sound effect will be computed
      by calling bunny_compute_effect. If you do not call it before
      playing, your modifications will be ignored.
    </li>
  </ul>
</div>

<div class="related_functions">
  <h3>Related functions</h3>
  <ul>
    <li>bunny_new_effect</li>
    <li>bunny_load_effect</li>
    <li>bunny_compute_effect</li>
    <li>bunny_delete_sound</li>
  </ul>
</div>
