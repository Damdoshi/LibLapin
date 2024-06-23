<div class="prototype">
  Macro
  $Tunsigned int @ $S ALPHA_GRAY @ (
  $Tunsigned char@ $Sopacity@,
  $Tunsigned char@ $Sgray@
  );
</div>

<div class="resume">
  <h3>Description</h3>
  This macro build a 4 byte color of gray color and with
  sent opacity.
</div>
<hr />

<div class="parameters">
  <h3>Parameters</h3>
  <ul>
    <li>
      $Tunsigned char@ $Sopacity@:<br />
      $A The opacity of the generated color.
    </li>
    <li>
      $Tunsigned char@ $Sgray@:<br />
      $A The red, green and blue part of the generated color.
    </li>
  </ul>
</div>
<hr />

<div class="return">
  <h3>Return value</h3>
  <ul>
    <li>
      This function returns a 4 byte color, mixing all the sent
      components.
    </li>
  </ul>
</div>
