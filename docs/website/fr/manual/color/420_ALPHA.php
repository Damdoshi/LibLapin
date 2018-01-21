<div class="prototype">
  Macro
  $Tunsigned int @ $S ALPHA @ ($Tunsigned char@ $Sopacity@, $Tunsigned int@ $Scolor@)
</div>

<div class="resume">
  <h3>Description</h3>
  This macro is pretty useful. It takes two parameters: an opacity and a color
  and generate a new color of the sent one with the sent opacity.
</div>
<hr />

<div class="parameters">
  <h3>Parameters</h3>
  <ul>
    <li>
      $Tunsigned char@ $Sopacity@:<br />
      $A The opacity of the color that will be generated.
    </li>
    <li>
      $Tunsigned int@ $Scolor@:<br />
      $A The color that will be used to generate a new one with the sent opacity.
    </li>
  </ul>
</div>
<hr />

<div class="return">
  <h3>Return value</h3>
  <ul>
    <li>
      This function return a 4 byte color of the sent color mixed with the
      sent opacity.
    </li>
  </ul>
</div>
