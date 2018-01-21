<div class="prototype">
  Macro
  $Tunsigned int @ $S COLOR @ (
  $Tunsigned char@ $Sopacity@,
  $Tunsigned char@ $Sred@,
  $Tunsigned char@ $Sgreen@,
  $Tunsigned char@ $Sblue@
  );
</div>

<div class="resume">
  <h3>Description</h3>
  This macro build a 4 byte color from 4 1 byte color components.
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
      $Tunsigned char@ $Sred@:<br />
      $A The red part of the generated color.
    </li>
    <li>
      $Tunsigned char@ $Sgreen@:<br />
      $A The green part of the generated color.
    </li>
    <li>
      $Tunsigned char@ $Sblue@:<br />
      $A The blue part of the generated color.
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
