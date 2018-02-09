<div class="prototype">
  $Ktypedef struct@ $Ts_bunny_animation@<br />
  {<br />
  $A $Tuint64_t@ $Shash@;<br />
  $A $Tdouble@ $Sdelay@;<br />
  $A $Tuint32_t@ $Snbr_frame@;<br />
  $A $Tt_bunny_position@ $Sposition@;<br />
  $A $Tt_bunny_vector@ *$Sframe_repetition@;<br />
  $A $Tt_bunny_frame_browsing@ $Sbrowsing@;<br />
  $A $Tint32_t@ $Sanimation_repeat@;<br />
  $A $Tint32_t@ $Snext_animation@;<br />
  <br />
  } $Tt_bunny_animation@;
</div>
<hr />

<div class="resume">
  <h3>Description</h3>
  $A This structure represents a single animation from a sprite sheet.
  For example, it will be a character running. This type is more internal
  than user-side, but you may want to edit it at runtime.<br />
  <br />
  <b>
    Some field should definitively be constant and may become on a next version.
    Concerned fields will be noted here.
  </b>
</div>
<hr />

<div class="parameters">
  <h3>Attributes</h3>
  <ul>
    <li>
      $Tuint64_t@ $Shash@:<br />
      $A The animation name, hashed with an inside algorithm.
      <b>This field will become const in a next version. Do not edit it.</b>
    </li>
    <li>
      $Tdouble@ $Sdelay@:<br />
      $A The delay between any frame shift, in seconds.
    </li>
    <li>
      $Tuint32_t@ $Snbr_frame@:<br />
      $A How many pictures is there in this animation.
    </li>
    <li>
      $Tt_bunny_position@ $Sposition@:<br />
      $A The position in pixel of the first frame of the animation in the
      whole sprite sheet.
    </li>
    <li>
      $Tt_bunny_vector@ *$Sframe_repetition@:<br />
      $A This vector is $Snbr_frame@ long. Each case contain a value greater
      or equal to zero that indicates how many time some frame must be repeated
      before switching to the next one.<br />
      For example, take a three frame long animation, the vector
      will have three cases. It may contains, for example: 1, 3 and 1.
      This means that at step 0, the first frame will be displayed.
      At step 1, 2 and 3, the second frame will be displayed.
      At step 4, the last one.
      <b>
        This pointer itself will become constant. Do not edit it. You can
        still change the content of the vector.
      </b>
    </li>
    <li>
      $Tt_bunny_frame_browsing@ $Sbrowsing@:<br />
      $A How the frame are browsed.
    </li>
    <li>
      $Tint32_t@ $Sanimation_repeat@:<br />
      $A How many time the full animation must be played before being
      considered terminated and switch to $Snext_animation@.
      Set this field to -1 will indicates infinite repetition.
    </li>
    <li>
      $Tint32_t@ $Snext_animation@:<br />
      $A The id of the next animation on which the system will
      automatically switch until the current one is considered terminated.
      It can be set to -1 to indicates there is no next animation.
      <b>This field will become const in a next version. Do not edit it.</b>
    </li>
  </ul>
</div>
<hr />

<div class="related_functions">
  <h3>Related functions</h3>
  <ul>
    <li>t_bunny_frame_browsing</li>
    <li>t_bunny_sprite</li>
  </ul>
</div>

