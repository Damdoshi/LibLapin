<div class="prototype">
  $Tbool@ $Sbunny_trace@($Tdouble@ *$Svalue@, $Tdouble@ $Slimit@, $Tdouble@ $Sstep@);
</div>
<hr />

<div class="resume">
  <h3>Description</h3>
  $A Make $Svalue@ reaching $Slimit@ $Sstep@ by $Sstep@. Returns $Ctrue@ if
  $Svalue@ reached $Slimit@.
</div>
<hr />

<div class="parameters">
  <h3>Parameters</h3>
  <ul>
    <li>
      $Tdouble@ *$Svalue@:<br />
      $A The value that must reach $Slimit@.
    </li>
    <li>
      $Tdouble@ $Slimit@:<br />
      $A The $Slimit@ to reach.
    </li>
    <li>
      $Tdouble@ $Sstep@:<br />
      $A The value that will be added or removed from *$Svalue@ to make it
      reach $Slimit@. $Sstep@ must be positive.
    </li>
  </ul>
</div>
<hr />

<div class="return">
  <h3>Return value</h3>
  <p>Returns $Ctrue@ if *$Svalue@ have reached $Slimit@.
</div>

