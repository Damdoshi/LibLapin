<div class="prototype">
  $Ktypedef struct@ $Ts_bunny_music@<br />
  {<br />
  $A $Tt_bunny_sound@ $Ssound@;<br />
  $A $Kconst@ $Tdouble@ $Sduration@;<br />
  <br />
  } $Tt_bunny_music@;<br />
</div>
<hr />

<div class="resume">
  <h3>Description</h3>
  $A This structure represents a music. It is based on t_bunny_sound
  and have an additionnal duration. Music are not loaded into memory
  but read from disk and load chunk by chunk automatically.<br />
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
      $Kconst@ $Tdouble@ $Sduration@:<br />
      $A The duration of the music in seconds.
    </li>
  </ul>
</div>

<div class="related_functions">
  <h3>Related functions</h3>
  <ul>
    <li>t_bunny_sound</li>
    <li>bunny_load_music</li>
    <li>bunny_delete_sound</li>
  </ul>
</div>
