<div class="prototype">
  $Tbool@ $Sbunny_uncipher_file@(
  $Tvoid@ *$Sdata@,
  $Tsize_t@ $Sdatalen@,
  $Tt_bunny_ciphering@ $Sciphering@,
  $Kconst@ $Tt_bunny_cipher_key@ *$Skey@
  );
</div>
<hr />

<div class="resume">
  <h3>Description</h3>
  $A Cipher the sent $Sdata@ of the length $Sdatalen@ with the sent algorithm and
  the sent key.
</div>
<hr />

<div class="parameters">
  <h3>Parameters</h3>
  <ul>
    <li>
      $Tvoid@ *$Sdata@:<br />
      $A The data to cipher.
    </li>
    <li>
      $Tsize_t@ $Sdatalen@:<br />
      $A The length of $Sdata@ in bytes.
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

<div class="related_functions">
  <h3>Related functions</h3>
  <ul>
    <li>bunny_cipher_file</li>
    <li>bunny_uncipher_file</li>
    <li>bunny_cipher_data</li>
  </ul>
</div>

