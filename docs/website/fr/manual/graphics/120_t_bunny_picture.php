<div class="prototype">
  $Ktypedef@ $Tt_bunny_clipable@ $Tt_bunny_picture@;
</div>
<hr />

<div class="resume">
  <h3>Description</h3>
  $A This type is the same as t_bunny_clipable but with a different meaning.
  A t_bunny_clipable is a component for other types that can be t_bunny_font
  or t_bunny_pixelarray. t_bunny_picture is also composed of a t_bunny_clipable:
  the only difference is that it is <b>only and fully</b> composed by it.<br />
  Actually, there is differences, but they are on the private side.<br />
  <br />
  This type is very fast for sprite based computation: drawing large chunks
  of pictures at specific places. Doing per-pixel computation is very slow
  on this kind of picture.<br />
  <br />
  This type of picture must be deleted by bunny_delete_clipable.
</div>
<hr />

<div class="related_functions">
  <h3>Related functions</h3>
  <ul>
    <li>bunny_new_picture</li>
    <li>bunny_load_picture</li>
    <li>bunny_read_picture_id</li>
    <li>bunny_read_picture</li>
    <li>bunny_delete_clipable</li>
  </ul>
</div>
