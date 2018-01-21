<div class="prototype">
  Macro
  $Tuint64_t@ $Sbunny_to_fixed_decimal@($Kconst@ $Sval@, $Sprec@, $Ssiz@);
</div>
<hr />

<div class="resume">
  <h3>Description</h3>
  $A Transform a double or a float to a fixed point decimal number
  of a specific length and a specific precision.
</div>
<hr />

<div class="parameters">
  <h3>Parameters</h3>
  <ul>
    <li>
      $Kconst@ $Sval@:<br />
      $A A float or a double to transform into a fixed point decimal.
    </li>
    <li>
      $Sprec@:<br />
      $A The precision in bits of the fixed point decimal.
      It is an amount of bits.
    </li>
    <li>
      $Ssiz@:<br />
      $A The size in bits of the whole fixed point decimal.
      The maximum is 64.
    </li>
  </ul>
</div>
<hr />

<div class="return">
  <h3>Return value</h3>
  $A A fixed point arithemtic decimal number of $Ssiz@ bits, that
  can be converted back to a float or a double thanks to
  bunny_to_floating_decimal.
</div>

