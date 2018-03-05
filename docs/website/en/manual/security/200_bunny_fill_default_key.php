<div class="prototype">
  $Tbool@ $Sbunny_fill_default_key@(
  $Kconst@ $Tchar@ *$Sbunny_program@,
  $Tt_bunny_cipher_key@ *$Skey@
  );
</div>
<hr />

<div class="resume">
  <h3>Description</h3>
  $A Write the sent key into the sent program file, in the place
  of the embedded key.
</div>
<hr />

<div class="parameters">
  <h3>Parameters</h3>
  <ul>
    <li>
      $Kconst@ $Tchar@ *$Sbunny_program@:<br />
      $A A software that needs an embedded key. The sent key will
      be written inside.
    </li>
    <li>
      $Tt_bunny_cipher_key@ *$Skey@:<br />
      $A The key that will be written inside the sent program.
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
      $CBE_CANNOT_FIND_EMBEDDED_KEY@:<br />
      <p>
        The key cannot be found inside the sent program.
      </p>
    </li>
    <li>
      Any errno code that open, read or write can set.
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
    <li>gl_bunny_ciphering_table</li>
    <li>t_bunny_cipher_key</li>
    <li>bunny_default_key</li>
  </ul>
</div>

