<div class="prototype">
  Macro
  $Tsize_t@ $Sbunny_delete_stack@($Tt_bunny_stack@ *$Sstack@);
</div>
<hr />

<div class="resume">
  <h3>Description</h3>
  $A Delete the sent stack. Do not delete elements that was stored.
</div>
<hr />

<div class="parameters">
  <h3>Parameters</h3>
  <ul>
    <li>
      $Tt_bunny_astack@ *$Sstack@:<br />
      $A The stack to delete.
    </li>
  </ul>
</div>
<hr />

<div class="return">
  <h3>Return value</h3>
  <ul>
    <li>
      The function returns the amount of element that was stored inside it
      before being destroyed.
    </li>
  </ul>
</div>

<div class="error_and_log">
  <h3>Logs</h3>
  <p>
    Logs written by this function are tagged with the $L"container"@ label.
  </p>
</div>

<div class="related_functions">
  <h3>Related functions</h3>
  <ul>
    <li>bunny_new_stack</li>
  </ul>
</div>
