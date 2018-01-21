<div class="prototype">
  Macro
  $Tt_bunny_bitfield@ *$Sbunny_new_abitfield@($Tsize_t@ $Sbit@);
</div>
<hr />

<div class="resume">
  <h3>Description</h3>
  $A Create a bitfield with a length matching the sent value in bits.
  The allocation is made with bunny_alloca on the system stack,
  so it is destroyed when leaving the function.<br />
  Bits are <b>not</b> initialized.
  <br />
  <br />
  The returned memory space must not be freed.
</div>
<hr />

<div class="parameters">
  <h3>Parameters</h3>
  <ul>
    <li>
      $Tsize_t@ $Sbit@:<br />
      $A The amount of bits to reserve.
    </li>
  </ul>
</div>
<hr />

<div class="return">
  <h3>Return value</h3>
  <ul>
    <li>
      The function returns the address of the first
      byte of the bitfield.
    </li>
  </ul>
</div>
<hr />

<div class="related_functions">
  <h3>Related functions</h3>
  <ul>
    <li>bunny_new_bitfield</li>
  </ul>
</div>

