<div class="prototype">
  $Tsize_t@ $Sbunny_history_erase_frame@(
  $Tt_bunny_history@ *$Shistory@,
  $Tsize_t@ $Stime@);
</div>
<hr />

<div class="resume">
  <h3>Description</h3>
  $A This function erase the frame which is used at the sent time index.
  Note this time index does not have to perfectly match the time index of
  the frame: it just have to be one in used at this time.
</div>
<hr />

<div class="parameters">
  <h3>Parameters</h3>
  <ul>
    <li>
      $Tt_bunny_history@ *$Shistory@:<br />
      $A The history you want to edit.
    </li>
    <li>
      $Tsize_t@ $Stime@:<br />
      $A The time index of the status you want to erase.
    </li>
  </ul>
</div>
<hr />

<div class="return">
  <h3>Return value</h3>
  Returns $Ctrue@ or $Cfalse@ depending a status was erased or not.
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
      $CBE_CANNOT_FIND_ELEMENT@:<br />
      <p>
        There is no status at the current time index.
        In most case, that means the time index is too old and that
        the status at this time was deleted to free memory space.
      </p>
    </li>
  </ul>
  <br />
  <p>
    Logs written by this function are tagged with the $L"history"@ label.
  </p>
</div>
<hr />

<div class="related_functions">
  <h3>Related functions</h3>
  <ul>
    <li>bunny_history_erase_before</li>
    <li>bunny_history_erase_after</li>
  </ul>
</div>

