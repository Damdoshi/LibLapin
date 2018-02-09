<div class="prototype">
  $Svoid@ $Sbunny_list_sort@(
  $Tt_bunny_list@ *$Slist@,
  $Tint@ (*$Ssort_function@)($Kconst@ $Tvoid@ *$Sa@, $Kconst@ $Tvoid@ *$Sb@,
  $Tvoid@ *$Sparam@),
  $Tvoid@ *$Sparam@
  );
</div>
<hr />

<div class="resume">
  <h3>Description</h3>
  $A Sort the sent list thanks to the comparator function $Ssort_function@.
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
      $Tint@ (*$Ssort_function@)($Kconst@ $Tvoid@ *$Sa@, $Kconst@ $Tvoid@ *$b@,
      $Tvoid@ *$Sparam@):
      <br />
      $A A function that will receive two elements from the list and the third
      parameter of bunny_list_sort. It must return an integer, positive if $Sa@
      is greater than $Sb@, negative if $Sb@ is greater than $Sa@ or zero
      if they are equal.
    </li>
    <li>
      $Tvoid@ *$Svoid@:<br />
      $A An arbitrary to send to $Ssort_function@ as second parameter.
    </li>
  </ul>
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
    <li>bunny_list_filter</li>
  </ul>
</div>

