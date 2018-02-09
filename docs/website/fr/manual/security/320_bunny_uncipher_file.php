<div class="prototype">
  $Tbool@ $Sbunny_uncipher_file@(
  $Kconst@ $Tchar@ *$Sfile@,
  $Tt_bunny_ciphering@ $Sciphering@,
  $Kconst@ $Tt_bunny_cipher_key@ *$Skey@
  );
</div>
<hr />

<div class="resume">
  <h3>Description</h3>
  $A Uncipher the sent file with the sent algorithm and
  the sent key.
</div>
<hr />

<div class="parameters">
  <h3>Parameters</h3>
  <ul>
    <li>
      $Kconst@ $Tchar@ *$Sfile@:<br />
      $A The file you want to uncipher.
    </li>
    <li>
      $Tt_bunny_ciphering@ $Sciphering@:<br />
      $A The ciphering algorithm you want to use.
    </li>
    <li>
      $Kconst@ $Tt_bunny_cipher_key@ *$Skey@:<br />
      $A The key the algorithm will use.
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
        Out of memory.
      </p>
    </li>
    <li>
      Any errno value that can be set by open, read or write.
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
    <li>bunny_cipher_file</li>
    <li>bunny_cipher_data</li>
    <li>bunny_uncipher_data</li>
  </ul>
</div>

