<div class="prototype">
  $Tt_bunny_font@ *$Sbunny_load_text@(
  $K const @ $T char @ * $S file @,
  );
</div>
<hr />

<div class="resume">
  <h3>Description</h3>
  $A Create a t_bunny_font, fully configured after a configuration file.
  <br />
  <br />
  The returned memory space must be freed with bunny_delete_clipable.
</div>
<hr />

<div class="parameters">
  <h3>Parameters</h3>
  <ul>
    <li>
      $Kconst@ $Tchar@ *$Sfile@:<br />
      $A The file to load that will be used to build the t_bunny_font.
    </li>
  </ul>
</div>
<hr />

<div class="return">
  <h3>Return value</h3>
  <ul>
    <li>
      On $Bsuccess@, the function returns a valid t_bunny_font.
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
    On error, $Sbunny_errno@ is set to:
  </p>
  <br />
  <ul>
    <li>
      $CENOMEM@:<br />
      <p>
        Out of memory.
      </p>
    </li>
    <li>
      $CEINVAL@:<br />
      <p>
        The sent file was invalid or the ressource file inside was invalid.
      </p>
    </li>
  </ul>
  <br />
  <p>
    Logs written by this function are tagged with $L"ressource"@
    and $L"text"@ labels.
  </p>
</div>
<hr />

<div class="details">
  <h3>Additional informations</h3>
  <h4>Picture base font format:</h4>
  <p>
    See bunny_load_font for more details.
  </p>
</div>
<hr />

<div class="related_functions">
  <h3>Related functions</h3>
  <ul>
    <li>bunny_load_font</li>
    <li>bunny_delete_clipable</li>
    <li>bunny_draw</li>
  </ul>
</div>

