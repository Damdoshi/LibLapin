<div class="prototype">
  Macro
  $Tt_bunny_bitfield@ *$Sbunny_new_bitfield@($Tsize_t@ $Sbit@);
</div>
<hr />

<div class="resume">
  <h3>Description</h3>
  $A Create a bitfield with a length matching the sent value in bits.
  Bits are initialized to $Cfalse@.
  <br />
  <br />
  The returned memory space must be freed with bunny_delete_bitfield.
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
      On $Bsuccess@, the function returns the address of the first
      byte of the bitfield.
    </li>
    <li>
      On $Bfailure@, it returns $CNULL@.
    </li>
  </ul>
</div>
<hr />

<div class="error_and_log">
  <h3>Error values and logs</h3>
  <p>
    On error, $Sbunny_errno@ is set to:
  </p>
  <br />
  <ul>
    <li>
      $CENOMEM@:<br />
      $A Out of memory.
    </li>
  </ul>
  <br />
  <p>
    Logs written by this function are tagged with the $L"allocator"@ label.
  </p>
</div>
<hr />

<div class="related_functions">
  <h3>Related functions</h3>
  <ul>
    <li>bunny_new_abitfield</li>
    <li>bunny_delete_bitfield</li>
  </ul>
</div>

