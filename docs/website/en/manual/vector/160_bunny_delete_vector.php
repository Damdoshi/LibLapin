<div class="prototype">
  $Tvoid@ $Sbunny_delete_vector@($Tt_bunny_vector@ *$Svector@);
</div>
<hr />

<div class="resume">
  <h3>Description</h3>
  $A Delete a vector. Release all data that was reserved.
  Call the destructor if any.
</div>
<hr />

<div class="parameters">
  <h3>Parameters</h3>
  <ul>
    <li>
      $Tt_bunny_vector@ *$Svector@:<br />
      $A The vector to destroy.
    </li>
  </ul>
</div>
<hr />

<div class="error_and_log">
  <h3>Logs</h3>
  <p>
    Logs written by this function are tagged with the $L"container"@ label.
  </p>
</div>
<hr />

<div class="related_functions">
  <h3>Related functions</h3>
  <ul>
    <li>bunny_new_vector</li>
    <li>bunny_build_vector</li>
  </ul>
</div>

