<div class="prototype">
  Macro
  $Tt_bunny_stack@ *$Sbunny_new_stack@($Tvoid@);
</div>
<hr />

<div class="resume">
  <h3>Description</h3>
  $A Create an Stack.
</div>
<hr />

<div class="return">
  <h3>Return value</h3>
  <ul>
    <li>
      The function returns the address of the created Stack or $CNULL
      if an error occured.
    </li>
  </ul>
</div>

<div class="error_and_log">
  <h3>Error values and logs</h3>
  <p>
    On error, $Vbunny_errno@ is set to:
  </p>
  <br />
  <ul>
    <li>
      $CENOMEM@:<br />
      Out of memory.
    </li>
  </ul>
</div>

<div class="related_functions">
  <h3>Related functions</h3>
  <ul>
    <li>bunny_new_stack</li>
    <li>bunny_delete_stack</li>
  </ul>
</div>
