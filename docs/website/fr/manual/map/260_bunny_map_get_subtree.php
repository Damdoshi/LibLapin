<div class="prototype">
  $Tt_bunny_map@ *$Sbunny_map_get_subtree@(
  $Tt_bunny_map@ *$Smap@,
  $Tvoid@ *$Skey@,
  $Tbool@ $Screate@
  );
</div>
<hr />

<div class="resume">
  <h3>Description</h3>
  $A Retrieve a node from the sent $Smap@ associated with $Skey@,
  $Screate@ it or not if it does not exist.
</div>
<hr />

<div class="parameters">
  <h3>Parameters</h3>
  <ul>
    <li>
      $Tt_bunny_map@ *$Smap@:<br />
      $A The map to browse and eventually edit.
    </li>
    <li>
      $Tvoid@ *$Skey@:<br />
      $A The key associated to the node you want to fetch or create.
    </li>
    <li>
      $Tbool@ $Screate@:<br />
      $A If $Ctrue@ and the node associated to $Skey@ does not exists, create it.
    </li>
  </ul>
</div>
<hr />

<div class="return">
  <h3>Return value</h3>
  <ul>
    <li>
      On $Bsuccess@, the function returns the address of the found or created node.
    </li>
    <li>
      On $Bfailure@, it returns $CNULL@.
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
        Out of memory.<br />
      </p>
    </li>
    <li>
      $CBE_CANNOT_DUPLICATE@:<br />
      <p>
        The set duplication function returned $CNULL@.
      </p>
    </li>
    <li>
      $CBE_CANNOT_FIND_ELEMENT@:<br />
      <p>
        The node was not found and create was $Cfalse@.
      </p>
    </li>
  </ul>
  <p>
    Logs written by this function are tagged with the $L"container"@ label.
  </p>
</div>

<div class="related_functions">
  <h3>Related functions</h3>
  <ul>
    <li>bunny_map_data</li>
    <li>bunny_map_get_data</li>
    <li>bunny_map_set_data</li>
  </ul>
</div>

