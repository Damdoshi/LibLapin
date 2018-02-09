<div class="prototype">
  $Tt_bunny_cipher_key@ *$Sbunny_new_key@(
  $Tsize_t@ $Slen@
  );
</div>
<hr />

<div class="resume">
  <h3>Description</h3>
  $A Reserve and generate a new key.
</div>
<hr />

<div class="parameters">
  <h3>Parameters</h3>
  <ul>
    <li>
      $Tsize_t@ $Slen@:<br />
      $A The length in byte of the key. It must be pair.
    </li>
  </ul>
</div>
<hr />

<div class="return">
  <h3>Return value</h3>
  <ul>
    <li>
      On $Bsuccess@, the function returns a valid t_bunny_cipher_key
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
      $CEINVAL@:<br />
      <p>
        Invalid length.
      </p>
    </li>
    <li>
      $CENOMEM@:<br />
      <p>
        Out of memory.
      </p>
    </li>
  </ul>
  <br />
  <p>
    Logs written by this function are tagged with the $L"security"@ label.
  </p>
</div>
<hr />

<div class="related_functions">
  <h3>Related functions</h3>
  <ul>
    <li>bunny_delete_key</li>
  </ul>
</div>

