<div class="prototype">
  $Kconst@ $Tchar@ * $Kconst@ *$Sbunny_split@(
  $Kconst@ $Tchar@ *$Sstring@,
  $Kconst@ $Tchar@ **$Stokens@,
  $Tbool@ $Saggregate@
  );
</div>
<hr />

<div class="resume">
  <h3>Description</h3>
  $A Split the sent $Sstring@ accordingly to the sent tokens.<br />
  For example:<br />
  $Kconst@ $Tchar@ $Stok@[3] = {$L","@, $L"=="@, $CNULL@};<br />
  <br />
  bunny_split($L"a, b == c", &tok[0], $Cfalse@);<br />
  Will return $L"a"@, $L" b "@ and $L" c"@.<br />
  <br />
  The $Saggregate@ parameter is useful to ignore several following tokens.<br />
  <br />
  Play attention with the order in tokens: the priority is the order of the
  token themselves! Not the length! The more they are close to the beginning, the
  higher they are.<br />
  <br />
  The returned memory must be deleted with bunny_delete_split.
</div>
<hr />

<div class="parameters">
  <h3>Parameters</h3>
  <ul>
    <li>
      $Kconst@ $Tchar@ *$Sstring@:<br />
      $A The string to split. bunny_split can only handle less than 4096 words.
    </li>
    <li>
      $Kconst@ $Tchar@ **$Stokens@:<br />
      $A An array of strings that are separator for the string to split.
      It must be $CNULL@ terminated. There cannot be more than 31 tokens.
    </li>
    <li>
      $Tbool@ $Saggregate@:<br />
      $A Can the separator be stacked or not?
    </li>
  </ul>
</div>
<hr />

<div class="return">
  <h3>Return value</h3>
  <p>Return a valid array of string if successful, $CNULL@ on error.
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
    Logs written by this function are tagged with the $L"misc"@ label.
  </p>
</div>
<hr />

<div class="related_functions">
  <h3>Related functions</h3>
  <ul>
    <li>bunny_delete_split</li>
    <li>t_bunny_split</li>
  </ul>
</div>

