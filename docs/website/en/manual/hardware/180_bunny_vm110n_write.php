<div class="prototype">
  $Tbool@ $Sbunny_vm110n_write@($Kconst@ $Tt_bunny_vm110n@ *$Svm110n@);
</div>
<hr />

<div class="resume">
  <h3>Description</h3>
  $A Write the status on board. Fields $Sdigital_outsputs@ and $Sanalog_outputs@
  are applied when this function is called.
</div>
<hr />

<div class="parameters">
  <h3>Parameters</h3>
  <ul>
    <li>
      $Kconst@ $Tt_bunny_vm110n@ *$Svm110n@:<br />
      $A The structure to write on board.
    </li>
  </ul>
</div>
<hr />

<div class="return">
  <h3>Return value</h3>
  <p>$Ctrue@ if the reading was done, $Cfalse on error.
</div>
<hr />

<div class="error_and_log">
  <h3>Error values and logs</h3>
  <p>
    On error, $Vbunny_errno@ is set to:
  </p>
  <br />
  <ul>
    <li>
      $CEINVAL@:<br />
      <p>
        One of the analog output value was incorrect. They should be between 0 and 1.
      </p>
    </li>
    <li>
      $CEWOULDBLOCK@:<br />
      <p>
        Retry later, maybe the board was not ready.
      </p>
    </li>
  </ul>
  <br />
  <p>
    Logs written by this function are tagged with the $L"vm110n"@ label.
  </p>
</div>
<hr />

<div class="related_functions">
  <h3>Related functions</h3>
  <ul>
    <li>bunny_vm110n_read</li>
  </ul>
</div>

