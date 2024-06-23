<div class="prototype">
  $Ktypedef struct@ $Ts_bunny_splash_screen@<br />
  {<br />
  $A $Tt_bunny_context_runtime_info@ $Shead@;<br />
  $A $Tchar@ *$Sbunny_picture_file@;<br />
  $A $Tchar@ *$Srope_picture_file@;<br />
  $A $Tchar@ *$Stitle_picture_file@;<br />
  $A $Tchar@ *$Sjingle_sound_file@;<br />
  $A $Tchar@ *$Sboom_sound_file@;<br />
  $A $Tchar@ *$Soutch_sound_file@;<br />
  $A $Tchar@ *$Sfalling_sound_file@;<br />
  $A $Kconst@ $Tchar@ $S_private@[512@;<br />
  <br />
  } $Tt_bunny_splash_screen@;<br />
</div>
<hr />

<div class="resume">
  <h3>Description</h3>
  $A This structure allow you to display the
  <a href="http://hangedbunnystudio.com">Hanged Bunny Studio</a>
  splash screen. It is mainly used by
  <a href="http://hangedbunnystudio.com">Hanged Bunny Studio</a> games, of course.
  <br />
  <br />
  To be used, all strings that relate to file must be filled. Those fields
  are not automatically set to adapt to different repository file organisation.
  <br />
  <br />
  You must set in $Shead@ a $Sscreen@ that will be used as graphic target.
  You can set any function pointer inside $Ssubcontext@ and any $Smain_structure@
  or $Snext_context@.
</div>

