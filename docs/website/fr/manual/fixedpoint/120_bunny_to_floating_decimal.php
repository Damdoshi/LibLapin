<div class="prototype">
  Macro
  $Tdouble@ $Sbunny_to_floating_decimal@($Kconst@ $Sval@, $Sprec@);
</div>
<hr />

<div class="resume">
  <h3>Description</h3>
  $A Transform fixed point decimal number into a double precision
  floating decimal number.
</div>
<hr />

<div class="parameters">
  <h3>Parameters</h3>
  <ul>
    <li>
      $Kconst@ $Sval@:<br />
      $A A fixed point decimal number to be converted.
    </li>
    <li>
      $Sprec@:<br />
      $A The precision in bits of the fixed point decimal.
      It is an amount of bits.
    </li>
  </ul>
</div>
<hr />

<div class="return">
  <h3>Return value</h3>
  $A A double with a value that match the send number. You can
  generate fixed point decimal number with
  bunny_to_fixed_decimal.
</div>


