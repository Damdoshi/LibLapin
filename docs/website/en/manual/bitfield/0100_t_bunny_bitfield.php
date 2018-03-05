<div class="prototype">
  $Tt_bunny_bitfield@
</div>
<hr />

<div class="resume">
  <h3>Description</h3>
  $A The t_bunny_bitfield type is an abstract type that can only
  be manipulated throught Bunny Bitfield's functions. An instance of this type cannot
  be declared on stack but have to be created by
  bunny_new_bitfield and to be deleted by bunny_delete_bitfield.<br />
  The purpose of t_bunny_bitfield is to contain a lot of boolean values
  in the minimal possible space. This container allows you to store
  up to height boolean per byte.<br />
  <br />
  Alternative types can be used if you need to declare a bitfield on stack.
</div>
<hr />

<div class="related_functions">
  <h3>Related functions</h3>
  <ul>
    <li>bunny_new_bitfield</li>
    <li>bunny_delete_bitfield</li>
  </ul>
</div>

