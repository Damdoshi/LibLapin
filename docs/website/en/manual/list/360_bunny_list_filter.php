<div class="prototype">
  $St_bunny_list@ *$Sbunny_list_filter@(
  $Tt_bunny_list@ *$Slist@,
  $Tbool@ (*$Sfilter_function@)($Kconst@ $Tvoid@ *$Slisted@, $Tvoid@ *$Sparam@),
  $Tvoid@ *$Sparam@
  );
</div>
<hr />

<div class="resume">
  <h3>Description</h3>
  $A Generate a new list with elements accepted by $Sfilter_function@.
</div>
<hr />

<div class="parameters">
  <h3>Parameters</h3>
  <ul>
    <li>
      $Tt_bunny_list@ *$Slist@:<br />
      $A The list to filter.
    </li>
    <li>
      $Tbool@ (*$Sfilter_function@)($Kconst@ $Tvoid@ *$Slisted@, $Tvoid@ *$Sparam@):
      <br />
      $A A function that will receive an element from the list and the third
      parameter of bunny_list_filter. It must return $Ctrue@ to add the received
      element to the generated list, $Cfalse to not include it.
    </li>
    <li>
      $Tvoid@ *$Svoid@:<br />
      $A An arbitrary to send to $Sfilter_function@ as second parameter.
    </li>
  </ul>
</div>
<hr />

<div class="return">
  <h3>Return value</h3>
  <p>Return the generated list. $CNULL@ on error.
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
        Out of memory.
      </p>
    </li>
  </ul>
  <br />
  <p>
    Logs written by this function are tagged with the $L"container"@ label.
  </p>
</div>
<hr />

<div class="related_functions">
  <h3>Related functions</h3>
  <ul>
    <li>bunny_list_sort</li>
  </ul>
</div>

