<div class="prototype">
  $Ktypedef@ $Tvoid@ (*$St_bunny_my_blit@)(
  $Tt_bunny_pixelarray@ *$Starget@,
  $Kconst@ $Tt_bunny_pixelarray@ *$Ssource@,
  $Kconst@ $Tt_bunny_position@ *$Sposition@
  );
</div>
<hr />

<div class="resume">
  <h3>Description</h3>
  $A This type is the one used by gl_bunny_my_blit function pointer
  that may be used to complete bunny_blit by giving it the ability to
  blit t_bunny_pixelarray over another t_bunny_pixelarray.
</div>
<hr />

<div class="parameters">
  <h3>Parameters</h3>
  <ul>
    <li>
      $Tt_bunny_pixelarray@ *$Starget@:<br />
      $A The picture, that can be any t_bunny_buffer children, even if in most
      cases it is a t_bunny_window, that will serve as drawing target.
    </li>
    <li>
      $Kconst@ $Tt_bunny_clipable@ *$Ssource@:<br />
      $A The picture that will be used a graphic source.
    </li>
    <li>
      $Kconst@ $Tt_bunny_position@ *$Sposition@:<br />
      $A Indicates the position in $Starget@ where to draw $Ssource@. It
      can be $CNULL@ and if it is, then the position inside $Ssource@ is
      used as position.
    </li>
  </ul>
</div>
<hr />

<div class="related_functions">
  <h3>Related functions</h3>
  <ul>
    <li>bunny_blit</li>
    <li>bunny_enable_full_blit</li>
    <li>gl_bunny_my_blit</li>
  </ul>
</div>

