<div class="prototype">
  Macro
  $Stype@ $Sbunny_list_push_back@(
  $Tt_bunny_list@ *$Slist@,
  $Sdata@
  );
</div>
<hr />

<div class="resume">
  <h3>Description</h3>
  $A Add the sent $Sdata@ at last element of $Slist@.
</div>
<hr />

<div class="parameters">
  <h3>Parameters</h3>
  <ul>
    <li>
      $Tt_bunny_list@ *$Slist@:<br />
      $A The list to enlarge.
    </li>
    <li>
      $Sdata@:<br />
      $A A data to any type to push at the end of the list.
    </li>
  </ul>
</div>
<hr />

<div class="return">
  <h3>Return value</h3>
  <p>Return $Ctrue@ if everything went well.</p>
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
      $CENOMEM@:<br />
      <p>
        Out of memory.<br />
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
    $Tbool@ $S_bunny_list_push_back@(
    $Tt_bunny_list@ *$Slist@,
    $Kconst@ $Tvoid@ *$Sdata@
    );
  </p>
</div>
<hr />

<div class="related_functions">
  <h3>Related functions</h3>
  <ul>
    <li>bunny_list_push_front</li>
    <li>bunny_list_pop_front</li>
    <li>bunny_list_pop_back</li>
    <li>bunny_list_clear</li>
  </ul>
</div>

