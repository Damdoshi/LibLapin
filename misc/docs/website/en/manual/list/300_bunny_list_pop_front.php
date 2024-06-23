<div class="prototype">
  Macro
  $Stype@ $Sbunny_list_pop_front@(
  $Tt_bunny_list@ *$Slist@,
  $Stype@
  );
</div>
<hr />

<div class="resume">
  <h3>Description</h3>
  $A Remove the first node of the list and return its data.
</div>
<hr />

<div class="parameters">
  <h3>Parameters</h3>
  <ul>
    <li>
      $Tt_bunny_list@ *$Slist@:<br />
      $A The list to edit.
    </li>
    <li>
      $Stype@:<br />
      $A The type of the data to pop out.
    </li>
  </ul>
</div>
<hr />

<div class="return">
  <h3>Return value</h3>
  <p>Return the value that was on front. $CNULL@ if the list was empty.
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
      $CBE_CONTAINER_IS_EMPTY@:<br />
      <p>
        The list is empty.<br />
      </p>
    </li>
  </ul>
  <br />
  <p>
    Logs written by this function are tagged with the $L"container"@ label.
  </p>
</div>
<hr />

<div class="details">
  <h3>Additional informations</h3>
  <p>This macro wraps a call to a real function, which is:</p>
  <p>
    $Tvoid@ *$S_bunny_list_pop_front@(
    $Tt_bunny_list@ *$Slist@
    );
  </p>
</div>
<hr />

<div class="related_functions">
  <h3>Related functions</h3>
  <ul>
    <li>bunny_list_push_front</li>
    <li>bunny_list_push_back</li>
    <li>bunny_list_pop_back</li>
    <li>bunny_list_clear</li>
  </ul>
</div>

