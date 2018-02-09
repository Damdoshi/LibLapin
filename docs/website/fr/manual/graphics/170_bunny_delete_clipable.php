<div class="prototype">
  Macro
  $Tvoid@ $Sbunny_delete_clipable(*$Sclipable@);
</div>
<hr />

<div class="resume">
  <h3>Description</h3>
  $A Delete the sent clipable.
</div>
<hr />

<div class="parameters">
  <h3>Parameters</h3>
  <ul>
    <li>
      *$Sclipable@:<br />
      $A The clipable to delete.
      If you use <b>C11</b> (Not available in C++), this
      function can handle t_bunny_picture, t_bunny_font, t_bunny_sprite
      and t_bunny_pixelarray automatically.<br />
      If you use a previous version or C++, this function only
      takes a $Tt_bunny_clipable@ and you have to resolve the type
      yourself.
    </li>
  </ul>
</div>
<hr />

<div class="details">
  <h3>Additional informations</h3>
  <p>This macro wraps a call to a real function, which is:</p>
  <p>
    $Tvoid@ $S_bunny_delete_clipable($Tt_bunny_clipable@ *$Sclipable@);
  </p>
</div>
<hr />

<div class="related_functions">
  <h3>Related functions</h3>
  <ul>
    <li>t_bunny_picture</li>
    <li>bunny_new_picture</li>
    <li>bunny_load_picture</li>
    <li>bunny_read_picture_id</li>
    <li>bunny_save_picture</li>
  </ul>
</div>

