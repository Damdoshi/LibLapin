<div class="prototype">
  Macro
  $Tt_bunny_queue@ *$Sbunny_new_queue@($Tvoid@);
g</div>
<hr />

<div class="resume">
  <h3>Description</h3>
  $A Create an Queue.
</div>
<hr />

<div class="return">
  <h3>Return value</h3>
  <ul>
    <li>
      The function returns the address of the created Queue.
      Return $CNULL@ on error.
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
    <li>bunny_new_queue</li>
    <li>bunny_delete_queue</li>
  </ul>
</div>
