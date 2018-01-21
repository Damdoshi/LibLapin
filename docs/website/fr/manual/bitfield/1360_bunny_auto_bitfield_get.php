<div class="prototype">
  Macro
  $Tvoid@ *$Sbunny_auto_bitfield_get@($Kconst@ $Tt_bunny_auto_bitfieldX@ $Sbitfield@, $Tsize_t@ $Sidx@);
</div>
<hr />

<div class="resume">
  <h3>Description</h3>
  $A Get the bit at position $Sidx@ inside $Sbitfield@.
</div>
<hr />

<div class="parameters">
  <h3>Parameters</h3>
  <ul>
    <li>
      $Kconst@ $Tt_bunny_bitfield@ $Sbitfield@:<br />
      $A The bitfield to edit. It must be a direct instance of
      $Tt_bunny_auto_bitfield8@, 16, 32 or 64.
    </li>
    <li>
      $Tsize_t@ $Sidx@:<br />
      $A The position in bit of the bit to get.
    </li>
  </ul>
</div>
<hr />

<div class="return">
  <h3>Return value</h3>
  <p>The bit status: $Ctrue@ or $Cfalse@.</p>
</div>
<hr />

<div class="related_functions">
  <h3>Related functions</h3>
  <ul>
    <li>bunny_auto_bitfield_set</li>
    <li>bunny_auto_bitfield_clr</li>
  </ul>
</div>

