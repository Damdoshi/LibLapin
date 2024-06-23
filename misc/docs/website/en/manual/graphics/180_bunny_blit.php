<div class="prototype">
  $Tvoid@ $Sbunny_blit@(
  $Tt_bunny_buffer@ *$Starget@,
  $Kconst@ $Tt_bunny_clipable@ *$Ssource@,
  $Kconst $Tt_bunny_position@ *$Sposition@
  );
</div>
<hr />

<div class="resume">
  <h3>Description</h3>
  $A Draw $Ssource@ on $Starget@ at sent $Sposition@.<br />
  <br />
  All transformations and alpha are not applied if behind $Ssource@, there is a
  t_bunny_pixelarray and if bunny_enable_full_blit was not called with
  true as parameter.<br />
  <br />
  Blits to a t_bunny_pixelarray are not possible, unless you have programmed
  it by yourself by filling the gl_bunny_my_blit global function pointer.
</div>
<hr />

<div class="parameters">
  <h3>Parameters</h3>
  <ul>
    <li>
      $Tt_bunny_buffer@ *$Starget@:<br />
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
    <li>bunny_blit_shader</li>
    <li>bunny_enable_full_blit</li>
    <li>t_bunny_my_blit</li>
    <li>gl_bunny_my_blit</li>
  </ul>
</div>

